#include "Service.h"

#include <QStringList>

#include <algorithm>
#include <cmath>

Service::Service()
    : m_totalWorkers(1),
      m_failedWorkers(0),
      m_baseLatencyMs(1.0),
      m_failureProbability(0.0),
      m_latencyMultiplier(1.0),
      m_available(true),
      m_trafficMultiplier(1.0),
      m_dnsFailureProbability(0.0),
      m_tlsFailureProbability(0.0),
      m_memoryPressure(0.0),
      m_storagePressure(0.0),
      m_retryMultiplier(1.0),
      m_linkFailureProbability(0.0)
{
}

Service::Service(
    const QString &id,
    const QString &name,
    int totalWorkers,
    double baseLatencyMs
)
    : m_id(id),
      m_name(name),
      m_totalWorkers(
          std::max(
              1,
              totalWorkers
          )
      ),
      m_failedWorkers(0),
      m_baseLatencyMs(
          std::max(
              0.1,
              baseLatencyMs
          )
      ),
      m_failureProbability(0.0),
      m_latencyMultiplier(1.0),
      m_available(true),
      m_trafficMultiplier(1.0),
      m_dnsFailureProbability(0.0),
      m_tlsFailureProbability(0.0),
      m_memoryPressure(0.0),
      m_storagePressure(0.0),
      m_retryMultiplier(1.0),
      m_linkFailureProbability(0.0)
{
}

QString Service::id() const
{
    return m_id;
}

QString Service::name() const
{
    return m_name;
}

int Service::totalWorkers() const
{
    return m_totalWorkers;
}

int Service::failedWorkers() const
{
    return m_failedWorkers;
}

int Service::activeWorkers() const
{
    return std::max(
        0,
        m_totalWorkers -
            m_failedWorkers
    );
}

double Service::baseLatencyMs() const
{
    return m_baseLatencyMs;
}

double Service::failureProbability() const
{
    return m_failureProbability;
}

double Service::latencyMultiplier() const
{
    return m_latencyMultiplier;
}

bool Service::isAvailable() const
{
    return m_available;
}

double Service::trafficMultiplier() const
{
    return m_trafficMultiplier;
}

double Service::dnsFailureProbability() const
{
    return m_dnsFailureProbability;
}

double Service::tlsFailureProbability() const
{
    return m_tlsFailureProbability;
}

double Service::memoryPressure() const
{
    return m_memoryPressure;
}

double Service::storagePressure() const
{
    return m_storagePressure;
}

double Service::retryMultiplier() const
{
    return m_retryMultiplier;
}

double Service::linkFailureProbability() const
{
    return m_linkFailureProbability;
}

void Service::setTotalWorkers(
    int workers
)
{
    m_totalWorkers =
        std::max(
            1,
            workers
        );

    m_failedWorkers =
        std::clamp(
            m_failedWorkers,
            0,
            m_totalWorkers
        );
}

void Service::setFailedWorkers(
    int workers
)
{
    m_failedWorkers =
        std::clamp(
            workers,
            0,
            m_totalWorkers
        );
}

void Service::setBaseLatencyMs(
    double latencyMs
)
{
    m_baseLatencyMs =
        std::max(
            0.1,
            latencyMs
        );
}

void Service::setFailureProbability(
    double probability
)
{
    m_failureProbability =
        clampProbability(
            probability
        );
}

void Service::setLatencyMultiplier(
    double multiplier
)
{
    m_latencyMultiplier =
        std::max(
            1.0,
            multiplier
        );
}

void Service::setAvailable(
    bool available
)
{
    m_available =
        available;
}

void Service::setTrafficMultiplier(
    double multiplier
)
{
    m_trafficMultiplier =
        std::max(
            1.0,
            multiplier
        );
}

void Service::setDnsFailureProbability(
    double probability
)
{
    m_dnsFailureProbability =
        clampProbability(
            probability
        );
}

