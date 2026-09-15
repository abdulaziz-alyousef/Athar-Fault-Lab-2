#include "FaultPanel.h"

#include "../simulation/SimulationEngine.h"

#include <QAbstractSpinBox>
#include <QAction>
#include <QDateTime>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMenu>
#include <QPushButton>
#include <QVBoxLayout>

FaultPanel::FaultPanel(
    SimulationEngine *engine,
    QWidget *parent
)
    : QWidget(parent),
      m_engine(engine),
      m_serviceButton(nullptr),
      m_faultButton(nullptr),
      m_serviceMenu(nullptr),
      m_faultMenu(nullptr),
      m_selectedFaultType(
          FaultType::WorkerCrash
      ),
      m_selectedFaultName(
          "Worker Crash"
      ),
      m_severitySpin(nullptr),
      m_minusButton(nullptr),
      m_plusButton(nullptr),
      m_severityLabel(nullptr),
      m_faultDescription(nullptr),
      m_serviceStatus(nullptr),
      m_activeFaultStatus(nullptr),
      m_faultLog(nullptr)
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
        20
    );

    QLabel *title =
        new QLabel(
            "Fault Injection"
        );

    title->setObjectName(
        "pageTitle"
    );

    QLabel *description =
        new QLabel(
            "Inject infrastructure faults while the simulation is running "
            "and observe their impact in real time."
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

    QFrame *controlCard =
        new QFrame;

    controlCard->setObjectName(
        "card"
    );

    QVBoxLayout *controlLayout =
        new QVBoxLayout(
            controlCard
        );

    controlLayout->setContentsMargins(
        25,
        22,
        25,
        22
    );

    controlLayout->setSpacing(
        16
    );

    QLabel *controlTitle =
        new QLabel(
            "Fault Control Center"
        );

    controlTitle->setObjectName(
        "sectionTitle"
    );

    controlLayout->addWidget(
        controlTitle
    );

    QHBoxLayout *selectors =
        new QHBoxLayout;

    selectors->setSpacing(
        20
    );

    QVBoxLayout *serviceLayout =
        new QVBoxLayout;

    QLabel *serviceLabel =
        new QLabel(
            "Target Service"
        );

    serviceLabel->setObjectName(
        "fieldLabel"
    );

    m_serviceButton =
        new QPushButton(
            "Select Service"
        );

    m_serviceButton->setObjectName(
        "selectorButton"
    );

    m_serviceButton->setFixedWidth(
        220
    );

    m_serviceMenu =
        new QMenu(
            m_serviceButton
        );

    m_serviceButton->setMenu(
        m_serviceMenu
    );

    serviceLayout->addWidget(
        serviceLabel
    );

    serviceLayout->addWidget(
        m_serviceButton
    );

    QVBoxLayout *faultLayout =
        new QVBoxLayout;

    QLabel *faultLabel =
        new QLabel(
            "Fault Type"
        );

    faultLabel->setObjectName(
        "fieldLabel"
    );

    m_faultButton =
        new QPushButton(
            "Worker Crash"
        );

    m_faultButton->setObjectName(
        "selectorButton"
    );

    m_faultButton->setFixedWidth(
        220
    );

    m_faultMenu =
        new QMenu(
            m_faultButton
        );

    m_faultButton->setMenu(
        m_faultMenu
    );

    faultLayout->addWidget(
        faultLabel
    );

    faultLayout->addWidget(
        m_faultButton
    );

    selectors->addLayout(
        serviceLayout,
        1
    );

    selectors->addLayout(
        faultLayout,
        1
    );

    controlLayout->addLayout(
        selectors
    );

    m_serviceStatus =
        new QLabel;

    m_serviceStatus->setWordWrap(
        true
    );

    m_serviceStatus->setStyleSheet(
        "background-color: rgba(127, 127, 127, 18);"
        "border: 1px solid rgba(127, 127, 127, 70);"
        "border-radius: 7px;"
        "padding: 10px;"
    );

    controlLayout->addWidget(
        m_serviceStatus
    );

    m_activeFaultStatus =
        new QLabel(
            "NO ACTIVE FAULT"
        );

    m_activeFaultStatus->setAlignment(
        Qt::AlignCenter
    );

    m_activeFaultStatus->setMinimumHeight(
        38
    );

    m_activeFaultStatus->setWordWrap(
        true
    );

    controlLayout->addWidget(
        m_activeFaultStatus
    );

    m_severityLabel =
        new QLabel(
            "Severity"
        );

    m_severityLabel->setObjectName(
        "fieldLabel"
    );

    controlLayout->addWidget(
        m_severityLabel
    );

    QHBoxLayout *severityLayout =
        new QHBoxLayout;

    severityLayout->setSpacing(
        8
    );

    m_minusButton =
        new QPushButton("-");

    m_minusButton->setObjectName(
        "secondaryButton"
    );

    m_minusButton->setFixedWidth(
        50
    );

    m_plusButton =
        new QPushButton("+");

    m_plusButton->setObjectName(
        "secondaryButton"
    );

    m_plusButton->setFixedWidth(
        50
    );

    m_severitySpin =
        new QDoubleSpinBox;

    m_severitySpin->setButtonSymbols(
        QAbstractSpinBox::NoButtons
    );

    m_severitySpin->setAlignment(
        Qt::AlignCenter
    );

    m_severitySpin->setMinimumWidth(
        210
    );

    severityLayout->addWidget(
        m_minusButton
    );

    severityLayout->addWidget(
        m_severitySpin
    );

    severityLayout->addWidget(
        m_plusButton
    );

    severityLayout->addStretch();

    controlLayout->addLayout(
        severityLayout
    );

    m_faultDescription =
        new QLabel;

    m_faultDescription->setObjectName(
        "pageDescription"
    );

    m_faultDescription->setWordWrap(
        true
    );

    controlLayout->addWidget(
        m_faultDescription
    );

    QHBoxLayout *actionButtons =
        new QHBoxLayout;

    QPushButton *injectButton =
        new QPushButton(
            "Inject Fault"
        );

    injectButton->setObjectName(
        "dangerButton"
    );

    QPushButton *recoverButton =
        new QPushButton(
            "Recover Service"
        );

    recoverButton->setObjectName(
        "primaryButton"
    );

    actionButtons->addWidget(
        injectButton
    );

    actionButtons->addWidget(
        recoverButton
    );

    actionButtons->addStretch();

    controlLayout->addLayout(
        actionButtons
    );

    mainLayout->addWidget(
        controlCard
    );

    QFrame *logCard =
        new QFrame;

    logCard->setObjectName(
        "card"
    );

    QVBoxLayout *logLayout =
        new QVBoxLayout(
            logCard
        );

    logLayout->setContentsMargins(
        25,
        22,
        25,
        22
    );

    logLayout->setSpacing(
        12
    );

    QLabel *logTitle =
        new QLabel(
            "Live Fault Log"
        );

    logTitle->setObjectName(
        "sectionTitle"
    );

    m_faultLog =
        new QListWidget;

    logLayout->addWidget(
        logTitle
    );

    logLayout->addWidget(
        m_faultLog
    );

    mainLayout->addWidget(
        logCard,
        1
    );

    // The application-level stylesheet in MainWindow controls the
    // selector buttons, menus, spin box, and fault log for both themes.
    // Avoid local dark-only styles here so Light/Dark switching stays correct.

    rebuildFaultMenu();
    refreshServices();

    updateSeverityMode();
    updateSelectedServiceStatus();

    connect(
        m_minusButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            m_severitySpin->stepDown();
        }
    );

    connect(
        m_plusButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            m_severitySpin->stepUp();
        }
    );

    connect(
        injectButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            injectFault();
        }
    );

    connect(
        recoverButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            recoverService();
        }
    );

    connect(
        m_engine,
        &SimulationEngine::faultInjected,
        this,
        [this](
            const QString &serviceName,
            const QString &faultName
        )
        {
            addLog(
                QString(
                    "FAULT | %1 | %2"
                )
                    .arg(
                        serviceName
                    )
                    .arg(
                        faultName
                    )
            );

            updateSelectedServiceStatus();
        }
    );

    connect(
        m_engine,
        &SimulationEngine::serviceRecovered,
        this,
        [this](
            const QString &serviceName
        )
        {
            addLog(
                QString(
                    "RECOVERED | %1"
                )
                    .arg(
                        serviceName
                    )
            );

            updateSelectedServiceStatus();
        }
    );

    connect(
        m_engine,
        &SimulationEngine::servicesChanged,
        this,
        [this]()
        {
            updateSelectedServiceStatus();
        }
    );
}

