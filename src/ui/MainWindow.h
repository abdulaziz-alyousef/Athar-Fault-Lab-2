#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class HistoryManager;
class HistoryPanel;
class QLabel;
class NetworkView;
class QProgressBar;
class QSpinBox;
class QStackedWidget;
class QTableWidget;
class QWidget;
class ReportsPanel;
class SimulationEngine;

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QWidget *createSidebar();
    QWidget *createDashboard();
    QWidget *createSimulationPage();
    QWidget *createServicesPage();
    QWidget *createNetworkViewPage();

    QWidget *createStatCard(
        const QString &title,
        const QString &value,
        const QString &description,
        QLabel **valueOutput
    );

    void refreshServicesTable();
    void refreshReportFromLatestHistory();

    QStackedWidget *pages;

    SimulationEngine *simulationEngine;

    HistoryManager *historyManager;
    HistoryPanel *historyPanel;
    ReportsPanel *reportsPanel;

    NetworkView *networkView;

    QLabel *simulationStatus;

    QLabel *totalRequestsValue;
    QLabel *successRateValue;
    QLabel *failedRequestsValue;
    QLabel *averageLatencyValue;

    QLabel *runtimeStatus;

    QProgressBar *simulationProgress;

    QSpinBox *requestsSpin;
    QSpinBox *rateSpin;
    QSpinBox *durationSpin;

    QTableWidget *servicesTable;
};

#endif