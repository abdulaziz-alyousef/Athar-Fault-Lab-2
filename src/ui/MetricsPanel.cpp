#include "MetricsPanel.h"
#include "UiLanguage.h"

#include "../simulation/SimulationEngine.h"

#include <QApplication>
#include <QColor>
#include <QFont>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QRectF>

#include <algorithm>
#include <cmath>

namespace
{
bool chartUsesLightTheme()
{
    return qApp &&
           qApp->property("atharTheme").toString() == "light";
}

QColor chartBackgroundColor()
{
    return chartUsesLightTheme()
               ? QColor("#f6f8fa")
               : QColor("#0d1117");
}

QColor chartPanelColor()
{
    return chartUsesLightTheme()
               ? QColor("#ffffff")
               : QColor("#161b22");
}

QColor chartBorderColor()
{
    return chartUsesLightTheme()
               ? QColor("#d0d7de")
               : QColor("#30363d");
}

QColor chartGridColor()
{
    return chartUsesLightTheme()
               ? QColor("#d8dee4")
               : QColor("#21262d");
}

QColor chartTextColor()
{
    return chartUsesLightTheme()
               ? QColor("#1f2328")
               : QColor("#f0f6fc");
}

QColor chartSecondaryTextColor()
{
    return chartUsesLightTheme()
               ? QColor("#59636e")
               : QColor("#8b949e");
}

QColor chartSuccessColor()
{
    return chartUsesLightTheme()
               ? QColor("#1a7f37")
               : QColor("#3fb950");
}

QColor chartFailureColor()
{
    return chartUsesLightTheme()
               ? QColor("#cf222e")
               : QColor("#f85149");
}

QColor chartLatencyColor()
{
    return chartUsesLightTheme()
               ? QColor("#0969da")
               : QColor("#58a6ff");
}

QPointF mapPoint(
    const QRectF &rect,
    double xValue,
    double yValue,
    double yMaximum
)
{
    double x =
        rect.left() +
        rect.width() *
            std::clamp(
                xValue / 100.0,
                0.0,
                1.0
            );

    double normalizedY =
        yMaximum > 0.0
            ? std::clamp(
                  yValue / yMaximum,
                  0.0,
                  1.0
              )
            : 0.0;

    double y =
        rect.bottom() -
        rect.height() *
            normalizedY;

    return QPointF(
        x,
        y
    );
}
}

MetricsPanel::MetricsPanel(
    SimulationEngine *engine,
    QWidget *parent
)
    : QWidget(parent),
      m_engine(engine),
      m_lastProgress(-1)
{
    setMinimumHeight(
        320
    );

    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );

    if (!m_engine)
    {
        return;
    }

    connect(
        m_engine,
        &SimulationEngine::statsUpdated,
        this,
        [this](
            int processed,
            int,
            int failed,
            double successRate,
            double averageLatency,
            int progress
        )
        {
            addSample(
                processed,
                failed,
                successRate,
                averageLatency,
                progress
            );
        }
    );

    connect(
        m_engine,
        &SimulationEngine::statusChanged,
        this,
        [this](
            const QString &status
        )
        {
            if (
                status == "RUNNING" ||
                status == "READY"
            )
            {
                resetSeries();
            }
        }
    );
}

QSize MetricsPanel::minimumSizeHint() const
{
    return QSize(
        650,
        340
    );
}

void MetricsPanel::resetSeries()
{
    m_samples.clear();
    m_lastProgress = -1;
    update();
}

void MetricsPanel::addSample(
    int processed,
    int failed,
    double successRate,
    double latency,
    int progress
)
{
    double runtimeFailureRate =
        processed > 0
            ? (
                  static_cast<double>(
                      failed
                  ) /
                  static_cast<double>(
                      processed
                  )
              ) *
                  100.0
            : 0.0;

    Sample sample{
        std::clamp(
            progress,
            0,
            100
        ),
        std::clamp(
            successRate,
            0.0,
            100.0
        ),
        std::clamp(
            runtimeFailureRate,
            0.0,
            100.0
        ),
        std::max(
            0.0,
            latency
        )
    };

    if (
        !m_samples.isEmpty() &&
        m_lastProgress == sample.progress
    )
    {
        m_samples.last() =
            sample;
    }
    else
    {
        m_samples.append(
            sample
        );

        m_lastProgress =
            sample.progress;
    }

    if (
        m_samples.size() >
        101
    )
    {
        m_samples.remove(
            0,
            m_samples.size() -
                101
        );
    }

    update();
}

