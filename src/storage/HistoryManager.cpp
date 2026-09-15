#include "HistoryManager.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

HistoryManager::HistoryManager(
    QObject *parent
)
    : QObject(parent),
      m_connectionName(
          "athar_history_connection"
      )
{
}

HistoryManager::~HistoryManager()
{
    if (
        QSqlDatabase::contains(
            m_connectionName
        )
    )
    {
        {
            QSqlDatabase database =
                QSqlDatabase::database(
                    m_connectionName
                );

            database.close();
        }

        QSqlDatabase::removeDatabase(
            m_connectionName
        );
    }
}

QString HistoryManager::databasePath() const
{
    QString dataDirectory =
        QCoreApplication::applicationDirPath()
        + "/data";

    QDir directory;

    if (
        !directory.exists(
            dataDirectory
        )
    )
    {
        directory.mkpath(
            dataDirectory
        );
    }

    return dataDirectory
        + "/athar_history.db";
}

bool HistoryManager::initialize()
{
    QSqlDatabase database;

    if (
        QSqlDatabase::contains(
            m_connectionName
        )
    )
    {
        database =
            QSqlDatabase::database(
                m_connectionName
            );
    }
    else
    {
        database =
            QSqlDatabase::addDatabase(
                "QSQLITE",
                m_connectionName
            );
    }

    database.setDatabaseName(
        databasePath()
    );

    if (!database.open())
    {
        m_lastError =
            database.lastError().text();

        return false;
    }

    QSqlQuery query(database);

    bool created =
        query.exec(
            "CREATE TABLE IF NOT EXISTS simulation_history ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "date_time TEXT NOT NULL,"
            "total_requests INTEGER NOT NULL,"
            "processed_requests INTEGER NOT NULL,"
            "successful_requests INTEGER NOT NULL,"
            "failed_requests INTEGER NOT NULL,"
            "success_rate REAL NOT NULL,"
            "average_latency REAL NOT NULL,"
            "fault_summary TEXT NOT NULL DEFAULT '',"
            "service_health_json TEXT NOT NULL DEFAULT ''"
            ")"
        );

    if (!created)
    {
        m_lastError =
            query.lastError().text();

        return false;
    }

    if (
        !ensureColumn(
            "fault_summary",
            "TEXT NOT NULL DEFAULT ''"
        )
    )
    {
        return false;
    }

    if (
        !ensureColumn(
            "service_health_json",
            "TEXT NOT NULL DEFAULT ''"
        )
    )
    {
        return false;
    }

    m_lastError.clear();

    return true;
}

bool HistoryManager::ensureColumn(
    const QString &columnName,
    const QString &definition
)
{
    if (
        !QSqlDatabase::contains(
            m_connectionName
        )
    )
    {
        m_lastError =
            "History database is not initialized.";

        return false;
    }

    QSqlDatabase database =
        QSqlDatabase::database(
            m_connectionName
        );

    QSqlQuery query(database);

    if (
        !query.exec(
            "PRAGMA table_info(simulation_history)"
        )
    )
    {
        m_lastError =
            query.lastError().text();

        return false;
    }

    while (query.next())
    {
        if (
            query.value(1).toString() ==
            columnName
        )
        {
            return true;
        }
    }

    QSqlQuery alterQuery(database);

    QString sql =
        QString(
            "ALTER TABLE simulation_history "
            "ADD COLUMN %1 %2"
        )
            .arg(
                columnName,
                definition
            );

    if (!alterQuery.exec(sql))
    {
        m_lastError =
            alterQuery.lastError().text();

        return false;
    }

    return true;
}

bool HistoryManager::addSimulation(
    int totalRequests,
    int processedRequests,
    int successfulRequests,
    int failedRequests,
    double successRate,
    double averageLatency,
    const QString &faultSummary,
    const QString &serviceHealthJson
)
{
    if (
        !QSqlDatabase::contains(
            m_connectionName
        )
    )
    {
        if (!initialize())
        {
            return false;
        }
    }

    QSqlDatabase database =
        QSqlDatabase::database(
            m_connectionName
        );

    if (
        !database.isOpen() &&
        !database.open()
    )
    {
        m_lastError =
            database.lastError().text();

        return false;
    }

    QSqlQuery query(database);

    query.prepare(
        "INSERT INTO simulation_history ("
        "date_time,"
        "total_requests,"
        "processed_requests,"
        "successful_requests,"
        "failed_requests,"
        "success_rate,"
        "average_latency,"
        "fault_summary,"
        "service_health_json"
        ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)"
    );

    query.addBindValue(
        QDateTime::currentDateTime()
            .toString(
                "yyyy-MM-dd HH:mm:ss"
            )
    );

    query.addBindValue(
        totalRequests
    );

    query.addBindValue(
        processedRequests
    );

    query.addBindValue(
        successfulRequests
    );

    query.addBindValue(
        failedRequests
    );

    query.addBindValue(
        successRate
    );

    query.addBindValue(
        averageLatency
    );

    query.addBindValue(
        faultSummary
    );

    query.addBindValue(
        serviceHealthJson
    );

    if (!query.exec())
    {
        m_lastError =
            query.lastError().text();

        return false;
    }

    m_lastError.clear();

    return true;
}

QVector<SimulationHistoryRecord>
HistoryManager::history() const
{
    QVector<SimulationHistoryRecord> records;

    if (
        !QSqlDatabase::contains(
            m_connectionName
        )
    )
    {
        m_lastError =
            "History database is not initialized.";

        return records;
    }

    QSqlDatabase database =
        QSqlDatabase::database(
            m_connectionName
        );

    QSqlQuery query(database);

    if (
        !query.exec(
            "SELECT "
            "id,"
            "date_time,"
            "total_requests,"
            "processed_requests,"
            "successful_requests,"
            "failed_requests,"
            "success_rate,"
            "average_latency,"
            "fault_summary,"
            "service_health_json "
            "FROM simulation_history "
            "ORDER BY id DESC"
        )
    )
    {
        m_lastError =
            query.lastError().text();

        return records;
    }

    while (query.next())
    {
        SimulationHistoryRecord record;

        record.id =
            query.value(0).toInt();

        record.dateTime =
            query.value(1).toString();

        record.totalRequests =
            query.value(2).toInt();

        record.processedRequests =
            query.value(3).toInt();

        record.successfulRequests =
            query.value(4).toInt();

        record.failedRequests =
            query.value(5).toInt();

        record.successRate =
            query.value(6).toDouble();

        record.averageLatency =
            query.value(7).toDouble();

        record.faultSummary =
            query.value(8).toString();

        record.serviceHealthJson =
            query.value(9).toString();

        records.append(
            record
        );
    }

    m_lastError.clear();

    return records;
}

bool HistoryManager::clearHistory()
{
    if (
        !QSqlDatabase::contains(
            m_connectionName
        )
    )
    {
        return false;
    }

    QSqlDatabase database =
        QSqlDatabase::database(
            m_connectionName
        );

    QSqlQuery query(database);

    if (
        !query.exec(
            "DELETE FROM simulation_history"
        )
    )
    {
        m_lastError =
            query.lastError().text();

        return false;
    }

    m_lastError.clear();

    return true;
}

QString HistoryManager::lastError() const
{
    return m_lastError;
}