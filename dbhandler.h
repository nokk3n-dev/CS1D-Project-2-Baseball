#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QString>
#include <QSqlDatabase>
#include <QMessageBox>
#include "dbConstance.h"

class DbHandler
{
public:
    DbHandler();
    DbHandler(QString dbPath, QString dbConnectionName);
    bool open();
    void close();

private:
    QSqlDatabase mydb;
    QMessageBox msgBox;
};

#endif // DBHANDLER_H
