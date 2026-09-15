#include "ReportsPanel.h"
#include "UiLanguage.h"

#include <QApplication>
#include <QColor>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFont>
#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QList>
#include <QPageLayout>
#include <QPageSize>
#include <QPainter>
#include <QPdfWriter>
#include <QPushButton>
#include <QScrollArea>
#include <QSizePolicy>
#include <QStringList>
#include <QStyle>
#include <QVBoxLayout>

ReportsPanel::ReportsPanel(
    QWidget *parent
)
    : QWidget(parent),
      m_runNumber(0),
      m_totalRequests(0),
      m_processedRequests(0),
      m_successfulRequests(0),
      m_failedRequests(0),
      m_successRate(0.0),
      m_avgLatencyMs(0.0),
      m_reportCard(nullptr),
      m_sourceLabel(nullptr),
      m_runValue(nullptr),
      m_dateValue(nullptr),
      m_totalValue(nullptr),
      m_processedValue(nullptr),
      m_successValue(nullptr),
      m_failedValue(nullptr),
      m_successRateValue(nullptr),
      m_avgLatencyValue(nullptr),
      m_faultSummaryValue(nullptr),
      m_serviceHealthValue(nullptr),
      m_notesValue(nullptr),
      m_exportStatus(nullptr),
      m_pngButton(nullptr),
      m_jpgButton(nullptr),
      m_pdfButton(nullptr)
{
    setObjectName("page");

    QVBoxLayout *rootLayout =
        new QVBoxLayout(this);

    rootLayout->setContentsMargins(
        35,
        30,
        35,
        30
    );

    rootLayout->setSpacing(18);

    QLabel *title =
        new QLabel("Reports");

    title->setObjectName("pageTitle");

    QLabel *description =
        new QLabel(
            "Generate a professional simulation report with fault and service-health details."
        );

    description->setObjectName(
        "pageDescription"
    );

    description->setWordWrap(true);

    rootLayout->addWidget(title);
    rootLayout->addWidget(description);

    QScrollArea *scrollArea =
        new QScrollArea;

    scrollArea->setFrameShape(
        QFrame::NoFrame
    );

    scrollArea->setWidgetResizable(
        true
    );

    scrollArea->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAsNeeded
    );

    scrollArea->setVerticalScrollBarPolicy(
        Qt::ScrollBarAsNeeded
    );

    QWidget *content =
        new QWidget;

    content->setObjectName("page");

    content->setMinimumWidth(900);

    QVBoxLayout *contentLayout =
        new QVBoxLayout(content);

    contentLayout->setContentsMargins(
        2,
        2,
        8,
        8
    );

    contentLayout->setSpacing(18);

    m_reportCard =
        new QFrame;

    m_reportCard->setObjectName("card");

    QVBoxLayout *reportLayout =
        new QVBoxLayout(m_reportCard);

    reportLayout->setContentsMargins(
        28,
        24,
        28,
        24
    );

    reportLayout->setSpacing(18);

    QHBoxLayout *reportHeader =
        new QHBoxLayout;

    QVBoxLayout *reportHeaderText =
        new QVBoxLayout;

    QLabel *reportTitle =
        new QLabel(
            "Simulation Report"
        );

    reportTitle->setObjectName(
        "sectionTitle"
    );

    m_sourceLabel =
        new QLabel(
            "No completed simulation selected."
        );

    m_sourceLabel->setObjectName(
        "pageDescription"
    );

    m_sourceLabel->setWordWrap(true);

    reportHeaderText->addWidget(
        reportTitle
    );

    reportHeaderText->addWidget(
        m_sourceLabel
    );

    QLabel *brand =
        new QLabel(
            "ATHAR FAULT LAB 2"
        );

    brand->setObjectName(
        "reportBrand"
    );

    brand->setAlignment(
        Qt::AlignCenter
    );

    brand->setMinimumSize(
        210,
        70
    );

    reportHeader->addLayout(
        reportHeaderText,
        1
    );

    reportHeader->addWidget(
        brand
    );

    reportLayout->addLayout(
        reportHeader
    );

    QGridLayout *metrics =
        new QGridLayout;

    metrics->setHorizontalSpacing(55);
    metrics->setVerticalSpacing(14);
    metrics->setColumnStretch(0, 1);
    metrics->setColumnStretch(1, 1);

    auto addMetric =
        [&metrics](
            const QString &labelText,
            QLabel **valueOutput,
            int row,
            int column
        )
        {
            QWidget *container =
                new QWidget;

            container->setMinimumWidth(300);

            QVBoxLayout *layout =
                new QVBoxLayout(container);

            layout->setContentsMargins(
                0,
                0,
                0,
                0
            );

            layout->setSpacing(5);

            QLabel *label =
                new QLabel(labelText);

            label->setObjectName(
                "fieldLabel"
            );

            QLabel *value =
                new QLabel("-");

            value->setObjectName(
                "reportValue"
            );

            value->setMinimumWidth(250);
            value->setSizePolicy(
                QSizePolicy::Expanding,
                QSizePolicy::Preferred
            );

            value->setTextInteractionFlags(
                Qt::TextSelectableByMouse
            );

            layout->addWidget(label);
            layout->addWidget(value);

            metrics->addWidget(
                container,
                row,
                column
            );

            if (valueOutput)
            {
                *valueOutput = value;
            }
        };

    addMetric(
        "Run Number",
        &m_runValue,
        0,
        0
    );

    addMetric(
        "Date / Time",
        &m_dateValue,
        0,
        1
    );

    addMetric(
        "Total Requests",
        &m_totalValue,
        1,
        0
    );

    addMetric(
        "Processed",
        &m_processedValue,
        1,
        1
    );

    addMetric(
        "Successful",
        &m_successValue,
        2,
        0
    );

    addMetric(
        "Failed",
        &m_failedValue,
        2,
        1
    );

    addMetric(
        "Success Rate",
        &m_successRateValue,
        3,
        0
    );

    addMetric(
        "Avg. Latency",
        &m_avgLatencyValue,
        3,
        1
    );

    reportLayout->addLayout(metrics);

    QLabel *faultTitle =
        new QLabel("Fault Summary");

    faultTitle->setObjectName(
        "fieldLabel"
    );

    m_faultSummaryValue =
        new QLabel(
            "No active faults."
        );

    m_faultSummaryValue->setObjectName(
        "reportFaultBox"
    );

    m_faultSummaryValue->setWordWrap(
        true
    );

    reportLayout->addWidget(faultTitle);
    reportLayout->addWidget(
        m_faultSummaryValue
    );

    QLabel *serviceTitle =
        new QLabel("Service Health");

    serviceTitle->setObjectName(
        "fieldLabel"
    );

    m_serviceHealthValue =
        new QLabel(
            "No service-health data."
        );

    m_serviceHealthValue->setObjectName(
        "reportCodeBox"
    );

    m_serviceHealthValue->setWordWrap(
        true
    );

    m_serviceHealthValue->setTextInteractionFlags(
        Qt::TextSelectableByMouse
    );

    reportLayout->addWidget(serviceTitle);
    reportLayout->addWidget(
        m_serviceHealthValue
    );

    QLabel *notesTitle =
        new QLabel("Notes");

    notesTitle->setObjectName(
        "fieldLabel"
    );

    m_notesValue =
        new QLabel(
            "No additional notes."
        );

    m_notesValue->setObjectName(
        "reportInfoBox"
    );

    m_notesValue->setWordWrap(true);

    reportLayout->addWidget(notesTitle);
    reportLayout->addWidget(m_notesValue);

    contentLayout->addWidget(
        m_reportCard
    );

    QFrame *exportCard =
        new QFrame;

    exportCard->setObjectName("card");

    QVBoxLayout *exportRoot =
        new QVBoxLayout(exportCard);

    exportRoot->setContentsMargins(
        18,
        14,
        18,
        14
    );

    exportRoot->setSpacing(10);

    QHBoxLayout *exportLayout =
        new QHBoxLayout;

    QLabel *exportLabel =
        new QLabel("Export report");

    exportLabel->setObjectName(
        "fieldLabel"
    );

    m_pngButton =
        new QPushButton(
            "Export PNG"
        );

    m_pngButton->setObjectName(
        "primaryButton"
    );

    m_jpgButton =
        new QPushButton(
            "Export JPG"
        );

    m_jpgButton->setObjectName(
        "secondaryButton"
    );

    m_pdfButton =
        new QPushButton(
            "Export PDF"
        );

    m_pdfButton->setObjectName(
        "secondaryButton"
    );

    exportLayout->addWidget(exportLabel);
    exportLayout->addStretch();
    exportLayout->addWidget(m_pngButton);
    exportLayout->addWidget(m_jpgButton);
    exportLayout->addWidget(m_pdfButton);

    exportRoot->addLayout(exportLayout);

    m_exportStatus =
        new QLabel(
            "Ready to export this report."
        );

    m_exportStatus->setObjectName(
        "reportStatus"
    );

    m_exportStatus->setWordWrap(true);

    exportRoot->addWidget(
        m_exportStatus
    );

    contentLayout->addWidget(
        exportCard
    );

    contentLayout->addStretch();

    scrollArea->setWidget(content);

    rootLayout->addWidget(
        scrollArea,
        1
    );

    connect(
        m_pngButton,
        &QPushButton::clicked,
        this,
        &ReportsPanel::exportPng
    );

    connect(
        m_jpgButton,
        &QPushButton::clicked,
        this,
        &ReportsPanel::exportJpg
    );

    connect(
        m_pdfButton,
        &QPushButton::clicked,
        this,
        &ReportsPanel::exportPdf
    );

    setReportData(
        0,
        "No completed run",
        0,
        0,
        0,
        0,
        0.0,
        0.0,
        "Complete a simulation first.",
        "",
        ""
    );
}

