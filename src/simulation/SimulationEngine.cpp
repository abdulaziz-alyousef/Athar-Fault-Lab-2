#include "SimulationEngine.h"

#include <algorithm>
#include <chrono>

SimulationEngine::SimulationEngine(
    QObject *parent
)
    : QObject(parent),
      m_random(
          static_cast<unsigned int>(
              std::chrono::steady_clock::now()
                  .time_since_epoch()
                  .count()
          )
      ),
      m_totalRequests(10000),
      m_requestsPerSecond(100),
      m_durationSeconds(60),
      m_processed(0),
      m_successful(0),
      m_failed(0),
      m_totalLatency(0.0),
      m_running(false),
      m_requestsPerTick(1)
{
    m_timer.setInterval(
        50
    );

    connect(
        &m_timer,
        &QTimer::timeout,
        this,
        &SimulationEngine::simulationTick
    );

    createDefaultServices();
}

void SimulationEngine::configure(
    int totalRequests,
    int requestsPerSecond,
    int durationSeconds
)
{
    if (m_running)
    {
        return;
    }

    m_totalRequests =
        std::max(
            1,
            totalRequests
        );

    m_requestsPerSecond =
        std::max(
            1,
            requestsPerSecond
        );

    m_durationSeconds =
        std::max(
            1,
            durationSeconds
        );

    const int ticksPerSecond =
        std::max(
            1,
            1000 /
                m_timer.interval()
        );

    m_requestsPerTick =
        std::max(
            1,
            m_requestsPerSecond /
                ticksPerSecond
        );
}

void SimulationEngine::start()
{
    if (m_running)
    {
        return;
    }

    if (
        m_processed >=
        m_totalRequests
    )
    {
        reset();
    }

    m_running =
        true;

    emit statusChanged(
        "RUNNING"
    );

    m_timer.start();
}

void SimulationEngine::stop()
{
    if (!m_running)
    {
        return;
    }

    m_running =
        false;

    m_timer.stop();

    emit statusChanged(
        "STOPPED"
    );
}

void SimulationEngine::reset()
{
    m_timer.stop();

    m_running =
        false;

    m_processed =
        0;

    m_successful =
        0;

    m_failed =
        0;

    m_totalLatency =
        0.0;

    emit statsUpdated(
        0,
        0,
        0,
        100.0,
        0.0,
        0
    );

    emit statusChanged(
        "READY"
    );
}

bool SimulationEngine::isRunning() const
{
    return m_running;
}

int SimulationEngine::totalRequests() const
{
    return m_totalRequests;
}

int SimulationEngine::processedRequests() const
{
    return m_processed;
}

int SimulationEngine::successfulRequests() const
{
    return m_successful;
}

int SimulationEngine::failedRequests() const
{
    return m_failed;
}

double SimulationEngine::successRate() const
{
    if (
        m_processed <=
        0
    )
    {
        return 100.0;
    }

    return
        static_cast<double>(
            m_successful
        ) /
        static_cast<double>(
            m_processed
        ) *
        100.0;
}

double SimulationEngine::averageLatency() const
{
    if (
        m_successful <=
        0
    )
    {
        return 0.0;
    }

    return
        m_totalLatency /
        static_cast<double>(
            m_successful
        );
}

const std::vector<Service> &
SimulationEngine::services() const
{
    return m_services;
}

bool SimulationEngine::updateService(
    const QString &id,
    int workers,
    double latencyMs,
    double failureProbability,
    bool available
)
{
    if (m_running)
    {
        return false;
    }

    for (
        Service &service :
        m_services
    )
    {
        if (
            service.id() ==
            id
        )
        {
            return updateService(
                id,
                workers,
                service.failedWorkers(),
                latencyMs,
                failureProbability,
                available
            );
        }
    }

    return false;
}

bool SimulationEngine::updateService(
    const QString &id,
    int totalWorkers,
    int failedWorkers,
    double latencyMs,
    double failureProbability,
    bool available
)
{
    if (m_running)
    {
        return false;
    }

    for (
        Service &service :
        m_services
    )
    {
        if (
            service.id() !=
            id
        )
        {
            continue;
        }

        service.setTotalWorkers(
            totalWorkers
        );

        service.setFailedWorkers(
            failedWorkers
        );

        service.setBaseLatencyMs(
            latencyMs
        );

        service.setFailureProbability(
            failureProbability
        );

        service.setAvailable(
            available
        );

        emit servicesChanged();

        return true;
    }

    return false;
}

void SimulationEngine::restoreDefaultServices()
{
    if (m_running)
    {
        return;
    }

    createDefaultServices();

    emit servicesChanged();
}

void SimulationEngine::createDefaultServices()
{
    m_services.clear();

    m_services.emplace_back(
        "gateway",
        "Gateway",
        12,
        4.0
    );

    m_services.emplace_back(
        "web",
        "Web Server",
        8,
        12.0
    );

    m_services.emplace_back(
        "api",
        "Application API",
        8,
        18.0
    );

    m_services.emplace_back(
        "database",
        "Database",
        8,
        25.0
    );

    for (
        Service &service :
        m_services
    )
    {
        service.clearFaultEffects();
    }
}