void MetricsPanel::paintEvent(
    QPaintEvent *event
)
{
    QWidget::paintEvent(
        event
    );

    QPainter painter(
        this
    );

    painter.setRenderHint(
        QPainter::Antialiasing,
        true
    );

    painter.fillRect(
        rect(),
        chartBackgroundColor()
    );

    QRectF outer =
        QRectF(
            rect()
        ).adjusted(
            1.0,
            1.0,
            -1.0,
            -1.0
        );

    painter.setPen(
        QPen(
            chartBorderColor(),
            1.0
        )
    );

    painter.setBrush(
        chartPanelColor()
    );

    painter.drawRoundedRect(
        outer,
        10.0,
        10.0
    );

    painter.setPen(
        chartTextColor()
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            13,
            QFont::Bold
        )
    );

    painter.drawText(
        QRectF(
            20.0,
            14.0,
            width() - 40.0,
            26.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        UiLanguage::text("Live Performance")
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            9,
            QFont::Normal
        )
    );

    painter.setPen(
        chartSecondaryTextColor()
    );

    painter.drawText(
        QRectF(
            20.0,
            40.0,
            width() - 40.0,
            22.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        UiLanguage::text("Runtime request outcome and average latency during the current simulation.")
    );

    QRectF content =
        QRectF(
            rect()
        ).adjusted(
            20.0,
            72.0,
            -20.0,
            -18.0
        );

    double gap =
        18.0;

    double rateHeight =
        content.height() *
        0.56;

    QRectF rateRect(
        content.left(),
        content.top(),
        content.width(),
        rateHeight
    );

    QRectF latencyRect(
        content.left(),
        rateRect.bottom() +
            gap,
        content.width(),
        content.bottom() -
            rateRect.bottom() -
            gap
    );

    drawRateChart(
        painter,
        rateRect
    );

    drawLatencyChart(
        painter,
        latencyRect
    );
}

void MetricsPanel::drawRateChart(
    QPainter &painter,
    const QRectF &rect
) const
{
    painter.save();

    painter.setPen(
        chartSecondaryTextColor()
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            9,
            QFont::DemiBold
        )
    );

    painter.drawText(
        QRectF(
            rect.left(),
            rect.top(),
            160.0,
            20.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        UiLanguage::text("REQUEST OUTCOME")
    );

    const double legendY =
        rect.top();

    painter.setPen(
        QPen(
            chartSuccessColor(),
            3.0
        )
    );

    painter.drawLine(
        QPointF(
            rect.right() - 250.0,
            legendY + 10.0
        ),
        QPointF(
            rect.right() - 220.0,
            legendY + 10.0
        )
    );

    painter.setPen(
        chartSecondaryTextColor()
    );

    painter.drawText(
        QRectF(
            rect.right() - 212.0,
            legendY,
            90.0,
            20.0
        ),
        UiLanguage::text("Success Rate")
    );

    painter.setPen(
        QPen(
            chartFailureColor(),
            3.0
        )
    );

    painter.drawLine(
        QPointF(
            rect.right() - 112.0,
            legendY + 10.0
        ),
        QPointF(
            rect.right() - 82.0,
            legendY + 10.0
        )
    );

    painter.setPen(
        chartSecondaryTextColor()
    );

    painter.drawText(
        QRectF(
            rect.right() - 74.0,
            legendY,
            74.0,
            20.0
        ),
        UiLanguage::text("Runtime Fail")
    );

    QRectF plot =
        rect.adjusted(
            44.0,
            28.0,
            -10.0,
            -26.0
        );

    painter.setPen(
        QPen(
            chartGridColor(),
            1.0
        )
    );

    for (
        int value = 0;
        value <= 100;
        value += 25
    )
    {
        double y =
            plot.bottom() -
            plot.height() *
                static_cast<double>(
                    value
                ) /
                100.0;

        painter.drawLine(
            QPointF(
                plot.left(),
                y
            ),
            QPointF(
                plot.right(),
                y
            )
        );

        painter.setPen(
            chartSecondaryTextColor()
        );

        painter.drawText(
            QRectF(
                rect.left(),
                y - 9.0,
                38.0,
                18.0
            ),
            Qt::AlignRight |
                Qt::AlignVCenter,
            QString::number(
                value
            ) +
                "%"
        );

        painter.setPen(
            QPen(
                chartGridColor(),
                1.0
            )
        );
    }

    if (
        m_samples.isEmpty()
    )
    {
        painter.setPen(
            chartSecondaryTextColor()
        );

        painter.drawText(
            plot,
            Qt::AlignCenter,
            UiLanguage::text("Start a simulation to populate the chart.")
        );

        painter.restore();
        return;
    }

    QPainterPath successPath;
    QPainterPath failurePath;

    for (
        int index = 0;
        index < m_samples.size();
        ++index
    )
    {
        const Sample &sample =
            m_samples[index];

        QPointF successPoint =
            mapPoint(
                plot,
                sample.progress,
                sample.successRate,
                100.0
            );

        QPointF failurePoint =
            mapPoint(
                plot,
                sample.progress,
                sample.failureRate,
                100.0
            );

        if (
            index == 0
        )
        {
            successPath.moveTo(
                successPoint
            );

            failurePath.moveTo(
                failurePoint
            );
        }
        else
        {
            successPath.lineTo(
                successPoint
            );

            failurePath.lineTo(
                failurePoint
            );
        }
    }

    painter.setBrush(
        Qt::NoBrush
    );

    painter.setPen(
        QPen(
            chartSuccessColor(),
            2.5
        )
    );

    painter.drawPath(
        successPath
    );

    painter.setPen(
        QPen(
            chartFailureColor(),
            2.5
        )
    );

    painter.drawPath(
        failurePath
    );

    painter.restore();
}

