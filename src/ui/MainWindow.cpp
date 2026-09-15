#include "MainWindow.h"
#include "Dashboard.h"
#include "FaultPanel.h"
#include "HistoryPanel.h"
#include "NetworkView.h"
#include "ReportsPanel.h"
#include "UiLanguage.h"
#include "../simulation/SimulationEngine.h"
#include "../storage/HistoryManager.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QAbstractSpinBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QGridLayout>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>
#include <QSettings>
#include <QPushButton>
#include <QSpinBox>
#include <QStringList>
#include <QStackedWidget>
#include <QStyle>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#ifdef Q_OS_WIN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <dwmapi.h>
#endif

#include <vector>

namespace
{
QString buildFaultSummary(
    const std::vector<Service> &services
)
{
    QStringList lines;

    for (
        const Service &service :
        services
    )
    {
        QString faultSummary =
            service.activeFaultSummary();

        if (
            faultSummary !=
            "None"
        )
        {
            lines <<
                QString(
                    "%1: %2"
                )
                    .arg(
                        service.name()
                    )
                    .arg(
                        faultSummary
                    );
        }
    }

    if (lines.isEmpty())
    {
        return
            "No active faults at simulation completion.";
    }

    return lines.join(
        "\n"
    );
}

QString buildServiceHealthJson(
    const std::vector<Service> &services
)
{
    QJsonArray array;

    for (
        const Service &service :
        services
    )
    {
        QJsonObject object;

        object.insert(
            "id",
            service.id()
        );

        object.insert(
            "name",
            service.name()
        );

        object.insert(
            "status",
            service.healthStatus()
        );

        object.insert(
            "available",
            service.isAvailable()
        );

        object.insert(
            "totalWorkers",
            service.totalWorkers()
        );

        object.insert(
            "failedWorkers",
            service.failedWorkers()
        );

        object.insert(
            "activeWorkers",
            service.activeWorkers()
        );

        object.insert(
            "baseLatency",
            service.baseLatencyMs()
        );

        object.insert(
            "effectiveLatency",
            service.effectiveLatencyEstimate()
        );

        object.insert(
            "failureRate",
            service.effectiveFailureProbability() *
                100.0
        );

        object.insert(
            "faultSummary",
            service.activeFaultSummary()
        );

        array.append(
            object
        );
    }

    return QString::fromUtf8(
        QJsonDocument(
            array
        ).toJson(
            QJsonDocument::Compact
        )
    );
}


QString themeStyleSheet(bool light)
{
    if (light)
    {
        return QString::fromUtf8(R"ATHAR(
            QMainWindow,
            QStackedWidget,
            QWidget#page {
                background-color: #f6f8fa;
            }

            QWidget {
                color: #1f2328;
                font-family: "Segoe UI";
                font-size: 14px;
            }

            QFrame#sidebar {
                background-color: #ffffff;
                border-right: 1px solid #d0d7de;
            }

            QLabel#appTitle {
                font-size: 22px;
                font-weight: 700;
                color: #1f2328;
            }

