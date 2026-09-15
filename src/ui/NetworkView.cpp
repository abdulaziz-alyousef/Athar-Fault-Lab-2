#include "NetworkView.h"

#include "../simulation/SimulationEngine.h"

#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

NetworkView::NetworkView(
    SimulationEngine *engine,
    QWidget *parent
)
    : QWidget(parent),
      m_engine(engine)
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

    QLabel *title =
        new QLabel(
            "Network View"
        );

    title->setObjectName(
        "pageTitle"
    );

    QLabel *description =
        new QLabel(
            "Live topology of the simulated request path. "
            "Node colors and metrics update automatically when "
            "services are changed, faults are injected, or services recover."
        );

    description->setObjectName(
        "pageDescription"
    );

    description->setWordWrap(
        true
    );

    mainLayout->addWidget(
        title
    );

    mainLayout->addWidget(
        description
    );

    QFrame *topologyCard =
        new QFrame;

    topologyCard->setObjectName(
        "card"
    );

    QVBoxLayout *topologyLayout =
        new QVBoxLayout(
            topologyCard
        );

    topologyLayout->setContentsMargins(
        22,
        20,
        22,
        20
    );

    topologyLayout->setSpacing(
        6
    );

    QLabel *topologyTitle =
        new QLabel(
            "Client Request Flow"
        );

    topologyTitle->setObjectName(
        "sectionTitle"
    );

    topologyLayout->addWidget(
        topologyTitle
    );

    QLabel *clientLabel =
        new QLabel(
            "CLIENT"
        );

    clientLabel->setAlignment(
        Qt::AlignCenter
    );

    clientLabel->setObjectName(
        "networkClient"
    );

    topologyLayout->addWidget(
        clientLabel
    );

    QLabel *arrow1 =
        new QLabel("↓");

    QLabel *arrow2 =
        new QLabel("↓");

    QLabel *arrow3 =
        new QLabel("↓");

    QLabel *arrow4 =
        new QLabel("↓");

    QLabel *arrows[] = {
        arrow1,
        arrow2,
        arrow3,
        arrow4
    };

    for (
        QLabel *arrow :
        arrows
    )
    {
        arrow->setAlignment(
            Qt::AlignCenter
        );

        arrow->setObjectName(
            "networkArrow"
        );
    }

    topologyLayout->addWidget(
        arrow1
    );

    topologyLayout->addWidget(
        createNodeCard(
            "gateway",
            "Gateway"
        )
    );

    topologyLayout->addWidget(
        arrow2
    );

    topologyLayout->addWidget(
        createNodeCard(
            "web",
            "Web Server"
        )
    );

    topologyLayout->addWidget(
        arrow3
    );

    topologyLayout->addWidget(
        createNodeCard(
            "api",
            "Application API"
        )
    );

    topologyLayout->addWidget(
        arrow4
    );

    topologyLayout->addWidget(
        createNodeCard(
            "database",
            "Database"
        )
    );

    mainLayout->addWidget(
        topologyCard,
        1
    );

    if (m_engine)
    {
        connect(
            m_engine,
            &SimulationEngine::servicesChanged,
            this,
            &NetworkView::refresh
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
                refresh();
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
                refresh();
            }
        );
    }

    refresh();
}

QWidget *NetworkView::createNodeCard(
    const QString &serviceId,
    const QString &title
)
{
    QFrame *card =
        new QFrame;

    card->setObjectName(
        "networkNode"
    );

    card->setMinimumHeight(
        96
    );

    QVBoxLayout *layout =
        new QVBoxLayout(card);

    layout->setContentsMargins(
        16,
        12,
        16,
        12
    );

    layout->setSpacing(
        5
    );

    QHBoxLayout *headerLayout =
        new QHBoxLayout;

    QLabel *nameLabel =
        new QLabel(
            title
        );

    nameLabel->setObjectName(
        "networkNodeName"
    );

    QLabel *stateLabel =
        new QLabel(
            "ONLINE"
        );

    stateLabel->setAlignment(
        Qt::AlignCenter
    );

    headerLayout->addWidget(
        nameLabel
    );

    headerLayout->addStretch();

    headerLayout->addWidget(
        stateLabel
    );

    QLabel *workersLabel =
        new QLabel;

    QLabel *latencyLabel =
        new QLabel;

    QLabel *failureLabel =
        new QLabel;

    QLabel *faultLabel =
        new QLabel;

    workersLabel->setObjectName(
        "networkNodeDetail"
    );

    latencyLabel->setObjectName(
        "networkNodeDetail"
    );

    failureLabel->setObjectName(
        "networkNodeDetail"
    );

    faultLabel->setObjectName(
        "networkNodeFault"
    );

    faultLabel->setWordWrap(
        true
    );

    QHBoxLayout *metricsLayout =
        new QHBoxLayout;

    metricsLayout->setSpacing(
        20
    );

    metricsLayout->addWidget(
        workersLabel,
        1
    );

    metricsLayout->addWidget(
        latencyLabel,
        1
    );

    metricsLayout->addWidget(
        failureLabel,
        1
    );

    layout->addLayout(
        headerLayout
    );

    layout->addLayout(
        metricsLayout
    );

    layout->addWidget(
        faultLabel
    );

    NodeWidgets widgets;

    widgets.card =
        card;

    widgets.name =
        nameLabel;

    widgets.state =
        stateLabel;

    widgets.workers =
        workersLabel;

    widgets.latency =
        latencyLabel;

    widgets.failure =
        failureLabel;

    widgets.fault =
        faultLabel;

    m_nodes.insert(
        serviceId,
        widgets
    );

    card->setStyleSheet(
        cardStyle(
            NodeState::Online
        )
    );

    return card;
}

