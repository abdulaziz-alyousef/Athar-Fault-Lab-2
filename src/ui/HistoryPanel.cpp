#include "HistoryPanel.h"

#include "ReportsPanel.h"
#include "UiLanguage.h"
#include "../storage/HistoryManager.h"

#include <QAbstractItemView>
#include <QDialog>
#include <QFrame>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QStackedWidget>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

namespace
{
bool confirmClearHistory(QWidget *parent)
{
    QDialog dialog(parent);

    dialog.setObjectName(
        "atharConfirmDialog"
    );

    dialog.setModal(true);

    dialog.setWindowFlags(
        Qt::Dialog |
        Qt::FramelessWindowHint
    );

    dialog.setAttribute(
        Qt::WA_TranslucentBackground,
        true
    );

    QVBoxLayout *outer =
        new QVBoxLayout(&dialog);

    outer->setContentsMargins(
        8,
        8,
        8,
        8
    );

    QFrame *card =
        new QFrame;

    card->setObjectName(
        "dialogCard"
    );

    card->setMinimumWidth(
        500
    );

    QVBoxLayout *layout =
        new QVBoxLayout(card);

    layout->setContentsMargins(
        24,
        22,
        24,
        22
    );

    layout->setSpacing(
        14
    );

    QLabel *title =
        new QLabel(
            "Clear History"
        );

    title->setObjectName(
        "dialogTitle"
    );

    QLabel *message =
        new QLabel(
            "Delete all saved simulation runs?"
        );

    message->setObjectName(
        "dialogTitle"
    );

    QLabel *description =
        new QLabel(
            "This permanently removes all locally saved SQLite history. "
            "Previously exported PNG, JPG and PDF reports are not deleted."
        );

    description->setObjectName(
        "dialogText"
    );

    description->setWordWrap(
        true
    );

    QHBoxLayout *actions =
        new QHBoxLayout;

    QPushButton *cancelButton =
        new QPushButton(
            "Cancel"
        );

    cancelButton->setObjectName(
        "secondaryButton"
    );

    QPushButton *deleteButton =
        new QPushButton(
            "Delete All"
        );

    deleteButton->setObjectName(
        "dangerButton"
    );

    actions->addStretch();
    actions->addWidget(cancelButton);
    actions->addWidget(deleteButton);

    layout->addWidget(title);
    layout->addWidget(message);
    layout->addWidget(description);
    layout->addSpacing(4);
    layout->addLayout(actions);

    outer->addWidget(card);

    QObject::connect(
        cancelButton,
        &QPushButton::clicked,
        &dialog,
        &QDialog::reject
    );

    QObject::connect(
        deleteButton,
        &QPushButton::clicked,
        &dialog,
        &QDialog::accept
    );

    dialog.adjustSize();

    UiLanguage::refreshApplication();

    if (parent && parent->window())
    {
        QRect parentRect =
            parent->window()->geometry();

        dialog.move(
            parentRect.center() -
            dialog.rect().center()
        );
    }

    return dialog.exec() ==
           QDialog::Accepted;
}
}