void ReportsPanel::setReportData(
    int runNumber,
    const QString &dateTime,
    int totalRequests,
    int processedRequests,
    int successfulRequests,
    int failedRequests,
    double successRate,
    double avgLatencyMs,
    const QString &notes,
    const QString &faultSummary,
    const QString &serviceHealthJson
)
{
    m_runNumber = runNumber;
    m_dateTime = dateTime;
    m_totalRequests = totalRequests;
    m_processedRequests = processedRequests;
    m_successfulRequests = successfulRequests;
    m_failedRequests = failedRequests;
    m_successRate = successRate;
    m_avgLatencyMs = avgLatencyMs;
    m_notes = notes;
    m_faultSummary = faultSummary;
    m_serviceHealthJson = serviceHealthJson;

    m_runValue->setText(
        runNumber > 0
            ? QString("#%1").arg(runNumber)
            : "-"
    );

    m_dateValue->setText(dateTime);
    m_totalValue->setText(
        QString::number(totalRequests)
    );
    m_processedValue->setText(
        QString::number(processedRequests)
    );
    m_successValue->setText(
        QString::number(successfulRequests)
    );
    m_failedValue->setText(
        QString::number(failedRequests)
    );
    m_successRateValue->setText(
        QString::number(
            successRate,
            'f',
            1
        ) + "%"
    );
    m_avgLatencyValue->setText(
        QString::number(
            avgLatencyMs,
            'f',
            1
        ) + " ms"
    );

    m_faultSummaryValue->setText(
        faultSummary.trimmed().isEmpty()
            ? (
                  runNumber > 0
                      ? "No active faults at simulation completion."
                      : "No report data."
              )
            : faultSummary
    );

    QString healthText =
        serviceHealthText();

    m_serviceHealthValue->setText(
        healthText.isEmpty()
            ? "No service-health data."
            : healthText
    );

    m_notesValue->setText(
        notes.isEmpty()
            ? "No additional notes."
            : notes
    );

    m_sourceLabel->setText(
        reportSourceText()
    );

    bool hasReport =
        runNumber > 0;

    m_pngButton->setEnabled(hasReport);
    m_jpgButton->setEnabled(hasReport);
    m_pdfButton->setEnabled(hasReport);

    setExportStatus(
        hasReport
            ? "Ready to export this report."
            : "Complete a simulation before exporting.",
        hasReport
    );
}

