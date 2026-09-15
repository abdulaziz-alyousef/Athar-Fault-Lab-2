#include "Dashboard.h"

#include "MetricsPanel.h"
#include "../simulation/SimulationEngine.h"

#include <QFrame>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLayoutItem>
#include <QVBoxLayout>

#include <vector>

Dashboard::Dashboard(
    SimulationEngine *engine,
    QWidget *parent
)
    : QWidget(parent),
      m_engine(engine),
      m_statusLabel(nullptr),
      m_totalRequestsLabel(nullptr),
      m_successRateLabel(nullptr),
      m_failedRequestsLabel(nullptr),
      m_averageLatencyLabel(nullptr),
      m_serviceRowsLayout(nullptr)
{
    setObjectName(
        "page"
    );

    QVBoxLayout *mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        35,
        30,
        35,
        30
    );

    mainLayout->setSpacing(
        18
    );

    QHBoxLayout *headerLayout =
        new QHBoxLayout;

    QVBoxLayout *headerText =
        new QVBoxLayout;

    QLabel *title =
        new QLabel(
            "Simulation Dashboard"
        );

    title->setObjectName(
        "pageTitle"
    );

    QLabel *description =
        new QLabel(
            "Real-time workload metrics, runtime failures, latency and infrastructure health."
        );

    description->setObjectName(
        "pageDescription"
    );

    description->setWordWrap(
        true
    );

    headerText->addWidget(
        title
    );

    headerText->addWidget(
        description
    );

    m_statusLabel =
        new QLabel(
            "SYSTEM READY"
        );

    m_statusLabel->setObjectName(
        "systemReady"
    );

    headerLayout->addLayout(
        headerText
    );

    headerLayout->addStretch();

    headerLayout->addWidget(
        m_statusLabel
    );

    mainLayout->addLayout(
        headerLayout
    );

    QGridLayout *statsLayout =
        new QGridLayout;

    statsLayout->setHorizontalSpacing(
        14
    );

    statsLayout->setVerticalSpacing(
        14
    );

    statsLayout->addWidget(
        createMetricCard(
            "PROCESSED REQUESTS",
            "0",
            "Requests processed during the current run",
            &m_totalRequestsLabel
        ),
        0,
        0
    );

    statsLayout->addWidget(
        createMetricCard(
            "SUCCESS RATE",
            "100%",
            "Runtime success rate across processed requests",
            &m_successRateLabel
        ),
        0,
        1
    );

    statsLayout->addWidget(
        createMetricCard(
            "FAILED REQUESTS",
            "0",
            "Observed runtime failures, including overload",
            &m_failedRequestsLabel
        ),
        0,
        2
    );

    statsLayout->addWidget(
        createMetricCard(
            "AVG. LATENCY",
            "0 ms",
            "Average latency of successful requests",
            &m_averageLatencyLabel
        ),
        0,
        3
    );

    mainLayout->addLayout(
        statsLayout
    );

    QHBoxLayout *workspaceLayout =
        new QHBoxLayout;

    workspaceLayout->setSpacing(
        16
    );

    QFrame *chartCard =
        new QFrame;

    chartCard->setObjectName(
        "card"
    );

    QVBoxLayout *chartLayout =
        new QVBoxLayout(
            chartCard
        );

    chartLayout->setContentsMargins(
        16,
        16,
        16,
        16
    );

    QLabel *chartExplanation =
        new QLabel(
            "Runtime Failure Rate is calculated from actual failed requests. "
            "It is separate from a service's configured fault probability."
        );

    chartExplanation->setObjectName(
        "pageDescription"
    );

    chartExplanation->setWordWrap(
        true
    );

    MetricsPanel *metricsPanel =
        new MetricsPanel(
            m_engine,
            chartCard
        );

    chartLayout->addWidget(
        chartExplanation
    );

    chartLayout->addWidget(
        metricsPanel,
        1
    );

    QFrame *healthCard =
        new QFrame;

    healthCard->setObjectName(
        "card"
    );

    healthCard->setMinimumWidth(
        340
    );

    QVBoxLayout *healthLayout =
        new QVBoxLayout(
            healthCard
        );

    healthLayout->setContentsMargins(
        20,
        18,
        20,
        18
    );

    healthLayout->setSpacing(
        10
    );

    QLabel *healthTitle =
        new QLabel(
            "Infrastructure Health"
        );

    healthTitle->setObjectName(
        "sectionTitle"
    );

    QLabel *healthDescription =
        new QLabel(
            "Configured service state and active injected faults."
        );

    healthDescription->setObjectName(
        "pageDescription"
    );

    healthDescription->setWordWrap(
        true
    );

    healthLayout->addWidget(
        healthTitle
    );

    healthLayout->addWidget(
        healthDescription
    );

    m_serviceRowsLayout =
        new QVBoxLayout;

    m_serviceRowsLayout->setSpacing(
        8
    );

    healthLayout->addLayout(
        m_serviceRowsLayout,
        1
    );

    workspaceLayout->addWidget(
        chartCard,
        2
    );

    workspaceLayout->addWidget(
        healthCard,
        1
    );

    mainLayout->addLayout(
        workspaceLayout,
        1
    );

    if (
        m_engine
    )
    {
        connect(
            m_engine,
            &SimulationEngine::servicesChanged,
            this,
            [this]()
            {
                rebuildServiceHealth();
            }
        );

        connect(
            m_engine,
            &SimulationEngine::faultInjected,
            this,
            [this](
                const QString &,
                const QString &
            )
            {
                rebuildServiceHealth();
            }
        );

        connect(
            m_engine,
            &SimulationEngine::serviceRecovered,
            this,
            [this](
                const QString &
            )
            {
                rebuildServiceHealth();
            }
        );
    }

    rebuildServiceHealth();
}