void Service::setTlsFailureProbability(
    double probability
)
{
    m_tlsFailureProbability =
        clampProbability(
            probability
        );
}

void Service::setMemoryPressure(
    double pressure
)
{
    m_memoryPressure =
        clampProbability(
            pressure
        );
}

void Service::setStoragePressure(
    double pressure
)
{
    m_storagePressure =
        clampProbability(
            pressure
        );
}

void Service::setRetryMultiplier(
    double multiplier
)
{
    m_retryMultiplier =
        std::max(
            1.0,
            multiplier
        );
}

void Service::setLinkFailureProbability(
    double probability
)
{
    m_linkFailureProbability =
        clampProbability(
            probability
        );
}

void Service::clearFaultEffects()
{
    m_available =
        true;

    m_failedWorkers =
        0;

    m_latencyMultiplier =
        1.0;

    m_failureProbability =
        0.0;

    m_trafficMultiplier =
        1.0;

    m_dnsFailureProbability =
        0.0;

    m_tlsFailureProbability =
        0.0;

    m_memoryPressure =
        0.0;

    m_storagePressure =
        0.0;

    m_retryMultiplier =
        1.0;

    m_linkFailureProbability =
        0.0;
}

bool Service::hasActiveFaults() const
{
    return
        !m_available ||
        m_failedWorkers > 0 ||
        m_latencyMultiplier > 1.001 ||
        m_failureProbability > 0.0001 ||
        m_trafficMultiplier > 1.001 ||
        m_dnsFailureProbability > 0.0001 ||
        m_tlsFailureProbability > 0.0001 ||
        m_memoryPressure > 0.0001 ||
        m_storagePressure > 0.0001 ||
        m_retryMultiplier > 1.001 ||
        m_linkFailureProbability > 0.0001;
}

QString Service::activeFaultSummary() const
{
    QStringList faults;

    if (!m_available)
    {
        faults <<
            "Service Down";
    }

    if (
        m_failedWorkers > 0
    )
    {
        faults <<
            QString(
                "Worker Crash: %1 failed"
            )
                .arg(
                    m_failedWorkers
                );
    }

    if (
        m_latencyMultiplier >
        1.001
    )
    {
        faults <<
            QString(
                "Slowdown %1x"
            )
                .arg(
                    m_latencyMultiplier,
                    0,
                    'f',
                    1
                );
    }

    if (
        m_failureProbability >
        0.0001
    )
    {
        faults <<
            QString(
                "Error Spike %1%"
            )
                .arg(
                    m_failureProbability *
                        100.0,
                    0,
                    'f',
                    1
                );
    }

    if (
        m_trafficMultiplier >
        1.001
    )
    {
        faults <<
            QString(
                "Traffic Spike %1x"
            )
                .arg(
                    m_trafficMultiplier,
                    0,
                    'f',
                    1
                );
    }

    if (
        m_dnsFailureProbability >
        0.0001
    )
    {
        faults <<
            QString(
                "DNS Failure %1%"
            )
                .arg(
                    m_dnsFailureProbability *
                        100.0,
                    0,
                    'f',
                    1
                );
    }

    if (
        m_tlsFailureProbability >
        0.0001
    )
    {
        faults <<
            QString(
                "TLS Failure %1%"
            )
                .arg(
                    m_tlsFailureProbability *
                        100.0,
                    0,
                    'f',
                    1
                );
    }

    if (
        m_memoryPressure >
        0.0001
    )
    {
        faults <<
            QString(
                "Memory Pressure %1%"
            )
                .arg(
                    m_memoryPressure *
                        100.0,
                    0,
                    'f',
                    0
                );
    }

    if (
        m_storagePressure >
        0.0001
    )
    {
        faults <<
            QString(
                "Storage Full %1%"
            )
                .arg(
                    m_storagePressure *
                        100.0,
                    0,
                    'f',
                    0
                );
    }

    if (
        m_retryMultiplier >
        1.001
    )
    {
        faults <<
            QString(
                "Retry Storm %1x"
            )
                .arg(
                    m_retryMultiplier,
                    0,
                    'f',
                    1
                );
    }

    if (
        m_linkFailureProbability >
        0.0001
    )
    {
        faults <<
            QString(
                "Link Outage %1%"
            )
                .arg(
                    m_linkFailureProbability *
                        100.0,
                    0,
                    'f',
                    1
                );
    }

    return faults.isEmpty()
        ? "None"
        : faults.join(
              " | "
          );
}