QString ReportsPanel::serviceHealthText() const
{
    if (m_serviceHealthJson.trimmed().isEmpty())
    {
        return QString();
    }

    QJsonParseError parseError;

    QJsonDocument document =
        QJsonDocument::fromJson(
            m_serviceHealthJson.toUtf8(),
            &parseError
        );

    if (
        parseError.error !=
            QJsonParseError::NoError ||
        !document.isArray()
    )
    {
        return m_serviceHealthJson;
    }

    QStringList lines;

    QJsonArray array =
        document.array();

    for (
        const QJsonValue &value :
        array
    )
    {
        if (!value.isObject())
        {
            continue;
        }

        QJsonObject object =
            value.toObject();

        QString name =
            object.value("name")
                .toString(
                    "Unknown Service"
                );

        QString status =
            object.value("status")
                .toString("UNKNOWN");

        int totalWorkers =
            object.value("totalWorkers")
                .toInt();

        int activeWorkers =
            object.value("activeWorkers")
                .toInt();

        double baseLatency =
            object.value("baseLatency")
                .toDouble();

        double effectiveLatency =
            object.value("effectiveLatency")
                .toDouble();

        double failureRate =
            object.value("failureRate")
                .toDouble();

        lines <<
            QString(
                "%1 — %2 | Workers %3/%4 | Latency %5 → %6 ms | Failure %7%"
            )
                .arg(name)
                .arg(status)
                .arg(activeWorkers)
                .arg(totalWorkers)
                .arg(
                    baseLatency,
                    0,
                    'f',
                    1
                )
                .arg(
                    effectiveLatency,
                    0,
                    'f',
                    1
                )
                .arg(
                    failureRate,
                    0,
                    'f',
                    1
                );
    }

    return lines.join("\n");
}

