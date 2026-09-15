#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include <QMap>
#include <QString>
#include <QWidget>

class QFrame;
class QLabel;
class SimulationEngine;

class NetworkView : public QWidget
{
    Q_OBJECT

public:
    explicit NetworkView(
        SimulationEngine *engine,
        QWidget *parent = nullptr
    );

    void refresh();

private:
    enum class NodeState
    {
        Online,
        Degraded,
        Offline
    };

    struct NodeWidgets
    {
        QFrame *card = nullptr;
        QLabel *name = nullptr;
        QLabel *state = nullptr;
        QLabel *workers = nullptr;
        QLabel *latency = nullptr;
        QLabel *failure = nullptr;
        QLabel *fault = nullptr;
    };

    QWidget *createNodeCard(
        const QString &serviceId,
        const QString &title
    );

    void updateNode(
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
    );

    QString cardStyle(
        NodeState state
    ) const;

    QString stateText(
        NodeState state
    ) const;

    QString stateColor(
        NodeState state
    ) const;

    SimulationEngine *m_engine;

    QMap<QString, NodeWidgets> m_nodes;
};

#endif