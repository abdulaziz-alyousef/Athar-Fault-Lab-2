#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QVector>
#include <QWidget>

class QLabel;
class QVBoxLayout;
class SimulationEngine;

class Dashboard : public QWidget
{
public:
    explicit Dashboard(
        SimulationEngine *engine,
        QWidget *parent = nullptr
    );

    QLabel *statusLabel() const;
    QLabel *totalRequestsLabel() const;
    QLabel *successRateLabel() const;
    QLabel *failedRequestsLabel() const;
    QLabel *averageLatencyLabel() const;

private:
    QWidget *createMetricCard(
        const QString &title,
        const QString &value,
        const QString &description,
        QLabel **valueOutput
    );

    void rebuildServiceHealth();

    SimulationEngine *m_engine;

    QLabel *m_statusLabel;
    QLabel *m_totalRequestsLabel;
    QLabel *m_successRateLabel;
    QLabel *m_failedRequestsLabel;
    QLabel *m_averageLatencyLabel;

    QVBoxLayout *m_serviceRowsLayout;
};

#endif