HistoryPanel::HistoryPanel(
    HistoryManager *manager,
    QWidget *parent
)
    : QWidget(parent),
      m_manager(manager),
      m_countLabel(nullptr),
      m_statusLabel(nullptr),
      m_openReportButton(nullptr),
      m_table(nullptr)
{
    setObjectName("page");

    QVBoxLayout *mainLayout =
        new QVBoxLayout(this);

    mainLayout->setContentsMargins(
        35,
        30,
        35,
        30
    );

    mainLayout->setSpacing(18);

    QHBoxLayout *headerLayout =
        new QHBoxLayout;

    QVBoxLayout *headerText =
        new QVBoxLayout;

    QLabel *title =
        new QLabel("History");

    title->setObjectName(
        "pageTitle"
    );

    QLabel *description =
        new QLabel(
            "Saved simulation runs stored locally in SQLite. "
            "Select any run to open its complete report."
        );

    description->setObjectName(
        "pageDescription"
    );

    description->setWordWrap(true);

    headerText->addWidget(title);
    headerText->addWidget(description);

    m_countLabel =
        new QLabel("0 RUNS");

    m_countLabel->setObjectName(
        "countBadge"
    );

    headerLayout->addLayout(headerText);
    headerLayout->addStretch();
    headerLayout->addWidget(m_countLabel);

    mainLayout->addLayout(
        headerLayout
    );

    QFrame *card =
        new QFrame;

    card->setObjectName("card");

    QVBoxLayout *cardLayout =
        new QVBoxLayout(card);

    cardLayout->setContentsMargins(
        22,
        20,
        22,
        20
    );

    cardLayout->setSpacing(14);

    QHBoxLayout *toolbar =
        new QHBoxLayout;

    QLabel *sectionTitle =
        new QLabel(
            "Simulation Runs"
        );

    sectionTitle->setObjectName(
        "sectionTitle"
    );

    m_openReportButton =
        new QPushButton(
            "Open Report"
        );

    m_openReportButton->setObjectName(
        "primaryButton"
    );

    m_openReportButton->setEnabled(
        false
    );

    m_openReportButton->setToolTip(
        "Open the selected saved run in Reports"
    );

    QPushButton *refreshButton =
        new QPushButton(
            "Refresh"
        );

    refreshButton->setObjectName(
        "secondaryButton"
    );

    QPushButton *clearButton =
        new QPushButton(
            "Clear History"
        );

    clearButton->setObjectName(
        "dangerButton"
    );

    toolbar->addWidget(sectionTitle);
    toolbar->addStretch();
    toolbar->addWidget(m_openReportButton);
    toolbar->addWidget(refreshButton);
    toolbar->addWidget(clearButton);

    cardLayout->addLayout(toolbar);

    m_statusLabel =
        new QLabel(
            "History is ready."
        );

    m_statusLabel->setObjectName(
        "pageDescription"
    );

    m_statusLabel->setWordWrap(true);

    cardLayout->addWidget(
        m_statusLabel
    );

    m_table =
        new QTableWidget;

    m_table->setColumnCount(8);

    m_table->setHorizontalHeaderLabels(
        {
            "Run",
            "Date / Time",
            "Total",
            "Processed",
            "Successful",
            "Failed",
            "Success Rate",
            "Avg. Latency"
        }
    );

    m_table->verticalHeader()->setVisible(
        false
    );

    m_table->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
    );

    m_table->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );

    m_table->setSelectionMode(
        QAbstractItemView::SingleSelection
    );

    m_table->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );

    m_table->setAlternatingRowColors(
        true
    );

    m_table->setSortingEnabled(
        false
    );

    cardLayout->addWidget(
        m_table,
        1
    );

    mainLayout->addWidget(
        card,
        1
    );

    connect(
        refreshButton,
        &QPushButton::clicked,
        this,
        &HistoryPanel::refreshHistory
    );

    connect(
        m_openReportButton,
        &QPushButton::clicked,
        this,
        &HistoryPanel::openSelectedReport
    );

    connect(
        m_table,
        &QTableWidget::itemSelectionChanged,
        this,
        [this]()
        {
            bool selected =
                m_table &&
                m_table->currentRow() >= 0;

            if (m_openReportButton)
            {
                m_openReportButton->setEnabled(
                    selected
                );
            }

            if (selected && m_statusLabel)
            {
                QTableWidgetItem *runItem =
                    m_table->item(
                        m_table->currentRow(),
                        0
                    );

                if (runItem)
                {
                    m_statusLabel->setText(
                        QString(
                            "%1 selected. Press Open Report or double-click the row."
                        ).arg(runItem->text())
                    );
                }
            }
        }
    );

    connect(
        m_table,
        &QTableWidget::cellDoubleClicked,
        this,
        [this](int, int)
        {
            openSelectedReport();
        }
    );

    connect(
        clearButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            if (!m_manager)
            {
                return;
            }

            QVector<SimulationHistoryRecord> records =
                m_manager->history();

            if (records.isEmpty())
            {
                m_statusLabel->setText(
                    "History is already empty."
                );

                return;
            }

            if (!confirmClearHistory(this))
            {
                return;
            }

            if (!m_manager->clearHistory())
            {
                m_statusLabel->setText(
                    "History could not be cleared: " +
                    m_manager->lastError()
                );

                return;
            }

            refreshHistory();

            QStackedWidget *stack =
                qobject_cast<QStackedWidget *>(
                    parentWidget()
                );

            if (stack)
            {
                ReportsPanel *reportsPanel =
                    stack->findChild<ReportsPanel *>(
                        QString(),
                        Qt::FindDirectChildrenOnly
                    );

                if (reportsPanel)
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
                        "History was cleared. Complete a simulation to create a new report.",
                        "",
                        ""
                    );
                }
            }
        }
    );

    refreshHistory();
}