QString Service::healthStatus() const
{
    if (
        !m_available ||
        activeWorkers() <= 0
    )
    {
        return "OFFLINE";
    }

    if (hasActiveFaults())
    {
        return "DEGRADED";
    }

    return "ONLINE";
}

double Service::effectiveLatencyEstimate() const
{
    double value =
        m_baseLatencyMs *
        m_latencyMultiplier;

    value *=
        1.0 +
        1.50 *
            m_memoryPressure;

    value *=
        1.0 +
        0.80 *
            m_storagePressure;

    value *=
        1.0 +
        0.15 *
            std::max(
                0.0,
                m_retryMultiplier -
                    1.0
            );

    value *=
        1.0 +
        0.10 *
            std::max(
                0.0,
                m_trafficMultiplier -
                    1.0
            );

    return value;
}

double Service::effectiveFailureProbability() const
{
    double successProbability =
        1.0;

    auto combineFailure =
        [&successProbability](
            double probability
        )
        {
            probability =
                std::clamp(
                    probability,
                    0.0,
                    1.0
                );

            successProbability *=
                1.0 -
                probability;
        };

    combineFailure(
        m_failureProbability
    );

    combineFailure(
        m_dnsFailureProbability
    );

    combineFailure(
        m_tlsFailureProbability
    );

    combineFailure(
        m_linkFailureProbability
    );

    combineFailure(
        m_memoryPressure *
            0.20
    );

    combineFailure(
        m_storagePressure *
            0.35
    );

    return
        1.0 -
        successProbability;
}

bool Service::processRequest(
    std::mt19937 &random,
    double loadFactor,
    double &latencyMs
) const
{
    if (
        !m_available ||
        activeWorkers() <= 0
    )
    {
        return false;
    }

    std::uniform_real_distribution<double>
        probabilityDistribution(
            0.0,
            1.0
        );

    std::uniform_real_distribution<double>
        jitterDistribution(
            0.92,
            1.12
        );

    double overloadFailure =
        0.0;

    if (
        loadFactor >
        1.0
    )
    {
        overloadFailure =
            std::min(
                0.45,
                (
                    loadFactor -
                    1.0
                ) *
                    0.10
            );
    }

    double successProbability =
        1.0;

    auto combineFailure =
        [&successProbability](
            double probability
        )
        {
            probability =
                std::clamp(
                    probability,
                    0.0,
                    1.0
                );

            successProbability *=
                1.0 -
                probability;
        };

    combineFailure(
        m_failureProbability
    );

    combineFailure(
        m_dnsFailureProbability
    );

    combineFailure(
        m_tlsFailureProbability
    );

    combineFailure(
        m_linkFailureProbability
    );

    combineFailure(
        m_memoryPressure *
            0.20
    );

    combineFailure(
        m_storagePressure *
            0.35
    );

    combineFailure(
        overloadFailure
    );

    double latencyMultiplierFromLoad =
        1.0;

    if (
        loadFactor >
        0.70
    )
    {
        latencyMultiplierFromLoad +=
            (
                loadFactor -
                0.70
            ) *
            0.45;
    }

    latencyMs +=
        effectiveLatencyEstimate() *
        latencyMultiplierFromLoad *
        jitterDistribution(
            random
        );

    double roll =
        probabilityDistribution(
            random
        );

    return
        roll <
        successProbability;
}

double Service::clampProbability(
    double value
)
{
    return std::clamp(
        value,
        0.0,
        1.0
    );
}