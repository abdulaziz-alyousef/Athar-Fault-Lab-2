#ifndef REPORTSPANEL_H
#define REPORTSPANEL_H

#include <QImage>
#include <QString>
#include <QWidget>

class QFrame;
class QLabel;
class QPushButton;

class ReportsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ReportsPanel(
        QWidget *parent = nullptr
    );

    void setReportData(
        int runNumber,
        const QString &dateTime,
        int totalRequests,
        int processedRequests,
        int successfulRequests,
        int failedRequests,
        double successRate,
        double avgLatencyMs,
        const QString &notes = QString(),
        const QString &faultSummary = QString(),
        const QString &serviceHealthJson = QString()
    );

private:
    void exportPng();
    void exportJpg();
    void exportPdf();

    void saveAsImage(
        const QString &format,
        const QString &filter,
        int quality
    );

    QImage buildReportImage() const;

    QString serviceHealthText() const;
    QString reportSourceText() const;

    void setExportStatus(
        const QString &message,
        bool success
    );

    int m_runNumber;
    QString m_dateTime;

    int m_totalRequests;
    int m_processedRequests;
    int m_successfulRequests;
    int m_failedRequests;

    double m_successRate;
    double m_avgLatencyMs;

    QString m_notes;
    QString m_faultSummary;
    QString m_serviceHealthJson;

    QFrame *m_reportCard;

    QLabel *m_sourceLabel;

    QLabel *m_runValue;
    QLabel *m_dateValue;
    QLabel *m_totalValue;
    QLabel *m_processedValue;
    QLabel *m_successValue;
    QLabel *m_failedValue;
    QLabel *m_successRateValue;
    QLabel *m_avgLatencyValue;

    QLabel *m_faultSummaryValue;
    QLabel *m_serviceHealthValue;
    QLabel *m_notesValue;
    QLabel *m_exportStatus;

    QPushButton *m_pngButton;
    QPushButton *m_jpgButton;
    QPushButton *m_pdfButton;
};

#endif