void HistoryPanel::refreshHistory()
{
    if (!m_manager || !m_table)
    {
        return;
    }

    QVector<SimulationHistoryRecord> records =
        m_manager->history();

    m_table->clearContents();
    m_table->setRowCount(records.size());

    if (m_openReportButton)
    {
        m_openReportButton->setEnabled(false);
    }

    for (
        int row = 0;
        row < records.size();
        ++row
    )
    {
        const SimulationHistoryRecord &record =
            records[row];

        QStringList values = {
            QString("#%1").arg(record.id),
            record.dateTime,
            QString::number(record.totalRequests),
            QString::number(record.processedRequests),
            QString::number(record.successfulRequests),
            QString::number(record.failedRequests),
            QString::number(
                record.successRate,
                'f',
                1
            ) + "%",
            QString::number(
                record.averageLatency,
                'f',
                1
            ) + " ms"
        };

        for (
            int column = 0;
            column < values.size();
            ++column
        )
        {
            QTableWidgetItem *item =
                new QTableWidgetItem(
                    values[column]
                );

            item->setTextAlignment(
                Qt::AlignCenter
            );

            if (column == 0)
            {
                item->setData(
                    Qt::UserRole,
                    record.id
                );
            }

            m_table->setItem(
                row,
                column,
                item
            );
        }
    }

    m_countLabel->setText(
        QString("%1 RUNS")
            .arg(records.size())
    );

    if (records.isEmpty())
    {
        m_statusLabel->setText(
            "No saved simulation runs yet. Complete a simulation to create the first record."
        );
    }
    else
    {
        m_statusLabel->setText(
            QString(
                "Loaded %1 saved simulation run(s). Select a row to inspect its report."
            ).arg(records.size())
        );
    }

    m_table->resizeRowsToContents();
}

void HistoryPanel::openSelectedReport()
{
    if (!m_manager || !m_table)
    {
        return;
    }

    int row =
        m_table->currentRow();

    if (row < 0)
    {
        m_statusLabel->setText(
            "Select a simulation run first."
        );

        return;
    }

    QTableWidgetItem *runItem =
        m_table->item(row, 0);

    if (!runItem)
    {
        m_statusLabel->setText(
            "The selected run could not be read."
        );

        return;
    }

    int runId =
        runItem->data(Qt::UserRole).toInt();

    QVector<SimulationHistoryRecord> records =
        m_manager->history();

    const SimulationHistoryRecord *selectedRecord =
        nullptr;

    for (
        const SimulationHistoryRecord &record :
        records
    )
    {
        if (record.id == runId)
        {
            selectedRecord = &record;
            break;
        }
    }

    if (!selectedRecord)
    {
        m_statusLabel->setText(
            QString(
                "Run #%1 could not be found. Refresh History and try again."
            ).arg(runId)
        );

        return;
    }

    QStackedWidget *stack =
        qobject_cast<QStackedWidget *>(
            parentWidget()
        );

    if (!stack)
    {
        m_statusLabel->setText(
            "Reports page could not be opened."
        );

        return;
    }

    ReportsPanel *reportsPanel =
        stack->findChild<ReportsPanel *>(
            QString(),
            Qt::FindDirectChildrenOnly
        );

    if (!reportsPanel)
    {
        m_statusLabel->setText(
            "Reports panel could not be found."
        );

        return;
    }

    reportsPanel->setReportData(
        selectedRecord->id,
        selectedRecord->dateTime,
        selectedRecord->totalRequests,
        selectedRecord->processedRequests,
        selectedRecord->successfulRequests,
        selectedRecord->failedRequests,
        selectedRecord->successRate,
        selectedRecord->averageLatency,
        QString(
            "Loaded from SQLite History. Run #%1 was selected manually from History."
        ).arg(selectedRecord->id),
        selectedRecord->faultSummary,
        selectedRecord->serviceHealthJson
    );

    stack->setCurrentWidget(
        reportsPanel
    );

    QWidget *mainWindow =
        window();

    if (mainWindow)
    {
        QList<QPushButton *> navigationButtons =
            mainWindow->findChildren<QPushButton *>(
                "navButton"
            );

        for (
            QPushButton *button :
            navigationButtons
        )
        {
            if (!button)
            {
                continue;
            }

            button->setChecked(
                button->property(
                    "atharPageIndex"
                ).toInt() == 6
            );
        }
    }
}
