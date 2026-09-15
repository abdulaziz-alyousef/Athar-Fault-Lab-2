#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QTimer>

#include <random>
#include <vector>

#include "Fault.h"
#include "Service.h"

class SimulationEngine : public QObject
{
    Q_OBJECT

public:
    explicit SimulationEngine(
        QObject *parent = nullptr
    );

    void configure(
        int totalRequests,
        int requestsPerSecond,
        int durationSeconds
    );

    void start();
    void stop();
    void reset();

    bool isRunning() const;

    int totalRequests() const;
    int processedRequests() const;
    int successfulRequests() const;
    int failedRequests() const;

    double successRate() const;
    double averageLatency() const;

    const std::vector<Service> &services() const;

    bool updateService(
        const QString &id,
        int workers,
        double latencyMs,
        double failureProbability,
        bool available
    );

    bool updateService(
        const QString &id,
        int totalWorkers,
        int failedWorkers,
        double latencyMs,
        double failureProbability,
        bool available
    );

    void restoreDefaultServices();

    bool injectFault(
        const Fault &fault
    );

    bool recoverService(
        const QString &serviceId
    );

signals:
    void statsUpdated(
        int processed,
        int successful,
        int failed,
        double successRate,
        double averageLatency,
        int progress
    );

    void statusChanged(
        const QString &status
    );

    void servicesChanged();

    void faultInjected(
        const QString &serviceName,
        const QString &faultName
    );

    void serviceRecovered(
        const QString &serviceName
    );

    void simulationFinished();

private slots:
    void simulationTick();

private:
    void createDefaultServices();

    bool processSingleRequest(
        double &latencyMs
    );

    static double severityAsProbability(
        double severity
    );

    QTimer m_timer;

    std::vector<Service> m_services;

    std::mt19937 m_random;

    int m_totalRequests;
    int m_requestsPerSecond;
    int m_durationSeconds;

    int m_processed;
    int m_successful;
    int m_failed;

    double m_totalLatency;

    bool m_running;

    int m_requestsPerTick;
};

#endif