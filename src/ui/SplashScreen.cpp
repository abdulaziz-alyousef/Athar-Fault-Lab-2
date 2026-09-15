#include "SplashScreen.h"

#include <QColor>
#include <QFont>
#include <QGuiApplication>
#include <QLinearGradient>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QRectF>
#include <QRadialGradient>
#include <QScreen>
#include <QtGlobal>

SplashScreen::SplashScreen(
    bool lightTheme,
    QWidget *parent
)
    : QWidget(parent),
      m_lightTheme(lightTheme),
      m_durationMs(1800),
      m_progress(0)
{
    setWindowFlags(
        Qt::SplashScreen |
        Qt::FramelessWindowHint |
        Qt::WindowStaysOnTopHint
    );

    setAttribute(
        Qt::WA_TranslucentBackground,
        true
    );

    setAttribute(
        Qt::WA_ShowWithoutActivating,
        true
    );

    setFixedSize(
        760,
        430
    );

    setWindowOpacity(
        1.0
    );

    connect(
        &m_frameTimer,
        &QTimer::timeout,
        this,
        [this]()
        {
            if (!m_elapsed.isValid())
            {
                return;
            }

            const qint64 elapsedMs =
                m_elapsed.elapsed();

            const double ratio =
                m_durationMs > 0
                    ? static_cast<double>(elapsedMs) /
                          static_cast<double>(m_durationMs)
                    : 1.0;

            m_progress =
                qBound(
                    0,
                    qRound(ratio * 100.0),
                    100
                );

            update();

            if (m_progress >= 100)
            {
                m_frameTimer.stop();
            }
        }
    );
}

void SplashScreen::startAnimation(
    int durationMs
)
{
    m_durationMs =
        qMax(
            700,
            durationMs
        );

    m_progress = 0;

    centerOnPrimaryScreen();

    m_elapsed.restart();

    m_frameTimer.start(
        16
    );

    update();
}

void SplashScreen::centerOnPrimaryScreen()
{
    QScreen *screen =
        QGuiApplication::primaryScreen();

    if (!screen)
    {
        return;
    }

    const QRect available =
        screen->availableGeometry();

    move(
        available.center() -
        rect().center()
    );
}

QString SplashScreen::statusText() const
{
    if (m_progress < 28)
    {
        return "Preparing simulation engine";
    }

    if (m_progress < 58)
    {
        return "Loading services and interface";
    }

    if (m_progress < 88)
    {
        return "Restoring workspace settings";
    }

    if (m_progress < 100)
    {
        return "Finalizing startup";
    }

    return "Ready";
}

