#include <QAbstractAnimation>
#include <QApplication>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QSettings>
#include <QTimer>

#include <memory>

#include "ui/MainWindow.h"
#include "ui/SplashScreen.h"

int main(
    int argc,
    char *argv[]
)
{
    QApplication app(
        argc,
        argv
    );

    QApplication::setApplicationName(
        "Athar Fault Lab 2"
    );

    QApplication::setApplicationDisplayName(
        "Athar Fault Lab 2"
    );

    QApplication::setOrganizationName(
        "abdulaziz alyousef"
    );

    QApplication::setOrganizationDomain(
        "athar-fault-lab.local"
    );

    app.setStyle(
        "Fusion"
    );

  
    QSettings settings;

    const bool useLightTheme =
        settings
            .value(
                "appearance/theme",
                "dark"
            )
            .toString() ==
        "light";

  
    app.setProperty(
        "atharTheme",
        useLightTheme
            ? "light"
            : "dark"
    );

    SplashScreen splash(
        useLightTheme
    );

    splash.show();

    splash.startAnimation(
        1800
    );

    app.processEvents();

    std::unique_ptr<MainWindow> window;

 
    QTimer::singleShot(
        1450,
        [&window]()
        {
            if (!window)
            {
                window =
                    std::make_unique<MainWindow>();
            }
        }
    );

    QTimer::singleShot(
        1950,
        [&splash, &window]()
        {
            if (!window)
            {
                window =
                    std::make_unique<MainWindow>();
            }

            QPropertyAnimation *fade =
                new QPropertyAnimation(
                    &splash,
                    "windowOpacity",
                    &splash
                );

            fade->setDuration(
                240
            );

            fade->setStartValue(
                1.0
            );

            fade->setEndValue(
                0.0
            );

            fade->setEasingCurve(
                QEasingCurve::OutCubic
            );

            QObject::connect(
                fade,
                &QPropertyAnimation::finished,
                &splash,
                [&splash, &window]()
                {
                    splash.hide();

                    window->show();
                    window->raise();
                    window->activateWindow();
                }
            );

            fade->start(
                QAbstractAnimation::DeleteWhenStopped
            );
        }
    );

    return app.exec();
}