QString ReportsPanel::reportSourceText() const
{
    if (m_runNumber <= 0)
    {
        return
            "No completed simulation selected.";
    }

    if (
        m_notes.contains(
            "selected manually",
            Qt::CaseInsensitive
        )
    )
    {
        return QString(
            "Selected historical run #%1 from SQLite History"
        ).arg(m_runNumber);
    }

    return QString(
        "Latest completed run #%1 from SQLite History"
    ).arg(m_runNumber);
}

void ReportsPanel::exportPng()
{
    saveAsImage(
        "PNG",
        "PNG Image (*.png)",
        -1
    );
}

void ReportsPanel::exportJpg()
{
    saveAsImage(
        "JPG",
        "JPEG Image (*.jpg *.jpeg)",
        95
    );
}

void ReportsPanel::exportPdf()
{
    if (m_runNumber <= 0)
    {
        setExportStatus(
            "There is no completed simulation report to export.",
            false
        );
        return;
    }

    QString defaultName =
        QString(
            "Athar_Run_%1_%2.pdf"
        )
            .arg(m_runNumber)
            .arg(
                QDateTime::currentDateTime()
                    .toString(
                        "yyyyMMdd_HHmmss"
                    )
            );

    QString filePath =
        QFileDialog::getSaveFileName(
            this,
            UiLanguage::text("Save Report as PDF"),
            defaultName,
            "PDF Document (*.pdf)"
        );

    if (filePath.isEmpty())
    {
        return;
    }

    if (
        !filePath.endsWith(
            ".pdf",
            Qt::CaseInsensitive
        )
    )
    {
        filePath += ".pdf";
    }

    QPdfWriter writer(filePath);

    writer.setTitle(
        UiLanguage::isArabic()
            ? QString::fromUtf8(u8"أثر - التشغيل المحدد #%1").arg(m_runNumber)
            : QString("Athar Fault Lab 2 - Selected Run #%1").arg(m_runNumber)
    );

    writer.setCreator(
        "Athar Fault Lab 2"
    );

    writer.setPageSize(
        QPageSize(QPageSize::A4)
    );

    writer.setPageOrientation(
        QPageLayout::Landscape
    );

    writer.setResolution(150);

    QPainter painter(&writer);

    if (!painter.isActive())
    {
        setExportStatus(
            "PDF export failed. The destination file could not be created.",
            false
        );
        return;
    }

    QImage image =
        buildReportImage();

    QRect pageRect =
        painter.viewport();

    QSize scaledSize =
        image.size();

    scaledSize.scale(
        pageRect.size(),
        Qt::KeepAspectRatio
    );

    QRect targetRect(
        pageRect.x() +
            (
                pageRect.width() -
                scaledSize.width()
            ) /
                2,
        pageRect.y() +
            (
                pageRect.height() -
                scaledSize.height()
            ) /
                2,
        scaledSize.width(),
        scaledSize.height()
    );

    painter.drawImage(
        targetRect,
        image
    );

    painter.end();

    if (
        QFileInfo::exists(filePath) &&
        QFileInfo(filePath).size() > 0
    )
    {
        setExportStatus(
            QString(
                "PDF report saved successfully: %1"
            ).arg(
                QDir::toNativeSeparators(
                    QFileInfo(filePath)
                        .absoluteFilePath()
                )
            ),
            true
        );
    }
    else
    {
        setExportStatus(
            "PDF export failed.",
            false
        );
    }
}

