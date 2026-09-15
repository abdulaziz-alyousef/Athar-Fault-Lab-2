#ifndef FAULTPANEL_H
#define FAULTPANEL_H

#include <QWidget>

#include "../simulation/Fault.h"

class SimulationEngine;
class QDoubleSpinBox;
class QLabel;
class QListWidget;
class QMenu;
class QPushButton;

class FaultPanel : public QWidget
{
public:
    explicit FaultPanel(
        SimulationEngine *engine,
        QWidget *parent = nullptr
    );

    void refreshServices();

private:
    void rebuildServiceMenu();
    void rebuildFaultMenu();

    void selectService(
        const QString &serviceId,
        const QString &serviceName
    );

    void selectFault(
        FaultType type,
        const QString &faultName
    );

    void updateSeverityMode();
    void updateSelectedServiceStatus();

    void injectFault();
    void recoverService();

    void addLog(
        const QString &message
    );

    SimulationEngine *m_engine;

    QPushButton *m_serviceButton;
    QPushButton *m_faultButton;

    QMenu *m_serviceMenu;
    QMenu *m_faultMenu;

    QString m_selectedServiceId;
    QString m_selectedServiceName;

    FaultType m_selectedFaultType;
    QString m_selectedFaultName;

    QDoubleSpinBox *m_severitySpin;

    QPushButton *m_minusButton;
    QPushButton *m_plusButton;

    QLabel *m_severityLabel;
    QLabel *m_faultDescription;
    QLabel *m_serviceStatus;
    QLabel *m_activeFaultStatus;

    QListWidget *m_faultLog;
};

#endif