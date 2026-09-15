#pragma once

#include <QElapsedTimer>
#include <QTimer>
#include <QWidget>

class SplashScreen : public QWidget
{
public:
    explicit SplashScreen(
        bool lightTheme,
        QWidget *parent = nullptr
    );

    void startAnimation(
        int durationMs = 1800
    );

protected:
    void paintEvent(
        QPaintEvent *event
    ) override;

private:
    void centerOnPrimaryScreen();
    QString statusText() const;

    bool m_lightTheme;
    int m_durationMs;
    int m_progress;

    QElapsedTimer m_elapsed;
    QTimer m_frameTimer;
};