void ReportsPanel::saveAsImage(
    const QString &format,
    const QString &filter,
    int quality
)
{
    if (m_runNumber <= 0)
    {
        setExportStatus(
            "There is no completed simulation report to export.",
            false
        );
        return;
    }

    QString extension =
        format == "PNG"
            ? "png"
            : "jpg";

    QString defaultName =
        QString(
            "Athar_Run_%1_%2.%3"
        )
            .arg(m_runNumber)
            .arg(
                QDateTime::currentDateTime()
                    .toString(
                        "yyyyMMdd_HHmmss"
                    )
            )
            .arg(extension);

    QString filePath =
        QFileDialog::getSaveFileName(
            this,
            UiLanguage::text(
                QString(
                    "Save Report as %1"
                ).arg(format)
            ),
            defaultName,
            filter
        );

    if (filePath.isEmpty())
    {
        return;
    }

    if (
        !filePath.endsWith(
            "." + extension,
            Qt::CaseInsensitive
        )
    )
    {
        filePath +=
            "." + extension;
    }

    QImage image =
        buildReportImage();

    bool saved =
        quality >= 0
            ? image.save(
                  filePath,
                  format.toUtf8()
                      .constData(),
                  quality
              )
            : image.save(
                  filePath,
                  format.toUtf8()
                      .constData()
              );

    if (saved)
    {
        setExportStatus(
            QString(
                "%1 report saved successfully: %2"
            )
                .arg(format)
                .arg(
                    QDir::toNativeSeparators(
                        QFileInfo(filePath)
                            .absoluteFilePath()
                    )
                ),
            true
        );
    }
    else
    {
        setExportStatus(
            QString(
                "%1 export failed."
            ).arg(format),
            false
        );
    }
}

void ReportsPanel::setExportStatus(
    const QString &message,
    bool success
)
{
    if (!m_exportStatus)
    {
        return;
    }

    m_exportStatus->setText(
        message
    );

    m_exportStatus->setObjectName(
        success
            ? "reportStatusSuccess"
            : "reportStatusError"
    );

    m_exportStatus->style()->unpolish(
        m_exportStatus
    );

    m_exportStatus->style()->polish(
        m_exportStatus
    );

    m_exportStatus->update();
}

