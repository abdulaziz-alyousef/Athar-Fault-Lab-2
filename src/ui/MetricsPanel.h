#ifndef METRICSPANEL_H
#define METRICSPANEL_H

#include <QVector>
#include <QWidget>

class QPainter;
class SimulationEngine;

class MetricsPanel : public QWidget
{
public:
    explicit MetricsPanel(
        SimulationEngine *engine,
        QWidget *parent = nullptr
    );

    QSize minimumSizeHint() const override;

protected:
    void paintEvent(
        QPaintEvent *event
    ) override;

private:
    struct Sample
    {
        int progress;
        double successRate;
        double failureRate;
        double latency;
    };

    void resetSeries();

    void addSample(
        int processed,
        int failed,
        double successRate,
        double latency,
        int progress
    );

    void drawRateChart(
        QPainter &painter,
        const QRectF &rect
    ) const;

    void drawLatencyChart(
        QPainter &painter,
        const QRectF &rect
    ) const;

    SimulationEngine *m_engine;
    QVector<Sample> m_samples;
    int m_lastProgress;
};

#endif