void FaultPanel::rebuildServiceMenu()
{
    if (
        !m_engine ||
        !m_serviceMenu
    )
    {
        return;
    }

    m_serviceMenu->clear();

    const std::vector<Service> &services =
        m_engine->services();

    for (
        const Service &service :
        services
    )
    {
        QAction *action =
            m_serviceMenu->addAction(
                service.name()
            );

        QString id =
            service.id();

        QString name =
            service.name();

        connect(
            action,
            &QAction::triggered,
            this,
            [
                this,
                id,
                name
            ]()
            {
                selectService(
                    id,
                    name
                );
            }
        );
    }
}

void FaultPanel::rebuildFaultMenu()
{
    if (!m_faultMenu)
    {
        return;
    }

    m_faultMenu->clear();

    auto addFault =
        [this](
            FaultType type,
            const QString &name
        )
        {
            QAction *action =
                m_faultMenu->addAction(
                    name
                );

            connect(
                action,
                &QAction::triggered,
                this,
                [
                    this,
                    type,
                    name
                ]()
                {
                    selectFault(
                        type,
                        name
                    );
                }
            );
        };

    addFault(
        FaultType::WorkerCrash,
        "Worker Crash"
    );

    addFault(
        FaultType::ServiceDown,
        "Service Down"
    );

    addFault(
        FaultType::Slowdown,
        "Slowdown"
    );

    addFault(
        FaultType::ErrorSpike,
        "Error Spike"
    );

    addFault(
        FaultType::TrafficSpike,
        "Traffic Spike"
    );

    addFault(
        FaultType::DNSFailure,
        "DNS Failure"
    );

    addFault(
        FaultType::TLSFailure,
        "TLS Failure"
    );

    addFault(
        FaultType::MemoryPressure,
        "Memory Pressure"
    );

    addFault(
        FaultType::StorageFull,
        "Storage Full"
    );

    addFault(
        FaultType::RetryStorm,
        "Retry Storm"
    );

    addFault(
        FaultType::LinkOutage,
        "Link Outage"
    );
}