QImage ReportsPanel::buildReportImage() const
{
    const int width = 1600;
    const int height = 1400;

    QImage image(
        width,
        height,
        QImage::Format_RGB32
    );

    const bool lightTheme =
        qApp &&
        qApp->property("atharTheme")
                .toString() == "light";

    const QColor background(
        lightTheme ? "#f6f8fa" : "#0d1117"
    );
    const QColor panel(
        lightTheme ? "#ffffff" : "#161b22"
    );
    const QColor border(
        lightTheme ? "#d0d7de" : "#30363d"
    );
    const QColor primaryText(
        lightTheme ? "#1f2328" : "#f0f6fc"
    );
    const QColor secondaryText(
        lightTheme ? "#59636e" : "#8b949e"
    );
    const QColor blue(
        lightTheme ? "#0969da" : "#58a6ff"
    );
    const QColor green(
        lightTheme ? "#1a7f37" : "#3fb950"
    );
    const QColor red(
        lightTheme ? "#cf222e" : "#f85149"
    );
    const QColor amber(
        lightTheme ? "#9a6700" : "#d29922"
    );
    const QColor headerBackground(
        lightTheme ? "#ddf4ff" : "#172a46"
    );

    image.fill(background);

    QPainter painter(&image);
    painter.setRenderHint(
        QPainter::Antialiasing,
        true
    );

    painter.setPen(Qt::NoPen);
    painter.setBrush(headerBackground);
    painter.drawRoundedRect(
        QRectF(70, 55, 1460, 120),
        18,
        18
    );

    painter.setPen(primaryText);
    painter.setFont(
        QFont(
            "Segoe UI",
            29,
            QFont::Bold
        )
    );
    painter.drawText(
        QRect(105, 78, 850, 45),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        UiLanguage::text("ATHAR FAULT LAB 2")
    );

    painter.setPen(blue);
    painter.setFont(
        QFont(
            "Segoe UI",
            13,
            QFont::DemiBold
        )
    );
    painter.drawText(
        QRect(105, 125, 850, 28),
        Qt::AlignLeft |
            Qt::AlignVCenter,
        UiLanguage::text("Simulation Analysis Report")
    );

    painter.setPen(secondaryText);
    painter.setFont(
        QFont(
            "Segoe UI",
            11,
            QFont::DemiBold
        )
    );
    painter.drawText(
        QRect(1120, 78, 350, 28),
        Qt::AlignRight |
            Qt::AlignVCenter,
        UiLanguage::isArabic()
            ? QString::fromUtf8(u8"التشغيل المحدد #%1").arg(m_runNumber)
            : QString("Selected Run #%1").arg(m_runNumber)
    );
    painter.drawText(
        QRect(1000, 115, 470, 28),
        Qt::AlignRight |
            Qt::AlignVCenter,
        m_dateTime
    );

    painter.setPen(QPen(border, 2));
    painter.setBrush(panel);
    painter.drawRoundedRect(
        QRectF(70, 210, 1460, 390),
        16,
        16
    );

    painter.setPen(primaryText);
    painter.setFont(
        QFont(
            "Segoe UI",
            20,
            QFont::Bold
        )
    );
    painter.drawText(
        QRect(105, 240, 600, 36),
        UiLanguage::text("Simulation Metrics")
    );

    struct Metric
    {
        QString label;
        QString value;
        QColor color;
    };

    QList<Metric> metrics = {
        {
            UiLanguage::text("TOTAL REQUESTS"),
            QString::number(m_totalRequests),
            primaryText
        },
        {
            UiLanguage::text("PROCESSED"),
            QString::number(m_processedRequests),
            primaryText
        },
        {
            UiLanguage::text("SUCCESSFUL"),
            QString::number(m_successfulRequests),
            primaryText
        },
        {
            UiLanguage::text("FAILED"),
            QString::number(m_failedRequests),
            m_failedRequests > 0
                ? red
                : primaryText
        },
        {
            UiLanguage::text("SUCCESS RATE"),
            QString::number(
                m_successRate,
                'f',
                1
            ) + "%",
            m_successRate >= 95.0
                ? green
                : (
                      m_successRate >= 70.0
                          ? amber
                          : red
                  )
        },
        {
            UiLanguage::text("AVG. LATENCY"),
            QString::number(
                m_avgLatencyMs,
                'f',
                1
            ) + " ms",
            primaryText
        }
    };

    const int startX = 110;
    const int startY = 315;
    const int columnWidth = 460;
    const int rowHeight = 135;

    for (
        int index = 0;
        index < metrics.size();
        ++index
    )
    {
        int row = index / 3;
        int column = index % 3;
        int x = startX + column * columnWidth;
        int y = startY + row * rowHeight;

        painter.setPen(secondaryText);
        painter.setFont(
            QFont(
                "Segoe UI",
                10,
                QFont::DemiBold
            )
        );
        painter.drawText(
            QRect(x, y, 350, 25),
            metrics[index].label
        );

        painter.setPen(
            metrics[index].color
        );
        painter.setFont(
            QFont(
                "Segoe UI",
                23,
                QFont::Bold
            )
        );
        painter.drawText(
            QRect(x, y + 35, 350, 48),
            metrics[index].value
        );
    }

    painter.setPen(QPen(border, 2));
    painter.setBrush(panel);
    painter.drawRoundedRect(
        QRectF(70, 630, 1460, 180),
        16,
        16
    );

    painter.setPen(amber);
    painter.setFont(
        QFont(
            "Segoe UI",
            17,
            QFont::Bold
        )
    );
    painter.drawText(
        QRect(105, 660, 500, 35),
        UiLanguage::text("Fault Summary")
    );

    painter.setPen(primaryText);
    painter.setFont(
        QFont("Segoe UI", 12)
    );
    painter.drawText(
        QRect(105, 705, 1360, 80),
        Qt::AlignLeft |
            Qt::AlignTop |
            Qt::TextWordWrap,
        UiLanguage::text(
            m_faultSummary.isEmpty()
                ? QString("No active faults at simulation completion.")
                : m_faultSummary
        )
    );

    painter.setPen(QPen(border, 2));
    painter.setBrush(panel);
    painter.drawRoundedRect(
        QRectF(70, 840, 1460, 260),
        16,
        16
    );

    painter.setPen(blue);
    painter.setFont(
        QFont(
            "Segoe UI",
            17,
            QFont::Bold
        )
    );
    painter.drawText(
        QRect(105, 870, 500, 35),
        UiLanguage::text("Service Health")
    );

    painter.setPen(primaryText);
    painter.setFont(
        QFont("Consolas", 11)
    );
    painter.drawText(
        QRect(105, 915, 1360, 155),
        Qt::AlignLeft |
            Qt::AlignTop |
            Qt::TextWordWrap,
        UiLanguage::text(
            serviceHealthText().isEmpty()
                ? QString("No service-health data.")
                : serviceHealthText()
        )
    );

    painter.setPen(QPen(border, 2));
    painter.setBrush(panel);
    painter.drawRoundedRect(
        QRectF(70, 1130, 1460, 165),
        16,
        16
    );

    painter.setPen(secondaryText);
    painter.setFont(
        QFont(
            "Segoe UI",
            11,
            QFont::Bold
        )
    );
    painter.drawText(
        QRect(105, 1160, 300, 28),
        UiLanguage::text("NOTES")
    );

    painter.setPen(primaryText);
    painter.setFont(
        QFont("Segoe UI", 11)
    );
    painter.drawText(
        QRect(105, 1198, 1360, 68),
        Qt::AlignLeft |
            Qt::AlignTop |
            Qt::TextWordWrap,
        UiLanguage::text(
            m_notes.isEmpty()
                ? QString("No additional notes.")
                : m_notes
        )
    );

    painter.setPen(secondaryText);
    painter.setFont(
        QFont("Segoe UI", 9)
    );
    painter.drawText(
        QRect(70, 1330, 1460, 30),
        Qt::AlignCenter,
        UiLanguage::text(
            "Athar Fault Lab 2 | Made by abdulaziz alyousef"
        )
    );

    return image;
}