void SplashScreen::paintEvent(
    QPaintEvent *event
)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint(
        QPainter::Antialiasing,
        true
    );

    painter.setRenderHint(
        QPainter::TextAntialiasing,
        true
    );

    const QColor background =
        m_lightTheme
            ? QColor("#f6f8fa")
            : QColor("#0d1117");

    const QColor panel =
        m_lightTheme
            ? QColor("#ffffff")
            : QColor("#161b22");

    const QColor panelSecondary =
        m_lightTheme
            ? QColor("#f0f3f6")
            : QColor("#111820");

    const QColor border =
        m_lightTheme
            ? QColor("#d0d7de")
            : QColor("#30363d");

    const QColor primaryText =
        m_lightTheme
            ? QColor("#1f2328")
            : QColor("#f0f6fc");

    const QColor secondaryText =
        m_lightTheme
            ? QColor("#59636e")
            : QColor("#8b949e");

    const QColor accent =
        m_lightTheme
            ? QColor("#0969da")
            : QColor("#58a6ff");

    const QColor green =
        m_lightTheme
            ? QColor("#1a7f37")
            : QColor("#3fb950");

    const QColor amber =
        m_lightTheme
            ? QColor("#9a6700")
            : QColor("#d29922");

    const QRectF card(
        16.0,
        16.0,
        width() - 32.0,
        height() - 32.0
    );

    QColor shadowColor(
        0,
        0,
        0,
        m_lightTheme ? 45 : 100
    );

    painter.setPen(
        Qt::NoPen
    );

    painter.setBrush(
        shadowColor
    );

    painter.drawRoundedRect(
        card.translated(
            0.0,
            7.0
        ),
        24.0,
        24.0
    );

    QLinearGradient cardGradient(
        card.topLeft(),
        card.bottomRight()
    );

    cardGradient.setColorAt(
        0.0,
        panel
    );

    cardGradient.setColorAt(
        1.0,
        background
    );

    painter.setBrush(
        cardGradient
    );

    painter.setPen(
        QPen(
            border,
            1.0
        )
    );

    painter.drawRoundedRect(
        card,
        24.0,
        24.0
    );

    const QRectF logoPanel(
        46.0,
        55.0,
        220.0,
        300.0
    );

    painter.setPen(
        QPen(
            border,
            1.0
        )
    );

    painter.setBrush(
        panelSecondary
    );

    painter.drawRoundedRect(
        logoPanel,
        20.0,
        20.0
    );

    // Decorative glow behind the Athar network mark.
    QRadialGradient glow(
        QPointF(
            156.0,
            176.0
        ),
        100.0
    );

    QColor glowCenter =
        accent;

    glowCenter.setAlpha(
        m_lightTheme ? 38 : 62
    );

    QColor glowEdge =
        accent;

    glowEdge.setAlpha(
        0
    );

    glow.setColorAt(
        0.0,
        glowCenter
    );

    glow.setColorAt(
        1.0,
        glowEdge
    );

    painter.setPen(
        Qt::NoPen
    );

    painter.setBrush(
        glow
    );

    painter.drawEllipse(
        QRectF(
            69.0,
            87.0,
            174.0,
            174.0
        )
    );

    // Network links.
    QPen linkPen(
        accent,
        3.0,
        Qt::SolidLine,
        Qt::RoundCap,
        Qt::RoundJoin
    );

    painter.setPen(
        linkPen
    );

    painter.drawLine(
        QPointF(111.0, 208.0),
        QPointF(156.0, 173.0)
    );

    painter.drawLine(
        QPointF(201.0, 208.0),
        QPointF(156.0, 173.0)
    );

    painter.drawLine(
        QPointF(156.0, 173.0),
        QPointF(156.0, 126.0)
    );

    // Three server racks.
    const QList<QRectF> serverRects = {
        QRectF(111.0, 137.0, 90.0, 23.0),
        QRectF(111.0, 169.0, 90.0, 23.0),
        QRectF(111.0, 201.0, 90.0, 23.0)
    };

    for (
        int index = 0;
        index < serverRects.size();
        ++index
    )
    {
        painter.setPen(
            QPen(
                accent,
                2.0
            )
        );

        painter.setBrush(
            panel
        );

        painter.drawRoundedRect(
            serverRects[index],
            6.0,
            6.0
        );

        painter.setPen(
            Qt::NoPen
        );

        painter.setBrush(
            index == 1
                ? amber
                : green
        );

        painter.drawEllipse(
            QPointF(
                serverRects[index].right() - 14.0,
                serverRects[index].center().y()
            ),
            3.6,
            3.6
        );
    }

    // Network nodes.
    const QList<QPointF> nodes = {
        QPointF(111.0, 208.0),
        QPointF(201.0, 208.0),
        QPointF(156.0, 126.0)
    };

    painter.setPen(
        QPen(
            panelSecondary,
            3.0
        )
    );

    painter.setBrush(
        accent
    );

    for (
        const QPointF &node :
        nodes
    )
    {
        painter.drawEllipse(
            node,
            7.0,
            7.0
        );
    }

    // Warning badge.
    QPainterPath warning;

    warning.moveTo(
        156.0,
        236.0
    );

    warning.lineTo(
        134.0,
        273.0
    );

    warning.lineTo(
        178.0,
        273.0
    );

    warning.closeSubpath();

    painter.setPen(
        QPen(
            amber,
            2.5
        )
    );

    QColor warningFill =
        amber;

    warningFill.setAlpha(
        m_lightTheme ? 28 : 40
    );

    painter.setBrush(
        warningFill
    );

    painter.drawPath(
        warning
    );

    painter.setPen(
        QPen(
            amber,
            3.0,
            Qt::SolidLine,
            Qt::RoundCap
        )
    );

    painter.drawLine(
        QPointF(156.0, 247.0),
        QPointF(156.0, 259.0)
    );

    painter.setPen(
        Qt::NoPen
    );

    painter.setBrush(
        amber
    );

    painter.drawEllipse(
        QPointF(156.0, 266.0),
        2.3,
        2.3
    );

    painter.setPen(
        primaryText
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            18,
            QFont::Bold
        )
    );

    painter.drawText(
        QRectF(
            72.0,
            298.0,
            168.0,
            34.0
        ),
        Qt::AlignCenter,
        "ATHAR"
    );

    // Main title area.
    painter.setPen(
        accent
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
            310.0,
            62.0,
            395.0,
            24.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        "SYSTEM RELIABILITY LABORATORY"
    );

    painter.setPen(
        primaryText
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            27,
            QFont::Bold
        )
    );

    painter.drawText(
        QRectF(
            307.0,
            94.0,
            410.0,
            48.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        "ATHAR FAULT LAB 2"
    );

    painter.setPen(
        secondaryText
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            11,
            QFont::Normal
        )
    );

    painter.drawText(
        QRectF(
            310.0,
            145.0,
            390.0,
            29.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        "Website Fault Simulation Laboratory"
    );

    painter.setPen(
        secondaryText
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            10,
            QFont::Normal
        )
    );

    painter.drawText(
        QRectF(
            310.0,
            208.0,
            390.0,
            26.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        statusText()
    );

    painter.setPen(
        primaryText
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
            630.0,
            208.0,
            70.0,
            26.0
        ),
        Qt::AlignRight |
            Qt::AlignVCenter,
        QString::number(m_progress) + "%"
    );

    const QRectF progressTrack(
        310.0,
        246.0,
        390.0,
        9.0
    );

    painter.setPen(
        Qt::NoPen
    );

    painter.setBrush(
        border
    );

    painter.drawRoundedRect(
        progressTrack,
        4.5,
        4.5
    );

    const qreal fillWidth =
        progressTrack.width() *
        static_cast<qreal>(m_progress) /
        100.0;

    if (fillWidth > 0.0)
    {
        QLinearGradient progressGradient(
            progressTrack.topLeft(),
            progressTrack.topRight()
        );

        progressGradient.setColorAt(
            0.0,
            accent
        );

        progressGradient.setColorAt(
            1.0,
            green
        );

        painter.setBrush(
            progressGradient
        );

        painter.drawRoundedRect(
            QRectF(
                progressTrack.left(),
                progressTrack.top(),
                fillWidth,
                progressTrack.height()
            ),
            4.5,
            4.5
        );
    }

    painter.setPen(
        border
    );

    painter.drawLine(
        QPointF(
            310.0,
            296.0
        ),
        QPointF(
            700.0,
            296.0
        )
    );

    painter.setPen(
        secondaryText
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            8,
            QFont::Normal
        )
    );

    painter.drawText(
        QRectF(
            310.0,
            310.0,
            230.0,
            24.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        "Version 2.0"
    );

    painter.drawText(
        QRectF(
            470.0,
            310.0,
            230.0,
            24.0
        ),
        Qt::AlignRight |
            Qt::AlignVCenter,
        "abdulaziz alyousef"
    );

    // Tiny animated activity indicators.
    for (
        int index = 0;
        index < 3;
        ++index
    )
    {
        const int threshold =
            (m_progress / 8 + index) % 3;

        QColor dotColor =
            index == threshold
                ? green
                : border;

        painter.setPen(
            Qt::NoPen
        );

        painter.setBrush(
            dotColor
        );

        painter.drawEllipse(
            QPointF(
                324.0 + index * 13.0,
                354.0
            ),
            3.0,
            3.0
        );
    }

    painter.setPen(
        secondaryText
    );

    painter.setFont(
        QFont(
            "Segoe UI",
            8,
            QFont::Normal
        )
    );

    painter.drawText(
        QRectF(
            370.0,
            342.0,
            330.0,
            24.0
        ),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        "Initializing local simulation environment"
    );
}