void MetricsPanel::drawLatencyChart(
    QPainter &painter,
    const QRectF &rect
) const
{
    painter.save();

    painter.setPen(
        chartSecondaryTextColor()
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            9,
            QFont::DemiBold
        )
    );

    painter.drawText(
        QRectF(
            rect.left(),
            rect.top(),
            180.0,
            20.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        UiLanguage::text("AVERAGE LATENCY")
    );

    painter.setPen(
        QPen(
            chartLatencyColor(),
            3.0
        )
    );

    painter.drawLine(
        QPointF(
            rect.right() - 120.0,
            rect.top() + 10.0
        ),
        QPointF(
            rect.right() - 90.0,
            rect.top() + 10.0
        )
    );

    painter.setPen(
        chartSecondaryTextColor()
    );

    painter.drawText(
        QRectF(
            rect.right() - 82.0,
            rect.top(),
            82.0,
            20.0
        ),
        UiLanguage::text("Latency ms")
    );

    QRectF plot =
        rect.adjusted(
            52.0,
            28.0,
            -10.0,
            -18.0
        );

    double maximumLatency =
        100.0;

    for (
        const Sample &sample :
        m_samples
    )
    {
        maximumLatency =
            std::max(
                maximumLatency,
                sample.latency
            );
    }

    maximumLatency =
        std::ceil(
            maximumLatency /
            25.0
        ) *
        25.0;

    painter.setPen(
        QPen(
            chartGridColor(),
            1.0
        )
    );

    for (
        int step = 0;
        step <= 4;
        ++step
    )
    {
        double value =
            maximumLatency *
            static_cast<double>(
                step
            ) /
            4.0;

        double y =
            plot.bottom() -
            plot.height() *
                static_cast<double>(
                    step
                ) /
                4.0;

        painter.drawLine(
            QPointF(
                plot.left(),
                y
            ),
            QPointF(
                plot.right(),
                y
            )
        );

        painter.setPen(
            chartSecondaryTextColor()
        );

        painter.drawText(
            QRectF(
                rect.left(),
                y - 9.0,
                46.0,
                18.0
            ),
            Qt::AlignRight |
                Qt::AlignVCenter,
            QString::number(
                value,
                'f',
                0
            )
        );

        painter.setPen(
            QPen(
                chartGridColor(),
                1.0
            )
        );
    }

    if (
        m_samples.isEmpty()
    )
    {
        painter.restore();
        return;
    }

    QPainterPath latencyPath;

    for (
        int index = 0;
        index < m_samples.size();
        ++index
    )
    {
        const Sample &sample =
            m_samples[index];

        QPointF point =
            mapPoint(
                plot,
                sample.progress,
                sample.latency,
                maximumLatency
            );

        if (
            index == 0
        )
        {
            latencyPath.moveTo(
                point
            );
        }
        else
        {
            latencyPath.lineTo(
                point
            );
        }
    }

    painter.setBrush(
        Qt::NoBrush
    );

    painter.setPen(
        QPen(
            chartLatencyColor(),
            2.5
        )
    );

    painter.drawPath(
        latencyPath
    );

    painter.restore();
}