void FaultPanel::selectService(
    const QString &serviceId,
    const QString &serviceName
)
{
    m_selectedServiceId =
        serviceId;

    m_selectedServiceName =
        serviceName;

    m_serviceButton->setText(
        serviceName
    );

    updateSelectedServiceStatus();
}

void FaultPanel::selectFault(
    FaultType type,
    const QString &faultName
)
{
    m_selectedFaultType =
        type;

    m_selectedFaultName =
        faultName;

    m_faultButton->setText(
        faultName
    );

    updateSeverityMode();
}

void FaultPanel::refreshServices()
{
    if (!m_engine)
    {
        return;
    }

    QString previousId =
        m_selectedServiceId;

    rebuildServiceMenu();

    const std::vector<Service> &services =
        m_engine->services();

    if (services.empty())
    {
        m_selectedServiceId.clear();
        m_selectedServiceName.clear();

        m_serviceButton->setText(
            "No Services"
        );

        updateSelectedServiceStatus();

        return;
    }

    for (
        const Service &service :
        services
    )
    {
        if (
            service.id() ==
            previousId
        )
        {
            selectService(
                service.id(),
                service.name()
            );

            return;
        }
    }

    selectService(
        services.front().id(),
        services.front().name()
    );
}

void FaultPanel::updateSelectedServiceStatus()
{
    if (
        !m_engine ||
        !m_serviceStatus ||
        !m_activeFaultStatus
    )
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
        if (
            service.id() !=
            m_selectedServiceId
        )
        {
            continue;
        }

        m_serviceStatus->setText(
            QString(
                "%1 | Workers: %2/%3 | Failed Workers: %4 | "
                "Base Latency: %5 ms | Effective Latency: %6 ms | "
                "Effective Failure: %7%"
            )
                .arg(
                    service.healthStatus()
                )
                .arg(
                    service.activeWorkers()
                )
                .arg(
                    service.totalWorkers()
                )
                .arg(
                    service.failedWorkers()
                )
                .arg(
                    service.baseLatencyMs(),
                    0,
                    'f',
                    1
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

        QString faultSummary =
            service.activeFaultSummary();

        if (
            faultSummary ==
            "None"
        )
        {
            m_activeFaultStatus->setText(
                "NO ACTIVE FAULT"
            );

            m_activeFaultStatus->setStyleSheet(
                "background-color: rgba(46, 160, 67, 28);"
                "color: #2da44e;"
                "border: 1px solid rgba(46, 160, 67, 150);"
                "border-radius: 7px;"
                "padding: 8px;"
                "font-weight: 700;"
            );
        }
        else
        {
            m_activeFaultStatus->setText(
                "ACTIVE FAULT: " +
                faultSummary
            );

            m_activeFaultStatus->setStyleSheet(
                "background-color: rgba(207, 34, 46, 28);"
                "color: #cf222e;"
                "border: 1px solid rgba(207, 34, 46, 150);"
                "border-radius: 7px;"
                "padding: 8px;"
                "font-weight: 700;"
            );
        }

        return;
    }

    m_serviceStatus->setText(
        "No service selected."
    );

    m_activeFaultStatus->setText(
        "NO ACTIVE FAULT"
    );
}

void FaultPanel::updateSeverityMode()
{
    m_severitySpin->setEnabled(
        true
    );

    m_minusButton->setEnabled(
        true
    );

    m_plusButton->setEnabled(
        true
    );

    if (
        m_selectedFaultType ==
        FaultType::WorkerCrash
    )
    {
        m_severityLabel->setText(
            "Workers to Crash"
        );

        m_severitySpin->setRange(
            1.0,
            256.0
        );

        m_severitySpin->setDecimals(
            0
        );

        m_severitySpin->setSingleStep(
            1.0
        );

        m_severitySpin->setValue(
            1.0
        );

        m_severitySpin->setSuffix(
            " workers"
        );

        m_faultDescription->setText(
            "Disables worker processes in the selected service and immediately reduces capacity."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::ServiceDown
    )
    {
        m_severityLabel->setText(
            "Severity"
        );

        m_severitySpin->setSuffix(
            ""
        );

        m_severitySpin->setValue(
            1.0
        );

        m_severitySpin->setEnabled(
            false
        );

        m_minusButton->setEnabled(
            false
        );

        m_plusButton->setEnabled(
            false
        );

        m_faultDescription->setText(
            "Takes the selected service completely offline. Requests reaching it fail immediately."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::Slowdown
    )
    {
        m_severityLabel->setText(
            "Latency Multiplier"
        );

        m_severitySpin->setRange(
            1.1,
            10.0
        );

        m_severitySpin->setDecimals(
            1
        );

        m_severitySpin->setSingleStep(
            0.1
        );

        m_severitySpin->setValue(
            2.0
        );

        m_severitySpin->setSuffix(
            "x"
        );

        m_faultDescription->setText(
            "Multiplies service response time. Example: 2.0x approximately doubles its latency."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::ErrorSpike
    )
    {
        m_severityLabel->setText(
            "Failure Probability"
        );

        m_severitySpin->setRange(
            0.0,
            100.0
        );

        m_severitySpin->setDecimals(
            1
        );

        m_severitySpin->setSingleStep(
            1.0
        );

        m_severitySpin->setValue(
            25.0
        );

        m_severitySpin->setSuffix(
            " %"
        );

        m_faultDescription->setText(
            "Introduces random application-level request failures in the selected service."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::TrafficSpike
    )
    {
        m_severityLabel->setText(
            "Traffic Multiplier"
        );

        m_severitySpin->setRange(
            1.1,
            10.0
        );

        m_severitySpin->setDecimals(
            1
        );

        m_severitySpin->setSingleStep(
            0.1
        );

        m_severitySpin->setValue(
            3.0
        );

        m_severitySpin->setSuffix(
            "x"
        );

        m_faultDescription->setText(
            "Simulates a sudden traffic surge. It increases service load, latency, and overload failures."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::DNSFailure
    )
    {
        m_severityLabel->setText(
            "DNS Failure Probability"
        );

        m_severitySpin->setRange(
            0.0,
            100.0
        );

        m_severitySpin->setDecimals(
            1
        );

        m_severitySpin->setSingleStep(
            1.0
        );

        m_severitySpin->setValue(
            50.0
        );

        m_severitySpin->setSuffix(
            " %"
        );

        m_faultDescription->setText(
            "Simulates DNS resolution failures. For realistic tests, target the Gateway."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::TLSFailure
    )
    {
        m_severityLabel->setText(
            "TLS Failure Probability"
        );

        m_severitySpin->setRange(
            0.0,
            100.0
        );

        m_severitySpin->setDecimals(
            1
        );

        m_severitySpin->setSingleStep(
            1.0
        );

        m_severitySpin->setValue(
            35.0
        );

        m_severitySpin->setSuffix(
            " %"
        );

        m_faultDescription->setText(
            "Simulates TLS handshake or certificate failures before a request is processed."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::MemoryPressure
    )
    {
        m_severityLabel->setText(
            "Memory Pressure"
        );

        m_severitySpin->setRange(
            0.0,
            100.0
        );

        m_severitySpin->setDecimals(
            0
        );

        m_severitySpin->setSingleStep(
            5.0
        );

        m_severitySpin->setValue(
            70.0
        );

        m_severitySpin->setSuffix(
            " %"
        );

        m_faultDescription->setText(
            "Simulates memory pressure. Higher values increase latency and can introduce request failures."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::StorageFull
    )
    {
        m_severityLabel->setText(
            "Storage Pressure"
        );

        m_severitySpin->setRange(
            0.0,
            100.0
        );

        m_severitySpin->setDecimals(
            0
        );

        m_severitySpin->setSingleStep(
            5.0
        );

        m_severitySpin->setValue(
            90.0
        );

        m_severitySpin->setSuffix(
            " %"
        );

        m_faultDescription->setText(
            "Simulates storage exhaustion. For realistic tests, target the Database."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::RetryStorm
    )
    {
        m_severityLabel->setText(
            "Retry Multiplier"
        );

        m_severitySpin->setRange(
            1.1,
            10.0
        );

        m_severitySpin->setDecimals(
            1
        );

        m_severitySpin->setSingleStep(
            0.1
        );

        m_severitySpin->setValue(
            3.0
        );

        m_severitySpin->setSuffix(
            "x"
        );

        m_faultDescription->setText(
            "Simulates clients repeatedly retrying failed requests, increasing effective load and latency."
        );
    }
    else if (
        m_selectedFaultType ==
        FaultType::LinkOutage
    )
    {
        m_severityLabel->setText(
            "Link Failure Probability"
        );

        m_severitySpin->setRange(
            0.0,
            100.0
        );

        m_severitySpin->setDecimals(
            1
        );

        m_severitySpin->setSingleStep(
            1.0
        );

        m_severitySpin->setValue(
            60.0
        );

        m_severitySpin->setSuffix(
            " %"
        );

        m_faultDescription->setText(
            "Simulates an unstable or partially unavailable network link to the selected service."
        );
    }
}

void FaultPanel::injectFault()
{
    if (
        !m_engine ||
        m_selectedServiceId.isEmpty()
    )
    {
        addLog(
            "ERROR | No target service selected."
        );

        return;
    }

    double severity =
        1.0;

    if (
        m_selectedFaultType !=
        FaultType::ServiceDown
    )
    {
        severity =
            m_severitySpin->value();
    }

    Fault fault(
        m_selectedFaultType,
        m_selectedServiceId,
        severity
    );

    bool success =
        m_engine->injectFault(
            fault
        );

    if (!success)
    {
        addLog(
            "ERROR | Fault injection failed."
        );
    }

    updateSelectedServiceStatus();
}

void FaultPanel::recoverService()
{
    if (
        !m_engine ||
        m_selectedServiceId.isEmpty()
    )
    {
        addLog(
            "ERROR | No target service selected."
        );

        return;
    }

    bool success =
        m_engine->recoverService(
            m_selectedServiceId
        );

    if (!success)
    {
        addLog(
            "ERROR | Service recovery failed."
        );
    }

    updateSelectedServiceStatus();
}

void FaultPanel::addLog(
    const QString &message
)
{
    if (!m_faultLog)
    {
        return;
    }

    QString time =
        QDateTime::currentDateTime()
            .toString(
                "HH:mm:ss"
            );

    m_faultLog->insertItem(
        0,
        QString(
            "[%1] %2"
        )
            .arg(
                time
            )
            .arg(
                message
            )
    );

    while (
        m_faultLog->count() >
        200
    )
    {
        delete m_faultLog->takeItem(
            m_faultLog->count() -
            1
        );
    }
}
