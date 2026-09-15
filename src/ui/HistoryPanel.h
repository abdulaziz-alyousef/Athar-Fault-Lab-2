#ifndef HISTORYPANEL_H
#define HISTORYPANEL_H

#include <QWidget>

class HistoryManager;
class QLabel;
class QPushButton;
class QTableWidget;

class HistoryPanel : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryPanel(
        HistoryManager *manager,
        QWidget *parent = nullptr
    );

    void refreshHistory();

private:
    void openSelectedReport();

    HistoryManager *m_manager;

    QLabel *m_countLabel;
    QLabel *m_statusLabel;

    QPushButton *m_openReportButton;

    QTableWidget *m_table;
};

#endif