bool SimulationEngine::injectFault(
    const Fault &fault
)
{
    for (
        Service &service :
        m_services
    )
    {
        if (
            service.id() !=
            fault.serviceId()
        )
        {
            continue;
        }

        switch (
            fault.type()
        )
        {
            case FaultType::WorkerCrash:
            {
                int workersToFail =
                    std::max(
                        1,
                        static_cast<int>(
                            fault.severity()
                        )
                    );

                int newFailedWorkers =
                    std::min(
                        service.totalWorkers(),
                        service.failedWorkers() +
                            workersToFail
                    );

                service.setFailedWorkers(
                    newFailedWorkers
                );

                break;
            }

            case FaultType::ServiceDown:
            {
                service.setAvailable(
                    false
                );

                break;
            }

            case FaultType::Slowdown:
            {
                service.setLatencyMultiplier(
                    std::max(
                        1.0,
                        fault.severity()
                    )
                );

                break;
            }

            case FaultType::ErrorSpike:
            {
                service.setFailureProbability(
                    severityAsProbability(
                        fault.severity()
                    )
                );

                break;
            }

            case FaultType::TrafficSpike:
            {
                service.setTrafficMultiplier(
                    std::max(
                        1.0,
                        fault.severity()
                    )
                );

                break;
            }

            case FaultType::DNSFailure:
            {
                service.setDnsFailureProbability(
                    severityAsProbability(
                        fault.severity()
                    )
                );

                break;
            }

            case FaultType::TLSFailure:
            {
                service.setTlsFailureProbability(
                    severityAsProbability(
                        fault.severity()
                    )
                );

                break;
            }

            case FaultType::MemoryPressure:
            {
                service.setMemoryPressure(
                    severityAsProbability(
                        fault.severity()
                    )
                );

                break;
            }

            case FaultType::StorageFull:
            {
                service.setStoragePressure(
                    severityAsProbability(
                        fault.severity()
                    )
                );

                break;
            }

            case FaultType::RetryStorm:
            {
                service.setRetryMultiplier(
                    std::max(
                        1.0,
                        fault.severity()
                    )
                );

                break;
            }

            case FaultType::LinkOutage:
            {
                service.setLinkFailureProbability(
                    severityAsProbability(
                        fault.severity()
                    )
                );

                break;
            }
        }

        emit servicesChanged();

        emit faultInjected(
            service.name(),
            fault.name()
        );

        return true;
    }

    return false;
}

bool SimulationEngine::recoverService(
    const QString &serviceId
)
{
    for (
        Service &service :
        m_services
    )
    {
        if (
            service.id() !=
            serviceId
        )
        {
            continue;
        }

        service.clearFaultEffects();

        emit servicesChanged();

        emit serviceRecovered(
            service.name()
        );

        return true;
    }

    return false;
}

bool SimulationEngine::processSingleRequest(
    double &latencyMs
)
{
    latencyMs =
        0.0;

    for (
        Service &service :
        m_services
    )
    {
        int activeWorkers =
            service.activeWorkers();

        if (
            !service.isAvailable() ||
            activeWorkers <=
                0
        )
        {
            return false;
        }

        double capacity =
            static_cast<double>(
                activeWorkers
            ) *
            25.0;

        double effectiveRequestRate =
            static_cast<double>(
                m_requestsPerSecond
            ) *
            service.trafficMultiplier() *
            service.retryMultiplier();

        double loadFactor =
            effectiveRequestRate /
            capacity;

        bool success =
            service.processRequest(
                m_random,
                loadFactor,
                latencyMs
            );

        if (!success)
        {
            return false;
        }
    }

    return true;
}

void SimulationEngine::simulationTick()
{
    if (!m_running)
    {
        return;
    }

    int remaining =
        m_totalRequests -
        m_processed;

    int batch =
        std::min(
            remaining,
            m_requestsPerTick
        );

    for (
        int index = 0;
        index < batch;
        ++index
    )
    {
        double latency =
            0.0;

        bool successful =
            processSingleRequest(
                latency
            );

        ++m_processed;

        if (successful)
        {
            ++m_successful;

            m_totalLatency +=
                latency;
        }
        else
        {
            ++m_failed;
        }
    }

    double currentSuccessRate =
        successRate();

    double currentAverageLatency =
        averageLatency();

    int progress =
        static_cast<int>(
            static_cast<double>(
                m_processed
            ) /
            static_cast<double>(
                m_totalRequests
            ) *
            100.0
        );

    progress =
        std::clamp(
            progress,
            0,
            100
        );

    emit statsUpdated(
        m_processed,
        m_successful,
        m_failed,
        currentSuccessRate,
        currentAverageLatency,
        progress
    );

    if (
        m_processed >=
        m_totalRequests
    )
    {
        m_timer.stop();

        m_running =
            false;

        emit statusChanged(
            "FINISHED"
        );

        emit simulationFinished();
    }
}

double SimulationEngine::severityAsProbability(
    double severity
)
{
    if (
        severity >
        1.0
    )
    {
        severity /=
            100.0;
    }

    return std::clamp(
        severity,
        0.0,
        1.0
    );
}