QLabel *Dashboard::statusLabel() const
{
    return m_statusLabel;
}

QLabel *Dashboard::totalRequestsLabel() const
{
    return m_totalRequestsLabel;
}

QLabel *Dashboard::successRateLabel() const
{
    return m_successRateLabel;
}

QLabel *Dashboard::failedRequestsLabel() const
{
    return m_failedRequestsLabel;
}

QLabel *Dashboard::averageLatencyLabel() const
{
    return m_averageLatencyLabel;
}

QWidget *Dashboard::createMetricCard(
    const QString &title,
    const QString &value,
    const QString &description,
    QLabel **valueOutput
)
{
    QFrame *card =
        new QFrame;

    card->setObjectName(
        "card"
    );

    card->setMinimumHeight(
        118
    );

    QVBoxLayout *layout =
        new QVBoxLayout(
            card
        );

    layout->setContentsMargins(
        17,
        14,
        17,
        14
    );

    layout->setSpacing(
        5
    );

    QLabel *titleLabel =
        new QLabel(
            title
        );

    titleLabel->setObjectName(
        "cardTitle"
    );

    QLabel *valueLabel =
        new QLabel(
            value
        );

    valueLabel->setObjectName(
        "cardValue"
    );

    QLabel *descriptionLabel =
        new QLabel(
            description
        );

    descriptionLabel->setObjectName(
        "cardDescription"
    );

    descriptionLabel->setWordWrap(
        true
    );

    layout->addWidget(
        titleLabel
    );

    layout->addWidget(
        valueLabel
    );

    layout->addWidget(
        descriptionLabel
    );

    if (
        valueOutput
    )
    {
        *valueOutput =
            valueLabel;
    }

    return card;
}

void Dashboard::rebuildServiceHealth()
{
    if (
        !m_serviceRowsLayout
    )
    {
        return;
    }

    while (
        QLayoutItem *item =
            m_serviceRowsLayout->takeAt(
                0
            )
    )
    {
        if (
            item->widget()
        )
        {
            delete item->widget();
        }

        delete item;
    }

    if (
        !m_engine
    )
    {
        QLabel *emptyLabel =
            new QLabel(
                "Simulation engine unavailable."
            );

        emptyLabel->setObjectName(
            "pageDescription"
        );

        m_serviceRowsLayout->addWidget(
            emptyLabel
        );

        return;
    }

    const std::vector<Service> &services =
        m_engine->services();

    for (
        const Service &service :
        services
    )
    {
        QFrame *row =
            new QFrame;
        row->setObjectName(
            "serviceHealthRow"
        );

        QVBoxLayout *rowLayout =
            new QVBoxLayout(
                row
            );

        rowLayout->setContentsMargins(
            12,
            9,
            12,
            9
        );

        rowLayout->setSpacing(
            4
        );

        QHBoxLayout *topLine =
            new QHBoxLayout;

        QLabel *nameLabel =
            new QLabel(
                service.name()
            );
        nameLabel->setObjectName(
            "serviceName"
        );

        QString health =
            service.healthStatus();

        QLabel *healthLabel =
            new QLabel(
                health
            );

        QString healthColor =
            health == "ONLINE"
                ? "#3fb950"
                : (
                      health == "DEGRADED"
                          ? "#d29922"
                          : "#f85149"
                  );

        healthLabel->setStyleSheet(
            QString(
                "border: none;"
                "color: %1;"
                "font-weight: 800;"
                "font-size: 11px;"
            )
                .arg(
                    healthColor
                )
        );

        topLine->addWidget(
            nameLabel
        );

        topLine->addStretch();

        topLine->addWidget(
            healthLabel
        );

        QLabel *detailsLabel =
            new QLabel(
                QString(
                    "Workers %1/%2 | Latency %3 ms | Configured Failure %4%"
                )
                    .arg(
                        service.activeWorkers()
                    )
                    .arg(
                        service.totalWorkers()
                    )
                    .arg(
                        service.effectiveLatencyEstimate(),
                        0,
                        'f',
                        1
                    )
                    .arg(
                        service.effectiveFailureProbability() *
                            100.0,
                        0,
                        'f',
                        1
                    )
            );
        detailsLabel->setObjectName(
            "serviceDetail"
        );

        detailsLabel->setWordWrap(
            true
        );

        QString fault =
            service.activeFaultSummary();

        QLabel *faultLabel =
            new QLabel(
                "Fault: " +
                fault
            );
        faultLabel->setObjectName(
            fault == "None"
                ? "serviceDetail"
                : "serviceFaultActive"
        );

        faultLabel->setWordWrap(
            true
        );

        rowLayout->addLayout(
            topLine
        );

        rowLayout->addWidget(
            detailsLabel
        );

        rowLayout->addWidget(
            faultLabel
        );

        m_serviceRowsLayout->addWidget(
            row
        );
    }

    m_serviceRowsLayout->addStretch();
}