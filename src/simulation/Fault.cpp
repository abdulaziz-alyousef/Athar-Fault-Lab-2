#include "Fault.h"

Fault::Fault()
    : m_type(
          FaultType::WorkerCrash
      ),
      m_severity(
          1.0
      )
{
}

Fault::Fault(
    FaultType type,
    const QString &serviceId,
    double severity
)
    : m_type(
          type
      ),
      m_serviceId(
          serviceId
      ),
      m_severity(
          severity
      )
{
}

FaultType Fault::type() const
{
    return m_type;
}

QString Fault::serviceId() const
{
    return m_serviceId;
}

double Fault::severity() const
{
    return m_severity;
}

QString Fault::name() const
{
    return typeName(
        m_type
    );
}

QString Fault::typeName(
    FaultType type
)
{
    switch (type)
    {
        case FaultType::WorkerCrash:
            return "Worker Crash";

        case FaultType::ServiceDown:
            return "Service Down";

        case FaultType::Slowdown:
            return "Slowdown";

        case FaultType::ErrorSpike:
            return "Error Spike";

        case FaultType::TrafficSpike:
            return "Traffic Spike";

        case FaultType::DNSFailure:
            return "DNS Failure";

        case FaultType::TLSFailure:
            return "TLS Failure";

        case FaultType::MemoryPressure:
            return "Memory Pressure";

        case FaultType::StorageFull:
            return "Storage Full";

        case FaultType::RetryStorm:
            return "Retry Storm";

        case FaultType::LinkOutage:
            return "Link Outage";
    }

    return "Unknown Fault";
}