            QLabel#appSubtitle,
            QLabel#pageDescription,
            QLabel#cardDescription,
            QLabel#serviceDetail,
            QLabel#networkMetricTitle,
            QLabel#networkNodeFault,
            QLabel#mutedText {
                color: #59636e;
            }

            QLabel#appSubtitle { font-size: 11px; }
            QLabel#pageDescription { font-size: 13px; }
            QLabel#cardDescription { font-size: 11px; }

            QLabel#pageTitle {
                font-size: 28px;
                font-weight: 700;
                color: #1f2328;
            }

            QLabel#cardTitle {
                color: #59636e;
                font-size: 12px;
                font-weight: 600;
            }

            QLabel#cardValue,
            QLabel#reportValue,
            QLabel#networkMetricValue {
                color: #1f2328;
                font-weight: 700;
            }

            QLabel#cardValue { font-size: 28px; }
            QLabel#reportValue { font-size: 20px; }
            QLabel#networkMetricValue { font-size: 16px; }

            QLabel#sectionTitle {
                font-size: 18px;
                font-weight: 700;
                color: #1f2328;
            }

            QLabel#fieldLabel {
                color: #59636e;
                font-size: 12px;
                font-weight: 600;
            }

            QLabel#systemReady,
            QLabel#faultStatusOk {
                background-color: #dafbe1;
                color: #1a7f37;
                border: 1px solid #1f883d;
                border-radius: 8px;
                padding: 8px 13px;
                font-weight: 700;
            }

            QLabel#systemRunning {
                background-color: #ddf4ff;
                color: #0969da;
                border: 1px solid #54aeff;
                border-radius: 8px;
                padding: 8px 13px;
                font-weight: 700;
            }

            QLabel#systemStopped,
            QLabel#faultStatusActive {
                background-color: #ffebe9;
                color: #cf222e;
                border: 1px solid #ff8182;
                border-radius: 8px;
                padding: 8px 13px;
                font-weight: 700;
            }

            QFrame#card,
            QFrame#serviceHealthRow,
            QFrame#networkMetricCard {
                background-color: #ffffff;
                border: 1px solid #d0d7de;
                border-radius: 12px;
            }

            QFrame#serviceHealthRow,
            QFrame#networkMetricCard {
                border-radius: 8px;
            }

            QLabel#serviceName,
            QLabel#networkNodeName {
                color: #1f2328;
                font-weight: 700;
            }

            QLabel#serviceName { font-size: 13px; }
            QLabel#networkNodeName { font-size: 16px; }

            QLabel#serviceDetail,
            QLabel#networkNodeDetail,
            QLabel#networkNodeFault {
                font-size: 11px;
            }

            QLabel#serviceFaultActive {
                color: #9a6700;
                font-size: 10px;
                font-weight: 700;
            }

            QLabel#networkClient {
                background-color: #ddf4ff;
                color: #0969da;
                border: 1px solid #54aeff;
                border-radius: 8px;
                padding: 7px;
                font-weight: 700;
            }

            QLabel#networkArrow {
                font-size: 21px;
                font-weight: 700;
                color: #0969da;
                padding: 0px;
                margin: 0px;
            }

            QLabel#panelInfoBox,
            QLabel#reportCodeBox,
            QLabel#reportInfoBox,
            QLabel#reportStatus {
                background-color: #f6f8fa;
                color: #1f2328;
                border: 1px solid #d0d7de;
                border-radius: 7px;
                padding: 10px 12px;
            }

            QLabel#reportCodeBox {
                font-family: Consolas;
                font-size: 12px;
            }

            QLabel#reportFaultBox {
                background-color: #fff8c5;
                color: #9a6700;
                border: 1px solid #d4a72c;
                border-radius: 7px;
                padding: 10px 12px;
                font-weight: 700;
            }

            QLabel#reportBrand {
                background-color: #ddf4ff;
                color: #0969da;
                border: 1px solid #54aeff;
                border-radius: 9px;
                padding: 12px;
                font-weight: 800;
                font-size: 16px;
            }

            QLabel#reportStatusSuccess,
            QLabel#feedbackSuccess {
                background-color: #dafbe1;
                color: #1a7f37;
                border: 1px solid #1f883d;
                border-radius: 7px;
                padding: 8px 10px;
                font-size: 12px;
                font-weight: 700;
            }

            QLabel#reportStatusError,
            QLabel#feedbackError {
                background-color: #ffebe9;
                color: #cf222e;
                border: 1px solid #ff8182;
                border-radius: 7px;
                padding: 8px 10px;
                font-size: 12px;
                font-weight: 700;
            }

            QLabel#feedbackNeutral {
                background-color: #f6f8fa;
                color: #59636e;
                border: 1px solid #d0d7de;
                border-radius: 7px;
                padding: 9px 11px;
                font-size: 12px;
                font-weight: 600;
            }

            QPushButton#navButton {
                background-color: transparent;
                border: none;
                border-radius: 7px;
                padding: 12px 16px;
                text-align: left;
                color: #1f2328;
            }

            QPushButton#navButton:hover {
                background-color: #f3f4f6;
            }

            QPushButton#navButton:checked {
                background-color: #0969da;
                color: #ffffff;
                font-weight: 700;
            }

            QPushButton#themeButton {
                background-color: #f6f8fa;
                color: #57606a;
                border: 1px solid #d0d7de;
                border-radius: 6px;
                padding: 7px 10px;
                font-size: 12px;
                font-weight: 700;
            }

            QPushButton#themeButton:hover {
                border-color: #0969da;
                color: #0969da;
            }

            QPushButton#themeButton:checked {
                background-color: #0969da;
                color: #ffffff;
                border-color: #0969da;
            }

            QPushButton#primaryButton {
                background-color: #1f883d;
                border: 1px solid #1a7f37;
                color: #ffffff;
                padding: 11px 18px;
                border-radius: 7px;
                font-weight: 700;
            }

            QPushButton#primaryButton:hover { background-color: #1a7f37; }

            QPushButton#dangerButton {
                background-color: #cf222e;
                border: 1px solid #a40e26;
                color: #ffffff;
                padding: 11px 18px;
                border-radius: 7px;
                font-weight: 700;
            }

            QPushButton#dangerButton:hover { background-color: #a40e26; }

            QPushButton#secondaryButton,
            QPushButton#selectorButton,
            QPushButton#stepButton,
            QPushButton#simulationStepButton {
                background-color: #f6f8fa;
                border: 1px solid #d0d7de;
                color: #1f2328;
                border-radius: 7px;
            }

            QPushButton#secondaryButton { padding: 11px 18px; }

            QPushButton#secondaryButton:hover,
            QPushButton#selectorButton:hover,
            QPushButton#stepButton:hover,
            QPushButton#simulationStepButton:hover {
                background-color: #eef1f4;
                border-color: #0969da;
            }

            QPushButton#selectorButton {
                padding: 10px 34px 10px 14px;
                text-align: left;
                min-height: 30px;
                font-weight: 600;
            }

            QPushButton#selectorButton::menu-indicator {
                subcontrol-origin: padding;
                subcontrol-position: center right;
                right: 12px;
            }

            QPushButton#stepButton {
                min-width: 24px;
                max-width: 24px;
                min-height: 30px;
                max-height: 30px;
                font-size: 18px;
                font-weight: 700;
                padding: 0px;
            }

            QPushButton#simulationStepButton {
                min-width: 40px;
                max-width: 40px;
                min-height: 40px;
                max-height: 40px;
                font-size: 20px;
                font-weight: 700;
                padding: 0px;
            }

            QSpinBox,
            QDoubleSpinBox,
            QListWidget,
            QTableWidget,
            QMenu {
                background-color: #ffffff;
                color: #1f2328;
                border: 1px solid #d0d7de;
            }

            QSpinBox,
            QDoubleSpinBox {
                border-radius: 6px;
                padding: 6px;
                min-height: 32px;
            }

            QSpinBox:focus,
            QDoubleSpinBox:focus { border-color: #0969da; }

            QListWidget,
            QTableWidget {
                border-radius: 7px;
            }

            QListWidget { padding: 6px; }
            QListWidget::item { padding: 7px; border-bottom: 1px solid #d8dee4; }

            QTableWidget {
                alternate-background-color: #f6f8fa;
                gridline-color: #d8dee4;
            }

            QTableWidget::item { padding: 8px; }
            QTableWidget::item:selected { background-color: #0969da; color: #ffffff; }

            QHeaderView::section {
                background-color: #f6f8fa;
                color: #1f2328;
                border: none;
                border-right: 1px solid #d0d7de;
                border-bottom: 1px solid #d0d7de;
                padding: 10px;
                font-weight: 700;
            }

            QMenu { padding: 4px; margin: 0px; }
            QMenu::item { padding: 9px 32px 9px 12px; margin: 1px; border-radius: 4px; }
            QMenu::item:selected { background-color: #0969da; color: #ffffff; }

            QCheckBox { spacing: 8px; color: #1f2328; padding-left: 10px; }

            QProgressBar {
                background-color: #ffffff;
                border: 1px solid #d0d7de;
                border-radius: 7px;
                text-align: center;
                color: #1f2328;
                min-height: 25px;
            }

            QProgressBar::chunk { background-color: #1f883d; border-radius: 6px; }

            QScrollArea { background: transparent; border: none; }

            QMessageBox { background-color: #ffffff; }
            QMessageBox QLabel { color: #1f2328; min-width: 340px; font-size: 14px; }
            QMessageBox QPushButton {
                background-color: #f6f8fa;
                color: #1f2328;
                border: 1px solid #d0d7de;
                border-radius: 6px;
                padding: 8px 18px;
                min-width: 90px;
                min-height: 24px;
            }
            QMessageBox QPushButton:hover { border-color: #0969da; }

            QDialog#atharConfirmDialog { background: transparent; }
            QFrame#dialogCard {
                background-color: #ffffff;
                border: 1px solid #d0d7de;
                border-radius: 12px;
            }
            QLabel#dialogTitle { color: #1f2328; border: none; font-size: 16px; font-weight: 800; }
            QLabel#dialogText { color: #59636e; border: none; font-size: 12px; }
        )ATHAR");
    }

    return QString::fromUtf8(R"ATHAR(
        QMainWindow,
        QStackedWidget,
        QWidget#page {
            background-color: #0d1117;
        }

        QWidget {
            color: #e6edf3;
            font-family: "Segoe UI";
            font-size: 14px;
        }

        QFrame#sidebar {
            background-color: #161b22;
            border-right: 1px solid #30363d;
        }

        QLabel#appTitle { font-size: 22px; font-weight: 700; color: #ffffff; }
        QLabel#appSubtitle { color: #8b949e; font-size: 11px; }
        QLabel#pageTitle { font-size: 28px; font-weight: 700; color: #f0f6fc; }
        QLabel#pageDescription { color: #8b949e; font-size: 13px; }
        QLabel#cardTitle { color: #8b949e; font-size: 12px; font-weight: 600; }
        QLabel#cardValue { color: #f0f6fc; font-size: 28px; font-weight: 700; }
        QLabel#cardDescription { color: #7d8590; font-size: 11px; }
        QLabel#sectionTitle { font-size: 18px; font-weight: 700; color: #f0f6fc; }
        QLabel#fieldLabel { color: #b1bac4; font-size: 12px; font-weight: 600; }
        QLabel#mutedText { color: #8b949e; }

        QLabel#systemReady,
        QLabel#faultStatusOk {
            background-color: #12261e;
            color: #3fb950;
            border: 1px solid #238636;
            border-radius: 8px;
            padding: 8px 13px;
            font-weight: 700;
        }

        QLabel#systemRunning {
            background-color: #172a46;
            color: #58a6ff;
            border: 1px solid #1f6feb;
            border-radius: 8px;
            padding: 8px 13px;
            font-weight: 700;
        }

        QLabel#systemStopped,
        QLabel#faultStatusActive {
            background-color: #341a1e;
            color: #ff7b72;
            border: 1px solid #da3633;
            border-radius: 8px;
            padding: 8px 13px;
            font-weight: 700;
        }

        QFrame#card {
            background-color: #161b22;
            border: 1px solid #30363d;
            border-radius: 12px;
        }

        QFrame#serviceHealthRow,
        QFrame#networkMetricCard {
            background-color: #0d1117;
            border: 1px solid #30363d;
            border-radius: 8px;
        }

        QLabel#serviceName,
        QLabel#networkNodeName {
            color: #f0f6fc;
            font-weight: 700;
        }
        QLabel#serviceName { font-size: 13px; }
        QLabel#networkNodeName { font-size: 16px; }
        QLabel#serviceDetail,
        QLabel#networkMetricTitle,
        QLabel#networkNodeDetail,
        QLabel#networkNodeFault { color: #8b949e; font-size: 11px; }
        QLabel#serviceFaultActive { color: #d29922; font-size: 10px; font-weight: 700; }
        QLabel#networkMetricValue { color: #f0f6fc; font-size: 16px; font-weight: 700; }

        QLabel#networkClient {
            background-color: #172a46;
            color: #58a6ff;
            border: 1px solid #1f6feb;
            border-radius: 8px;
            padding: 7px;
            font-weight: 700;
        }
        QLabel#networkArrow { font-size: 21px; font-weight: 700; color: #58a6ff; padding: 0px; margin: 0px; }

        QLabel#panelInfoBox,
        QLabel#reportCodeBox,
        QLabel#reportInfoBox,
        QLabel#reportStatus {
            background-color: #0d1117;
            color: #c9d1d9;
            border: 1px solid #30363d;
            border-radius: 7px;
            padding: 10px 12px;
        }

        QLabel#reportCodeBox { font-family: Consolas; font-size: 12px; }
        QLabel#reportValue { color: #f0f6fc; font-size: 20px; font-weight: 800; }
        QLabel#reportFaultBox {
            background-color: #0d1117;
            color: #f0a33a;
            border: 1px solid #30363d;
            border-radius: 7px;
            padding: 10px 12px;
            font-weight: 700;
        }
        QLabel#reportBrand {
            background-color: #172a46;
            color: #58d6ff;
            border: 1px solid #1f9ee0;
            border-radius: 9px;
            padding: 12px;
            font-weight: 800;
            font-size: 16px;
        }

        QLabel#reportStatusSuccess,
        QLabel#feedbackSuccess {
            background-color: #12261e;
            color: #3fb950;
            border: 1px solid #238636;
            border-radius: 7px;
            padding: 8px 10px;
            font-size: 12px;
            font-weight: 700;
        }
        QLabel#reportStatusError,
        QLabel#feedbackError {
            background-color: #341a1e;
            color: #ff7b72;
            border: 1px solid #da3633;
            border-radius: 7px;
            padding: 8px 10px;
            font-size: 12px;
            font-weight: 700;
        }
        QLabel#feedbackNeutral {
            background-color: #0d1117;
            color: #8b949e;
            border: 1px solid #30363d;
            border-radius: 7px;
            padding: 9px 11px;
            font-size: 12px;
            font-weight: 600;
        }

        QPushButton#navButton {
            background-color: transparent;
            border: none;
            border-radius: 7px;
            padding: 12px 16px;
            text-align: left;
            color: #c9d1d9;
        }
        QPushButton#navButton:hover { background-color: #21262d; }
        QPushButton#navButton:checked { background-color: #1f6feb; color: #ffffff; font-weight: 700; }

        QPushButton#themeButton {
            background-color: #0d1117;
            color: #8b949e;
            border: 1px solid #30363d;
            border-radius: 6px;
            padding: 7px 10px;
            font-size: 12px;
            font-weight: 700;
        }
        QPushButton#themeButton:hover { border-color: #58a6ff; color: #58a6ff; }
        QPushButton#themeButton:checked { background-color: #1f6feb; color: #ffffff; border-color: #58a6ff; }

        QPushButton#primaryButton {
            background-color: #238636;
            border: 1px solid #2ea043;
            color: #ffffff;
            padding: 11px 18px;
            border-radius: 7px;
            font-weight: 700;
        }
        QPushButton#primaryButton:hover { background-color: #2ea043; }

        QPushButton#dangerButton {
            background-color: #da3633;
            border: 1px solid #f85149;
            color: #ffffff;
            padding: 11px 18px;
            border-radius: 7px;
            font-weight: 700;
        }
        QPushButton#dangerButton:hover { background-color: #f85149; }

        QPushButton#secondaryButton,
        QPushButton#selectorButton,
        QPushButton#stepButton,
        QPushButton#simulationStepButton {
            background-color: #21262d;
            border: 1px solid #30363d;
            color: #e6edf3;
            border-radius: 7px;
        }
        QPushButton#secondaryButton { padding: 11px 18px; }
        QPushButton#secondaryButton:hover,
        QPushButton#selectorButton:hover,
        QPushButton#stepButton:hover,
        QPushButton#simulationStepButton:hover {
            background-color: #30363d;
            border-color: #58a6ff;
        }

        QPushButton#selectorButton {
            padding: 10px 34px 10px 14px;
            text-align: left;
            min-height: 30px;
            font-weight: 600;
        }
        QPushButton#selectorButton::menu-indicator {
            subcontrol-origin: padding;
            subcontrol-position: center right;
            right: 12px;
        }
        QPushButton#stepButton {
            min-width: 24px; max-width: 24px; min-height: 30px; max-height: 30px;
            font-size: 18px; font-weight: 700; padding: 0px;
        }
        QPushButton#simulationStepButton {
            min-width: 40px; max-width: 40px; min-height: 40px; max-height: 40px;
            font-size: 20px; font-weight: 700; padding: 0px;
        }

        QSpinBox,
        QDoubleSpinBox,
        QListWidget,
        QTableWidget,
        QMenu {
            background-color: #0d1117;
            color: #f0f6fc;
            border: 1px solid #30363d;
        }
        QSpinBox,
        QDoubleSpinBox { border-radius: 6px; padding: 6px; min-height: 32px; }
        QSpinBox:focus,
        QDoubleSpinBox:focus { border-color: #58a6ff; }

        QListWidget,
        QTableWidget { border-radius: 7px; }
        QListWidget { padding: 6px; }
        QListWidget::item { padding: 7px; border-bottom: 1px solid #21262d; }

        QTableWidget { alternate-background-color: #161b22; gridline-color: #30363d; }
        QTableWidget::item { padding: 8px; }
        QTableWidget::item:selected { background-color: #1f6feb; color: #ffffff; }
        QHeaderView::section {
            background-color: #21262d;
            color: #f0f6fc;
            border: none;
            border-right: 1px solid #30363d;
            border-bottom: 1px solid #30363d;
            padding: 10px;
            font-weight: 700;
        }

        QMenu { padding: 4px; margin: 0px; }
        QMenu::item { padding: 9px 32px 9px 12px; margin: 1px; border-radius: 4px; }
        QMenu::item:selected { background-color: #1f6feb; color: #ffffff; }

        QCheckBox { spacing: 8px; color: #e6edf3; padding-left: 10px; }

        QProgressBar {
            background-color: #0d1117;
            border: 1px solid #30363d;
            border-radius: 7px;
            text-align: center;
            color: #f0f6fc;
            min-height: 25px;
        }
        QProgressBar::chunk { background-color: #238636; border-radius: 6px; }

        QScrollArea { background: transparent; border: none; }

        QMessageBox { background-color: #161b22; }
        QMessageBox QLabel { color: #f0f6fc; min-width: 340px; font-size: 14px; }
        QMessageBox QPushButton {
            background-color: #21262d;
            color: #f0f6fc;
            border: 1px solid #30363d;
            border-radius: 6px;
            padding: 8px 18px;
            min-width: 90px;
            min-height: 24px;
        }
        QMessageBox QPushButton:hover { background-color: #30363d; border-color: #58a6ff; }

        QDialog#atharConfirmDialog { background: transparent; }
        QFrame#dialogCard {
            background-color: #161b22;
            border: 1px solid #30363d;
            border-radius: 12px;
        }
        QLabel#dialogTitle { color: #f0f6fc; border: none; font-size: 16px; font-weight: 800; }
        QLabel#dialogText { color: #8b949e; border: none; font-size: 12px; }
    )ATHAR");
}

void applyNativeTitleBarTheme(QWidget *window, bool light)
{
#ifdef Q_OS_WIN
    if (!window || !window->isWindow())
    {
        return;
    }

    HWND handle =
        reinterpret_cast<HWND>(
            window->winId()
        );

    if (!handle)
    {
        return;
    }

    BOOL darkMode =
        light ? FALSE : TRUE;

    constexpr DWORD immersiveDarkModeAttribute = 20;
    constexpr DWORD immersiveDarkModeAttributeLegacy = 19;
    constexpr DWORD borderColorAttribute = 34;
    constexpr DWORD captionColorAttribute = 35;
    constexpr DWORD textColorAttribute = 36;

    HRESULT darkModeResult =
        DwmSetWindowAttribute(
            handle,
            immersiveDarkModeAttribute,
            &darkMode,
            sizeof(darkMode)
        );

    if (FAILED(darkModeResult))
    {
        DwmSetWindowAttribute(
            handle,
            immersiveDarkModeAttributeLegacy,
            &darkMode,
            sizeof(darkMode)
        );
    }

    const COLORREF captionColor =
        light
            ? RGB(246, 248, 250)
            : RGB(13, 17, 23);

    const COLORREF textColor =
        light
            ? RGB(31, 35, 40)
            : RGB(240, 246, 252);

    const COLORREF borderColor =
        light
            ? RGB(208, 215, 222)
            : RGB(48, 54, 61);

    DwmSetWindowAttribute(
        handle,
        captionColorAttribute,
        &captionColor,
        sizeof(captionColor)
    );

    DwmSetWindowAttribute(
        handle,
        textColorAttribute,
        &textColor,
        sizeof(textColor)
    );

    DwmSetWindowAttribute(
        handle,
        borderColorAttribute,
        &borderColor,
        sizeof(borderColor)
    );

    SetWindowPos(
        handle,
        nullptr,
        0,
        0,
        0,
        0,
        SWP_NOMOVE |
            SWP_NOSIZE |
            SWP_NOZORDER |
            SWP_NOACTIVATE |
            SWP_FRAMECHANGED
    );
#else
    Q_UNUSED(window);
    Q_UNUSED(light);
#endif
}

void applyApplicationTheme(bool light)
{
    if (!qApp)
    {
        return;
    }

    const QString themeName = light ? "light" : "dark";

    qApp->setProperty(
        "atharTheme",
        themeName
    );

    qApp->setStyleSheet(
        themeStyleSheet(light)
    );

    QSettings settings;
    settings.setValue(
        "appearance/theme",
        themeName
    );

    const auto widgets = qApp->allWidgets();

    for (QWidget *widget : widgets)
    {
        if (!widget)
        {
            continue;
        }

        widget->style()->unpolish(widget);
        widget->style()->polish(widget);
        widget->update();

        if (widget->isWindow())
        {
            applyNativeTitleBarTheme(
                widget,
                light
            );
        }
    }
}

bool isLightTheme()
{
    return qApp &&
           qApp->property("atharTheme").toString() == "light";
}

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      pages(nullptr),
      simulationEngine(nullptr),
      historyManager(nullptr),
      historyPanel(nullptr),
      reportsPanel(nullptr),
      networkView(nullptr),
      simulationStatus(nullptr),
      totalRequestsValue(nullptr),
      successRateValue(nullptr),
      failedRequestsValue(nullptr),
      averageLatencyValue(nullptr),
      runtimeStatus(nullptr),
      simulationProgress(nullptr),
      requestsSpin(nullptr),
      rateSpin(nullptr),
      durationSpin(nullptr),
      servicesTable(nullptr)
{
    setWindowTitle("Athar Fault Lab 2");
    resize(1400, 850);
    setMinimumSize(1100, 700);

    UiLanguage::initialize();

    QSettings themeSettings;

    const bool useLightTheme =
        themeSettings
            .value(
                "appearance/theme",
                "dark"
            )
            .toString() ==
        "light";

    // Apply the saved theme before building the sidebar.
    // This makes the Dark/Light button selection match the
    // theme that was restored from the previous session.
    applyApplicationTheme(
        useLightTheme
    );

    simulationEngine = new SimulationEngine(this);

    historyManager =
        new HistoryManager(this);

    bool historyReady =
        historyManager->initialize();

    QWidget *root = new QWidget(this);

    QHBoxLayout *rootLayout = new QHBoxLayout(root);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    pages = new QStackedWidget(root);

    pages->addWidget(createDashboard());
    pages->addWidget(createSimulationPage());
    pages->addWidget(createServicesPage());

    pages->addWidget(
        new FaultPanel(
            simulationEngine,
            pages
        )
    );

    pages->addWidget(
        createNetworkViewPage()
    );

    historyPanel =
        new HistoryPanel(
            historyManager,
            pages
        );

    pages->addWidget(
        historyPanel
    );

    reportsPanel =
        new ReportsPanel(
            pages
        );

    pages->addWidget(
        reportsPanel
    );

    rootLayout->addWidget(createSidebar());
    rootLayout->addWidget(pages, 1);

    setCentralWidget(root);

    connect(
        simulationEngine,
        &SimulationEngine::simulationFinished,
        this,
        [this]()
        {
            if (!historyManager)
            {
                return;
            }

            const std::vector<Service> &services =
                simulationEngine->services();

            bool saved =
                historyManager->addSimulation(
                    simulationEngine->totalRequests(),
                    simulationEngine->processedRequests(),
                    simulationEngine->successfulRequests(),
                    simulationEngine->failedRequests(),
                    simulationEngine->successRate(),
                    simulationEngine->averageLatency(),
                    buildFaultSummary(
                        services
                    ),
                    buildServiceHealthJson(
                        services
                    )
                );

            if (saved)
            {
                if (historyPanel)
                {
                    historyPanel->refreshHistory();
                }

                refreshReportFromLatestHistory();
            }
            else
            {
                QMessageBox::warning(
                    this,
                    "History Error",
                    historyManager->lastError()
                );
            }
        }
    );

    if (!historyReady)
    {
        QMessageBox::warning(
            this,
            "History Database",
            QString(
                "The application started, but the history database "
                "could not be initialized.\n\n%1"
            )
                .arg(
                    historyManager->lastError()
                )
        );
    }

    refreshReportFromLatestHistory();

    // Re-apply after all widgets are created so every widget and
    // the native Windows title bar use the restored theme.
    applyApplicationTheme(
        useLightTheme
    );

    UiLanguage::refreshApplication();

    QTimer *languageRefreshTimer =
        new QTimer(this);

    languageRefreshTimer->setInterval(150);

    connect(
        languageRefreshTimer,
        &QTimer::timeout,
        this,
        []()
        {
            UiLanguage::refreshApplication();
        }
    );

    languageRefreshTimer->start();

}

QWidget *MainWindow::createSidebar()
{
    QFrame *sidebar = new QFrame;
    sidebar->setObjectName("sidebar");
    sidebar->setFixedWidth(240);

    QVBoxLayout *layout =
        new QVBoxLayout(sidebar);

    layout->setContentsMargins(
        18,
        25,
        18,
        20
    );

    layout->setSpacing(7);

    QLabel *title =
        new QLabel("ATHAR");

    title->setObjectName(
        "appTitle"
    );

    QLabel *subtitle =
        new QLabel("FAULT LAB 2");

    subtitle->setObjectName(
        "appSubtitle"
    );

    layout->addWidget(title);
    layout->addWidget(subtitle);
    layout->addSpacing(30);

    QPushButton *dashboardButton =
        new QPushButton("Dashboard");

    QPushButton *simulationButton =
        new QPushButton("Simulation");

    QPushButton *servicesButton =
        new QPushButton("Services");

    QPushButton *faultButton =
        new QPushButton("Fault Injection");

    QPushButton *networkButton =
        new QPushButton("Network View");

    QPushButton *historyButton =
        new QPushButton("History");

    QPushButton *reportsButton =
        new QPushButton("Reports");

    QPushButton *buttons[] = {
        dashboardButton,
        simulationButton,
        servicesButton,
        faultButton,
        networkButton,
        historyButton,
        reportsButton
    };

    for (int index = 0; index < 7; ++index)
    {
        buttons[index]->setProperty(
            "atharPageIndex",
            index
        );
    }

    for (QPushButton *button : buttons)
    {
        button->setObjectName(
            "navButton"
        );

        button->setCheckable(
            true
        );

        layout->addWidget(
            button
        );
    }

    dashboardButton->setChecked(
        true
    );

    auto clearChecks =
        [
            dashboardButton,
            simulationButton,
            servicesButton,
            faultButton,
            networkButton,
            historyButton,
            reportsButton
        ]()
        {
            dashboardButton->setChecked(false);
            simulationButton->setChecked(false);
            servicesButton->setChecked(false);
            faultButton->setChecked(false);
            networkButton->setChecked(false);
            historyButton->setChecked(false);
            reportsButton->setChecked(false);
        };

    connect(
        dashboardButton,
        &QPushButton::clicked,
        this,
        [this, clearChecks, dashboardButton]()
        {
            clearChecks();

            pages->setCurrentIndex(0);

            dashboardButton->setChecked(true);
        }
    );

    connect(
        simulationButton,
        &QPushButton::clicked,
        this,
        [this, clearChecks, simulationButton]()
        {
            clearChecks();

            pages->setCurrentIndex(1);

            simulationButton->setChecked(true);
        }
    );

    connect(
        servicesButton,
        &QPushButton::clicked,
        this,
        [this, clearChecks, servicesButton]()
        {
            clearChecks();

            pages->setCurrentIndex(2);

            servicesButton->setChecked(true);

            refreshServicesTable();
        }
    );

    connect(
        faultButton,
        &QPushButton::clicked,
        this,
        [this, clearChecks, faultButton]()
        {
            clearChecks();

            pages->setCurrentIndex(3);

            faultButton->setChecked(true);
        }
    );

    connect(
        networkButton,
        &QPushButton::clicked,
        this,
        [this, clearChecks, networkButton]()
        {
            clearChecks();

            pages->setCurrentIndex(4);

            networkButton->setChecked(true);

            if (networkView)
            {
                networkView->refresh();
            }
        }
    );

    connect(
        historyButton,
        &QPushButton::clicked,
        this,
        [this, clearChecks, historyButton]()
        {
            clearChecks();

            pages->setCurrentIndex(5);

            historyButton->setChecked(true);

            if (historyPanel)
            {
                historyPanel->refreshHistory();
            }
        }
    );

    connect(
        reportsButton,
        &QPushButton::clicked,
        this,
        [this, clearChecks, reportsButton]()
        {
            clearChecks();

            pages->setCurrentIndex(6);

            reportsButton->setChecked(true);

            refreshReportFromLatestHistory();
        }
    );

    layout->addSpacing(16);

    QLabel *themeLabel =
        new QLabel("Theme");

    themeLabel->setObjectName(
        "fieldLabel"
    );

    QHBoxLayout *themeLayout =
        new QHBoxLayout;

    themeLayout->setSpacing(6);

    QPushButton *darkThemeButton =
        new QPushButton("Dark");

    QPushButton *lightThemeButton =
        new QPushButton("Light");

    darkThemeButton->setObjectName(
        "themeButton"
    );

    lightThemeButton->setObjectName(
        "themeButton"
    );

    darkThemeButton->setCheckable(true);
    lightThemeButton->setCheckable(true);

    darkThemeButton->setChecked(
        !isLightTheme()
    );

    lightThemeButton->setChecked(
        isLightTheme()
    );

    themeLayout->addWidget(
        darkThemeButton
    );

    themeLayout->addWidget(
        lightThemeButton
    );

    layout->addWidget(themeLabel);
    layout->addLayout(themeLayout);

    connect(
        darkThemeButton,
        &QPushButton::clicked,
        this,
        [this, darkThemeButton, lightThemeButton]()
        {
            applyApplicationTheme(false);

            darkThemeButton->setChecked(true);
            lightThemeButton->setChecked(false);

            if (networkView)
            {
                networkView->refresh();
            }
        }
    );

    connect(
        lightThemeButton,
        &QPushButton::clicked,
        this,
        [this, darkThemeButton, lightThemeButton]()
        {
            applyApplicationTheme(true);

            darkThemeButton->setChecked(false);
            lightThemeButton->setChecked(true);

            if (networkView)
            {
                networkView->refresh();
            }
        }
    );

    layout->addSpacing(12);

    QLabel *languageLabel =
        new QLabel("Language");

    languageLabel->setObjectName(
        "fieldLabel"
    );

    QHBoxLayout *languageLayout =
        new QHBoxLayout;

    languageLayout->setSpacing(6);

    QPushButton *englishButton =
        new QPushButton("E");

    QPushButton *arabicButton =
        new QPushButton(QString::fromUtf8(u8"ع"));

    englishButton->setObjectName(
        "themeButton"
    );

    arabicButton->setObjectName(
        "themeButton"
    );

    englishButton->setCheckable(true);
    arabicButton->setCheckable(true);

    englishButton->setChecked(
        !UiLanguage::isArabic()
    );

    arabicButton->setChecked(
        UiLanguage::isArabic()
    );

    languageLayout->addWidget(
        englishButton
    );

    languageLayout->addWidget(
        arabicButton
    );

    layout->addWidget(languageLabel);
    layout->addLayout(languageLayout);

    connect(
        englishButton,
        &QPushButton::clicked,
        this,
        [englishButton, arabicButton]()
        {
            UiLanguage::setArabic(false);

            englishButton->setChecked(true);
            arabicButton->setChecked(false);

            UiLanguage::refreshApplication();
        }
    );

    connect(
        arabicButton,
        &QPushButton::clicked,
        this,
        [englishButton, arabicButton]()
        {
            UiLanguage::setArabic(true);

            englishButton->setChecked(false);
            arabicButton->setChecked(true);

            UiLanguage::refreshApplication();
        }
    );

    layout->addStretch();

    QLabel *version =
        new QLabel(
            "Athar Fault Lab 2\n"
            "Version 2.0\n\n"
            "Made by:\n"
            "abdulaziz alyousef"
        );

    version->setObjectName(
        "appSubtitle"
    );

    layout->addWidget(version);

    return sidebar;
}

QWidget *MainWindow::createDashboard()
{
    Dashboard *dashboard =
        new Dashboard(
            simulationEngine,
            pages
        );

    simulationStatus =
        dashboard->statusLabel();

    totalRequestsValue =
        dashboard->totalRequestsLabel();

    successRateValue =
        dashboard->successRateLabel();

    failedRequestsValue =
        dashboard->failedRequestsLabel();

    averageLatencyValue =
        dashboard->averageLatencyLabel();

    return dashboard;
}

QWidget *MainWindow::createSimulationPage()
{
    QWidget *page = new QWidget;
    page->setObjectName("page");

    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(35, 30, 35, 30);
    layout->setSpacing(20);

    QLabel *title = new QLabel("Simulation Control Center");
    title->setObjectName("pageTitle");

    QLabel *description = new QLabel(
        "Configure workload parameters and run the simulation engine."
    );
    description->setObjectName("pageDescription");

    layout->addWidget(title);
    layout->addWidget(description);

    QFrame *card = new QFrame;
    card->setObjectName("card");

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(25, 22, 25, 22);
    cardLayout->setSpacing(18);

    QLabel *sectionTitle = new QLabel("Simulation Parameters");
    sectionTitle->setObjectName("sectionTitle");
    cardLayout->addWidget(sectionTitle);

    QGridLayout *fields = new QGridLayout;
    fields->setHorizontalSpacing(25);
    fields->setVerticalSpacing(15);

    auto createSimulationStepEditor =
        [this](QSpinBox *spinBox) -> QWidget *
        {
            QWidget *container = new QWidget;

            QHBoxLayout *editorLayout =
                new QHBoxLayout(container);

            editorLayout->setContentsMargins(0, 0, 0, 0);
            editorLayout->setSpacing(8);

            QPushButton *minusButton =
                new QPushButton("-");

            minusButton->setObjectName(
                "simulationStepButton"
            );
            minusButton->setToolTip("Decrease");

            QPushButton *plusButton =
                new QPushButton("+");

            plusButton->setObjectName(
                "simulationStepButton"
            );
            plusButton->setToolTip("Increase");

            spinBox->setButtonSymbols(
                QAbstractSpinBox::NoButtons
            );

            spinBox->setAlignment(
                Qt::AlignCenter
            );

            spinBox->setMinimumHeight(40);

            editorLayout->addWidget(minusButton);
            editorLayout->addWidget(spinBox, 1);
            editorLayout->addWidget(plusButton);

            connect(
                minusButton,
                &QPushButton::clicked,
                spinBox,
                &QAbstractSpinBox::stepDown
            );

            connect(
                plusButton,
                &QPushButton::clicked,
                spinBox,
                &QAbstractSpinBox::stepUp
            );

            return container;
        };

    QLabel *requestsLabel = new QLabel("Total Requests");
    requestsLabel->setObjectName("fieldLabel");

    requestsSpin = new QSpinBox;
    requestsSpin->setRange(100, 1000000);
    requestsSpin->setValue(10000);
    requestsSpin->setSingleStep(1000);

    QLabel *rateLabel = new QLabel("Arrival Rate (req/s)");
    rateLabel->setObjectName("fieldLabel");

    rateSpin = new QSpinBox;
    rateSpin->setRange(1, 10000);
    rateSpin->setValue(100);
    rateSpin->setSingleStep(1);

    QLabel *durationLabel = new QLabel("Duration (seconds)");
    durationLabel->setObjectName("fieldLabel");

    durationSpin = new QSpinBox;
    durationSpin->setRange(1, 3600);
    durationSpin->setValue(60);
    durationSpin->setSingleStep(1);

    fields->addWidget(requestsLabel, 0, 0);
    fields->addWidget(
        createSimulationStepEditor(requestsSpin),
        1,
        0
    );

    fields->addWidget(rateLabel, 0, 1);
    fields->addWidget(
        createSimulationStepEditor(rateSpin),
        1,
        1
    );

    fields->addWidget(durationLabel, 2, 0);
    fields->addWidget(
        createSimulationStepEditor(durationSpin),
        3,
        0
    );

    cardLayout->addLayout(fields);

    QHBoxLayout *controls = new QHBoxLayout;

    QPushButton *startButton =
        new QPushButton("Start Simulation");
    startButton->setObjectName("primaryButton");

    QPushButton *stopButton =
        new QPushButton("Stop");
    stopButton->setObjectName("dangerButton");

    QPushButton *resetButton =
        new QPushButton("Reset");
    resetButton->setObjectName("secondaryButton");

    controls->addWidget(startButton);
    controls->addWidget(stopButton);
    controls->addWidget(resetButton);
    controls->addStretch();

    cardLayout->addLayout(controls);
    layout->addWidget(card);

    QFrame *runtimeCard = new QFrame;
    runtimeCard->setObjectName("card");

    QVBoxLayout *runtimeLayout =
        new QVBoxLayout(runtimeCard);

    runtimeLayout->setContentsMargins(25, 22, 25, 22);
    runtimeLayout->setSpacing(15);

    QLabel *runtimeTitle = new QLabel("Runtime Monitor");
    runtimeTitle->setObjectName("sectionTitle");

    runtimeStatus = new QLabel(
        "Simulation engine is idle. "
        "Configure the parameters and press Start."
    );

    runtimeStatus->setObjectName("pageDescription");
    runtimeStatus->setWordWrap(true);

    simulationProgress = new QProgressBar;
    simulationProgress->setRange(0, 100);
    simulationProgress->setValue(0);
    simulationProgress->setFormat("%p%");
    simulationProgress->setTextVisible(true);

    runtimeLayout->addWidget(runtimeTitle);
    runtimeLayout->addWidget(runtimeStatus);
    runtimeLayout->addWidget(simulationProgress);
    runtimeLayout->addStretch();

    layout->addWidget(runtimeCard, 1);

    connect(
        startButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            simulationEngine->configure(
                requestsSpin->value(),
                rateSpin->value(),
                durationSpin->value()
            );

            simulationEngine->start();
        }
    );

    connect(
        stopButton,
        &QPushButton::clicked,
        simulationEngine,
        &SimulationEngine::stop
    );

    connect(
        resetButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            simulationEngine->reset();

            requestsSpin->setValue(10000);
            rateSpin->setValue(100);
            durationSpin->setValue(60);
        }
    );

    connect(
        simulationEngine,
        &SimulationEngine::statsUpdated,
        this,
        [this](
            int processed,
            int successful,
            int failed,
            double successRate,
            double averageLatency,
            int progress
        )
        {
            if (totalRequestsValue)
            {
                totalRequestsValue->setText(
                    QString::number(processed)
                );
            }

            if (successRateValue)
            {
                successRateValue->setText(
                    QString::number(
                        successRate,
                        'f',
                        1
                    ) + "%"
                );
            }

            if (failedRequestsValue)
            {
                failedRequestsValue->setText(
                    QString::number(failed)
                );
            }

            if (averageLatencyValue)
            {
                averageLatencyValue->setText(
                    QString::number(
                        averageLatency,
                        'f',
                        1
                    ) + " ms"
                );
            }

            if (simulationProgress)
            {
                simulationProgress->setValue(progress);
            }

            if (runtimeStatus)
            {
                runtimeStatus->setText(
                    QString(
                        "Processed: %1 | "
                        "Successful: %2 | "
                        "Failed: %3"
                    )
                    .arg(processed)
                    .arg(successful)
                    .arg(failed)
                );
            }
        }
    );

    connect(
        simulationEngine,
        &SimulationEngine::statusChanged,
        this,
        [this](const QString &status)
        {
            if (!simulationStatus)
            {
                return;
            }

            if (status == "RUNNING")
            {
                simulationStatus->setText(
                    "SIMULATION RUNNING"
                );

                simulationStatus->setObjectName(
                    "systemRunning"
                );

                if (runtimeStatus)
                {
                    runtimeStatus->setText(
                        "Generating and processing requests..."
                    );
                }
            }
            else if (status == "STOPPED")
            {
                simulationStatus->setText(
                    "SIMULATION STOPPED"
                );

                simulationStatus->setObjectName(
                    "systemStopped"
                );

                if (runtimeStatus)
                {
                    runtimeStatus->setText(
                        "Simulation stopped by the user."
                    );
                }
            }
            else if (status == "READY")
            {
                simulationStatus->setText(
                    "SYSTEM READY"
                );

                simulationStatus->setObjectName(
                    "systemReady"
                );

                if (runtimeStatus)
                {
                    runtimeStatus->setText(
                        "System reset and ready."
                    );
                }

                if (simulationProgress)
                {
                    simulationProgress->setValue(0);
                }
            }
            else if (status == "FINISHED")
            {
                simulationStatus->setText(
                    "SIMULATION FINISHED"
                );

                simulationStatus->setObjectName(
                    "systemReady"
                );

                if (runtimeStatus)
                {
                    runtimeStatus->setText(
                        "Simulation completed successfully."
                    );
                }

                if (simulationProgress)
                {
                    simulationProgress->setValue(100);
                }
            }

            simulationStatus->style()->unpolish(
                simulationStatus
            );

            simulationStatus->style()->polish(
                simulationStatus
            );

            simulationStatus->update();
        }
    );

    return page;
}

QWidget *MainWindow::createServicesPage()
{
    QWidget *page = new QWidget;
    page->setObjectName("page");

    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(35, 30, 35, 30);
    layout->setSpacing(20);

    QLabel *title = new QLabel("Services");
    title->setObjectName("pageTitle");

    QLabel *description = new QLabel(
        "Configure workers, failures, latency and availability "
        "for each infrastructure service."
    );
    description->setObjectName("pageDescription");
    description->setWordWrap(true);

    layout->addWidget(title);
    layout->addWidget(description);

    QFrame *card = new QFrame;
    card->setObjectName("card");

    QVBoxLayout *cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(25, 22, 25, 22);
    cardLayout->setSpacing(15);

    QLabel *sectionTitle = new QLabel("Infrastructure Services");
    sectionTitle->setObjectName("sectionTitle");
    cardLayout->addWidget(sectionTitle);

    QLabel *helpText = new QLabel(
        "Active Workers are calculated automatically: "
        "Total Workers - Failed Workers."
    );
    helpText->setObjectName("pageDescription");
    helpText->setWordWrap(true);
    cardLayout->addWidget(helpText);

    servicesTable = new QTableWidget;
    servicesTable->setColumnCount(7);
    servicesTable->setHorizontalHeaderLabels(
        {
            "Service",
            "Total Workers",
            "Failed Workers",
            "Active Workers",
            "Base Latency (ms)",
            "Failure %",
            "Available"
        }
    );

    servicesTable->verticalHeader()->setVisible(false);

    QHeaderView *header = servicesTable->horizontalHeader();

    header->setMinimumSectionSize(115);
    header->setStretchLastSection(false);

    for (int column = 0; column < 7; ++column)
    {
        header->setSectionResizeMode(
            column,
            QHeaderView::Stretch
        );
    }

    servicesTable->setHorizontalScrollMode(
        QAbstractItemView::ScrollPerPixel
    );

    servicesTable->setSelectionMode(QAbstractItemView::NoSelection);
    servicesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    servicesTable->setAlternatingRowColors(true);

    cardLayout->addWidget(servicesTable);

    QHBoxLayout *buttons = new QHBoxLayout;

    QPushButton *applyButton = new QPushButton("Apply Changes");
    applyButton->setObjectName("primaryButton");

    QPushButton *defaultsButton = new QPushButton("Restore Defaults");
    defaultsButton->setObjectName("secondaryButton");

    buttons->addWidget(applyButton);
    buttons->addWidget(defaultsButton);
    buttons->addStretch();

    cardLayout->addLayout(buttons);

    QLabel *servicesFeedback =
        new QLabel(
            "Service configuration is ready."
        );

    servicesFeedback->setWordWrap(
        true
    );

    servicesFeedback->setObjectName(
        "feedbackNeutral"
    );

    cardLayout->addWidget(
        servicesFeedback
    );

    layout->addWidget(card, 1);

    refreshServicesTable();

    connect(
        applyButton,
        &QPushButton::clicked,
        this,
        [this, servicesFeedback]()
        {
            auto showFeedback =
                [servicesFeedback](
                    const QString &message,
                    bool success
                )
                {
                    servicesFeedback->setText(
                        message
                    );
                    servicesFeedback->setObjectName(
                        success
                            ? "feedbackSuccess"
                            : "feedbackError"
                    );

                    servicesFeedback->style()->unpolish(
                        servicesFeedback
                    );

                    servicesFeedback->style()->polish(
                        servicesFeedback
                    );
                };

            if (simulationEngine->isRunning())
            {
                showFeedback(
                    "Stop the simulation before changing services.",
                    false
                );

                return;
            }

            const std::vector<Service> &services =
                simulationEngine->services();

            for (
                int row = 0;
                row < static_cast<int>(services.size());
                ++row
            )
            {
                QTableWidgetItem *serviceItem =
                    servicesTable->item(row, 0);

                QWidget *totalCell =
                    servicesTable->cellWidget(row, 1);

                QWidget *failedCell =
                    servicesTable->cellWidget(row, 2);

                QWidget *latencyCell =
                    servicesTable->cellWidget(row, 4);

                QWidget *failureCell =
                    servicesTable->cellWidget(row, 5);

                QSpinBox *totalWorkersSpin =
                    totalCell
                        ? totalCell->findChild<QSpinBox *>("totalWorkersSpin")
                        : nullptr;

                QSpinBox *failedWorkersSpin =
                    failedCell
                        ? failedCell->findChild<QSpinBox *>("failedWorkersSpin")
                        : nullptr;

                QDoubleSpinBox *latencySpin =
                    latencyCell
                        ? latencyCell->findChild<QDoubleSpinBox *>("latencySpin")
                        : nullptr;

                QDoubleSpinBox *failureSpin =
                    failureCell
                        ? failureCell->findChild<QDoubleSpinBox *>("failureSpin")
                        : nullptr;

                QCheckBox *availableCheck =
                    qobject_cast<QCheckBox *>(
                        servicesTable->cellWidget(row, 6)
                    );

                if (
                    !serviceItem ||
                    !totalWorkersSpin ||
                    !failedWorkersSpin ||
                    !latencySpin ||
                    !failureSpin ||
                    !availableCheck
                )
                {
                    showFeedback(
                        "One of the service controls is missing.",
                        false
                    );

                    return;
                }

                QString id =
                    serviceItem->data(
                        Qt::ItemDataRole::UserRole
                    ).toString();

                bool updated =
                    simulationEngine->updateService(
                        id,
                        totalWorkersSpin->value(),
                        failedWorkersSpin->value(),
                        latencySpin->value(),
                        failureSpin->value() / 100.0,
                        availableCheck->isChecked()
                    );

                if (!updated)
                {
                    showFeedback(
                        "The service configuration could not be updated.",
                        false
                    );

                    return;
                }
            }

            refreshServicesTable();

            showFeedback(
                "✓ Service configuration applied successfully.",
                true
            );
        }
    );

    connect(
        defaultsButton,
        &QPushButton::clicked,
        this,
        [this, servicesFeedback]()
        {
            if (simulationEngine->isRunning())
            {
                servicesFeedback->setText(
                    "Stop the simulation before restoring defaults."
                );

                servicesFeedback->setObjectName(
                    "feedbackError"
                );

                servicesFeedback->style()->unpolish(
                    servicesFeedback
                );

                servicesFeedback->style()->polish(
                    servicesFeedback
                );

                return;
            }

            simulationEngine->restoreDefaultServices();

            refreshServicesTable();

            servicesFeedback->setText(
                "✓ Default service configuration restored."
            );

            servicesFeedback->setObjectName(
                "feedbackSuccess"
            );

            servicesFeedback->style()->unpolish(
                servicesFeedback
            );

            servicesFeedback->style()->polish(
                servicesFeedback
            );
        }
    );

    return page;
}

void MainWindow::refreshServicesTable()
{
    if (!servicesTable || !simulationEngine)
    {
        return;
    }

    const std::vector<Service> &services =
        simulationEngine->services();

    servicesTable->clearContents();
    servicesTable->setRowCount(
        static_cast<int>(services.size())
    );

    auto createStepEditor =
        [this](
            QAbstractSpinBox *spinBox,
            const QString &unit
        ) -> QWidget *
        {
            QWidget *container = new QWidget;
            container->setLayoutDirection(Qt::LeftToRight);

            QHBoxLayout *layout =
                new QHBoxLayout(container);

            layout->setContentsMargins(3, 4, 3, 4);
            layout->setSpacing(3);
            layout->setDirection(QBoxLayout::LeftToRight);

            QPushButton *minusButton =
                new QPushButton("-");

            minusButton->setObjectName("stepButton");
            minusButton->setToolTip("Decrease");

            QPushButton *plusButton =
                new QPushButton("+");

            plusButton->setObjectName("stepButton");
            plusButton->setToolTip("Increase");

            spinBox->setButtonSymbols(
                QAbstractSpinBox::NoButtons
            );

            layout->addWidget(minusButton);
            layout->addWidget(spinBox, 1);

            if (!unit.isEmpty())
            {
                QLabel *unitLabel =
                    new QLabel(unit);

                unitLabel->setAlignment(
                    Qt::AlignCenter
                );

                unitLabel->setObjectName(
                    "mutedText"
                );

                unitLabel->setMinimumWidth(
                    unit == "%" ? 14 : 22
                );

                layout->addWidget(unitLabel);
            }

            layout->addWidget(plusButton);

            connect(
                minusButton,
                &QPushButton::clicked,
                spinBox,
                &QAbstractSpinBox::stepDown
            );

            connect(
                plusButton,
                &QPushButton::clicked,
                spinBox,
                &QAbstractSpinBox::stepUp
            );

            return container;
        };

    for (
        int row = 0;
        row < static_cast<int>(services.size());
        ++row
    )
    {
        const Service &service =
            services[row];

        QTableWidgetItem *serviceItem =
            new QTableWidgetItem(service.name());

        serviceItem->setToolTip(
            service.name()
        );

        serviceItem->setData(
            Qt::ItemDataRole::UserRole,
            service.id()
        );

        serviceItem->setTextAlignment(
            Qt::AlignCenter
        );

        serviceItem->setFlags(
            Qt::ItemFlag::ItemIsEnabled
        );

        servicesTable->setItem(
            row,
            0,
            serviceItem
        );

        QSpinBox *totalWorkersSpin =
            new QSpinBox;

        totalWorkersSpin->setObjectName(
            "totalWorkersSpin"
        );

        totalWorkersSpin->setRange(1, 256);
        totalWorkersSpin->setValue(
            service.totalWorkers()
        );
        totalWorkersSpin->setSingleStep(1);
        totalWorkersSpin->setMinimumWidth(50);
        totalWorkersSpin->setMaximumWidth(62);
        totalWorkersSpin->setAlignment(
            Qt::AlignCenter
        );

        servicesTable->setCellWidget(
            row,
            1,
            createStepEditor(totalWorkersSpin, "")
        );

        QSpinBox *failedWorkersSpin =
            new QSpinBox;

        failedWorkersSpin->setObjectName(
            "failedWorkersSpin"
        );

        failedWorkersSpin->setRange(
            0,
            service.totalWorkers()
        );

        failedWorkersSpin->setValue(
            service.failedWorkers()
        );

        failedWorkersSpin->setSingleStep(1);
        failedWorkersSpin->setMinimumWidth(50);
        failedWorkersSpin->setMaximumWidth(62);
        failedWorkersSpin->setAlignment(
            Qt::AlignCenter
        );

        servicesTable->setCellWidget(
            row,
            2,
            createStepEditor(failedWorkersSpin, "")
        );

        QLabel *activeWorkersLabel =
            new QLabel(
                QString::number(
                    service.activeWorkers()
                )
            );

        activeWorkersLabel->setAlignment(
            Qt::AlignCenter
        );

        auto updateActiveStyle =
            [activeWorkersLabel](
                int activeWorkers,
                int failedWorkers
            )
            {
                activeWorkersLabel->setText(
                    QString::number(activeWorkers)
                );

                if (activeWorkers == 0)
                {
                    activeWorkersLabel->setStyleSheet(
                        "font-weight: 700;"
                        "color: #f85149;"
                    );
                }
                else if (failedWorkers > 0)
                {
                    activeWorkersLabel->setStyleSheet(
                        "font-weight: 700;"
                        "color: #d29922;"
                    );
                }
                else
                {
                    activeWorkersLabel->setStyleSheet(
                        "font-weight: 700;"
                        "color: #3fb950;"
                    );
                }
            };

        updateActiveStyle(
            service.activeWorkers(),
            service.failedWorkers()
        );

        servicesTable->setCellWidget(
            row,
            3,
            activeWorkersLabel
        );

        QDoubleSpinBox *latencySpin =
            new QDoubleSpinBox;

        latencySpin->setObjectName(
            "latencySpin"
        );

        latencySpin->setRange(
            0.1,
            10000.0
        );

        latencySpin->setDecimals(1);
        latencySpin->setSingleStep(1.0);
        latencySpin->setSuffix(" ms");
        latencySpin->setValue(
            service.baseLatencyMs()
        );

        latencySpin->setMinimumWidth(64);
        latencySpin->setMaximumWidth(78);
        latencySpin->setAlignment(
            Qt::AlignCenter
        );

        servicesTable->setCellWidget(
            row,
            4,
            createStepEditor(
                latencySpin,
                ""
            )
        );

        QDoubleSpinBox *failureSpin =
            new QDoubleSpinBox;

        failureSpin->setObjectName(
            "failureSpin"
        );

        failureSpin->setRange(
            0.0,
            100.0
        );

        failureSpin->setDecimals(1);
        failureSpin->setSingleStep(1.0);
        failureSpin->setSuffix(" %");

        failureSpin->setValue(
            service.failureProbability() *
            100.0
        );

        failureSpin->setMinimumWidth(64);
        failureSpin->setMaximumWidth(78);
        failureSpin->setAlignment(
            Qt::AlignCenter
        );

        servicesTable->setCellWidget(
            row,
            5,
            createStepEditor(
                failureSpin,
                ""
            )
        );

        QCheckBox *availableCheck =
            new QCheckBox;

        availableCheck->setChecked(
            service.isAvailable()
        );

        availableCheck->setText(
            service.isAvailable()
                ? "Online"
                : "Offline"
        );

        servicesTable->setCellWidget(
            row,
            6,
            availableCheck
        );

        connect(
            totalWorkersSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            [
                failedWorkersSpin,
                activeWorkersLabel,
                updateActiveStyle
            ](int totalWorkers)
            {
                failedWorkersSpin->setMaximum(
                    totalWorkers
                );

                int failedWorkers =
                    failedWorkersSpin->value();

                int activeWorkers =
                    totalWorkers -
                    failedWorkers;

                updateActiveStyle(
                    activeWorkers,
                    failedWorkers
                );
            }
        );

        connect(
            failedWorkersSpin,
            QOverload<int>::of(&QSpinBox::valueChanged),
            this,
            [
                totalWorkersSpin,
                updateActiveStyle
            ](int failedWorkers)
            {
                int activeWorkers =
                    totalWorkersSpin->value() -
                    failedWorkers;

                updateActiveStyle(
                    activeWorkers,
                    failedWorkers
                );
            }
        );

        connect(
            availableCheck,
            &QCheckBox::toggled,
            this,
            [availableCheck](bool checked)
            {
                availableCheck->setText(
                    checked
                        ? "Online"
                        : "Offline"
                );
            }
        );
    }

    servicesTable->resizeRowsToContents();
}

void MainWindow::refreshReportFromLatestHistory()
{
    if (
        !historyManager ||
        !reportsPanel
    )
    {
        return;
    }

    QVector<SimulationHistoryRecord> records =
        historyManager->history();

    if (records.isEmpty())
    {
        reportsPanel->setReportData(
            0,
            "No completed run",
            0,
            0,
            0,
            0,
            0.0,
            0.0,
            "Complete a simulation first. "
            "The newest saved History run will appear here automatically.",
            "",
            ""
        );

        return;
    }

    const SimulationHistoryRecord &record =
        records.first();

    reportsPanel->setReportData(
        record.id,
        record.dateTime,
        record.totalRequests,
        record.processedRequests,
        record.successfulRequests,
        record.failedRequests,
        record.successRate,
        record.averageLatency,
        QString(
            "Loaded from SQLite History. "
            "Run #%1 is the latest completed simulation."
        )
            .arg(
                record.id
            ),
        record.faultSummary,
        record.serviceHealthJson
    );
}

QWidget *MainWindow::createNetworkViewPage()
{
    networkView =
        new NetworkView(
            simulationEngine,
            pages
        );

    return networkView;
}

QWidget *MainWindow::createStatCard(
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
        130
    );

    QVBoxLayout *layout =
        new QVBoxLayout(card);

    layout->setContentsMargins(
        18,
        16,
        18,
        16
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

    if (
        valueOutput != nullptr
    )
    {
        *valueOutput =
            valueLabel;
    }

    layout->addWidget(
        titleLabel
    );

    layout->addWidget(
        valueLabel
    );

    layout->addWidget(
        descriptionLabel
    );

    return card;
}