void NetworkView::refresh()
{
    if (!m_engine)
    {
        return;
    }

    const std::vector<Service> &services =
        m_engine->services();

    for (
        const Service &service :
        services
    )
    {
        NodeState state =
            NodeState::Online;

        QString health =
            service.healthStatus();

        if (
            health ==
            "OFFLINE"
        )
        {
            state =
                NodeState::Offline;
        }
        else if (
            health ==
            "DEGRADED"
        )
        {
            state =
                NodeState::Degraded;
        }

        updateNode(
            service.id(),
            service.name(),
            service.isAvailable(),
            service.totalWorkers(),
            service.failedWorkers(),
            service.activeWorkers(),
            service.baseLatencyMs(),
            service.effectiveLatencyEstimate(),
            service.effectiveFailureProbability() *
                100.0,
            service.activeFaultSummary(),
            state
        );
    }
}

void NetworkView::updateNode(
    const QString &serviceId,
    const QString &name,
    bool available,
    int totalWorkers,
    int failedWorkers,
    int activeWorkers,
    double baseLatency,
    double effectiveLatency,
    double failureRate,
    const QString &faultText,
    NodeState state
)
{
    if (
        !m_nodes.contains(
            serviceId
        )
    )
    {
        return;
    }

    NodeWidgets widgets =
        m_nodes.value(
            serviceId
        );

    widgets.card->setStyleSheet(
        cardStyle(
            state
        )
    );

    widgets.name->setText(
        name
    );

    widgets.state->setText(
        stateText(
            state
        )
    );

    widgets.state->setStyleSheet(
        QString(
            "background-color: %1;"
            "color: #0d1117;"
            "border-radius: 7px;"
            "padding: 5px 10px;"
            "font-size: 11px;"
            "font-weight: 800;"
        )
            .arg(
                stateColor(
                    state
                )
            )
    );

    widgets.workers->setText(
        QString(
            "Workers: %1/%2 active | Failed: %3"
        )
            .arg(
                activeWorkers
            )
            .arg(
                totalWorkers
            )
            .arg(
                failedWorkers
            )
    );

    widgets.latency->setText(
        QString(
            "Latency: %1 → %2 ms"
        )
            .arg(
                baseLatency,
                0,
                'f',
                1
            )
            .arg(
                effectiveLatency,
                0,
                'f',
                1
            )
    );

    widgets.failure->setText(
        QString(
            "Failure: %1%"
        )
            .arg(
                failureRate,
                0,
                'f',
                1
            )
    );

    widgets.fault->setText(
        "Active Fault: " +
        faultText
    );

    const bool lightTheme =
        qApp &&
        qApp->property("atharTheme").toString() == "light";

    if (!available)
    {
        widgets.fault->setStyleSheet(
            QString(
                "font-size: 12px;"
                "color: %1;"
                "font-weight: 700;"
            ).arg(
                lightTheme ? "#cf222e" : "#ff7b72"
            )
        );
    }
    else if (
        state ==
        NodeState::Degraded
    )
    {
        widgets.fault->setStyleSheet(
            QString(
                "font-size: 12px;"
                "color: %1;"
                "font-weight: 700;"
            ).arg(
                lightTheme ? "#9a6700" : "#d29922"
            )
        );
    }
    else
    {
        widgets.fault->setStyleSheet(
            QString(
                "font-size: 12px;"
                "color: %1;"
                "font-weight: 600;"
            ).arg(
                lightTheme ? "#59636e" : "#8b949e"
            )
        );
    }
}

QString NetworkView::cardStyle(
    NodeState state
) const
{
    const bool lightTheme =
        qApp &&
        qApp->property("atharTheme").toString() == "light";

    QString background =
        lightTheme ? "#dafbe1" : "#0f1b14";

    QString border =
        lightTheme ? "#1f883d" : "#238636";

    if (
        state ==
        NodeState::Degraded
    )
    {
        background =
            lightTheme ? "#fff8c5" : "#221d12";

        border =
            lightTheme ? "#d4a72c" : "#d29922";
    }
    else if (
        state ==
        NodeState::Offline
    )
    {
        background =
            lightTheme ? "#ffebe9" : "#28181b";

        border =
            lightTheme ? "#cf222e" : "#da3633";
    }

    return QString(
        "QFrame#networkNode {"
        "background-color: %1;"
        "border: 2px solid %2;"
        "border-radius: 10px;"
        "}"
    )
        .arg(
            background,
            border
        );
}

QString NetworkView::stateText(
    NodeState state
) const
{
    switch (state)
    {
        case NodeState::Online:
            return "ONLINE";

        case NodeState::Degraded:
            return "DEGRADED";

        case NodeState::Offline:
            return "OFFLINE";
    }

    return "ONLINE";
}

QString NetworkView::stateColor(
    NodeState state
) const
{
    switch (state)
    {
        case NodeState::Online:
            return "#3fb950";

        case NodeState::Degraded:
            return "#d29922";

        case NodeState::Offline:
            return "#f85149";
    }

    return "#3fb950";
}