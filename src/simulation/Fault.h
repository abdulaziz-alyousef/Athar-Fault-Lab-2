#ifndef FAULT_H
#define FAULT_H

#include <QString>

enum class FaultType
{
    WorkerCrash,
    ServiceDown,
    Slowdown,
    ErrorSpike,
    TrafficSpike,
    DNSFailure,
    TLSFailure,
    MemoryPressure,
    StorageFull,
    RetryStorm,
    LinkOutage
};

class Fault
{
public:
    Fault();

    Fault(
        FaultType type,
        const QString &serviceId,
        double severity
    );

    FaultType type() const;

    QString serviceId() const;

    double severity() const;

    QString name() const;

    static QString typeName(
        FaultType type
    );

private:
    FaultType m_type;

    QString m_serviceId;

    double m_severity;
};

#endif