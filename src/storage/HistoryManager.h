#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QObject>
#include <QString>
#include <QVector>

struct SimulationHistoryRecord
{
    int id = 0;

    QString dateTime;

    int totalRequests = 0;
    int processedRequests = 0;
    int successfulRequests = 0;
    int failedRequests = 0;

    double successRate = 0.0;
    double averageLatency = 0.0;

    QString faultSummary;
    QString serviceHealthJson;
};

class HistoryManager : public QObject
{
    Q_OBJECT

public:
    explicit HistoryManager(
        QObject *parent = nullptr
    );

    ~HistoryManager();

    bool initialize();

    bool addSimulation(
        int totalRequests,
        int processedRequests,
        int successfulRequests,
        int failedRequests,
        double successRate,
        double averageLatency,
        const QString &faultSummary = QString(),
        const QString &serviceHealthJson = QString()
    );

    QVector<SimulationHistoryRecord> history() const;

    bool clearHistory();

    QString lastError() const;

private:
    QString databasePath() const;

    bool ensureColumn(
        const QString &columnName,
        const QString &definition
    );

    QString m_connectionName;

    mutable QString m_lastError;
};

#endif