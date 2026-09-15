#ifndef SERVICE_H
#define SERVICE_H

#include <QString>

#include <random>

class Service
{
public:
    Service();

    Service(
        const QString &id,
        const QString &name,
        int totalWorkers,
        double baseLatencyMs
    );

    QString id() const;
    QString name() const;

    int totalWorkers() const;
    int failedWorkers() const;
    int activeWorkers() const;

    double baseLatencyMs() const;
    double failureProbability() const;
    double latencyMultiplier() const;

    bool isAvailable() const;

    double trafficMultiplier() const;
    double dnsFailureProbability() const;
    double tlsFailureProbability() const;
    double memoryPressure() const;
    double storagePressure() const;
    double retryMultiplier() const;
    double linkFailureProbability() const;

    void setTotalWorkers(
        int workers
    );

    void setFailedWorkers(
        int workers
    );

    void setBaseLatencyMs(
        double latencyMs
    );

    void setFailureProbability(
        double probability
    );

    void setLatencyMultiplier(
        double multiplier
    );

    void setAvailable(
        bool available
    );

    void setTrafficMultiplier(
        double multiplier
    );

    void setDnsFailureProbability(
        double probability
    );

    void setTlsFailureProbability(
        double probability
    );

    void setMemoryPressure(
        double pressure
    );

    void setStoragePressure(
        double pressure
    );

    void setRetryMultiplier(
        double multiplier
    );

    void setLinkFailureProbability(
        double probability
    );

    void clearFaultEffects();

    bool hasActiveFaults() const;

    QString activeFaultSummary() const;

    QString healthStatus() const;

    double effectiveLatencyEstimate() const;

    double effectiveFailureProbability() const;

    bool processRequest(
        std::mt19937 &random,
        double loadFactor,
        double &latencyMs
    ) const;

private:
    static double clampProbability(
        double value
    );

    QString m_id;
    QString m_name;

    int m_totalWorkers;
    int m_failedWorkers;

    double m_baseLatencyMs;
    double m_failureProbability;
    double m_latencyMultiplier;

    bool m_available;

    double m_trafficMultiplier;
    double m_dnsFailureProbability;
    double m_tlsFailureProbability;
    double m_memoryPressure;
    double m_storagePressure;
    double m_retryMultiplier;
    double m_linkFailureProbability;
};

#endif