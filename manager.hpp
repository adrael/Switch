#ifndef MANAGER_HPP
#define MANAGER_HPP

/** --------------------------------------------------------------------------------------------------------------- **/

#include <qlayout.h>
#include <qdialog.h>
#include <qsqlquery.h>
#include <qsqlerror.h>
#include <qmessagebox.h>
#include <qsqldatabase.h>

#include <qdebug.h>

/** --------------------------------------------------------------------------------------------------------------- **/

#include "crypto.hpp"
#include "lineedit.hpp"

/** --------------------------------------------------------------------------------------------------------------- **/

class Manager : public QWidget {

public:
    static void store(const QString & account, const QString & login, const QString & password) {
        QSqlDatabase tmp = QSqlDatabase::database(databaseLocation + "/Switch.db");
        QSqlQuery query(tmp);
//        QString cryptLog(Crypto::blowfish(Crypto::base64(login.toStdString()), managerKey.toStdString().c_str()).c_str());
//        QString cryptPwd(Crypto::blowfish(Crypto::base64(password.toStdString()), managerKey.toStdString().c_str()).c_str());
        QString prepQuery("INSERT INTO %1 (Username, Password) VALUES (%2, %3)");
        query.prepare(prepQuery.arg(account, "'" + login + "'", "'" + password + "'"));
        if(!query.exec())
            QMessageBox::critical(0, tr("Database error"), tr("Error") +":\n" + tmp.lastError().text(), QMessageBox::Ok);
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static void setKey(const QString & key) {
        managerKey = key;
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static void setLocation(const QString & location) {
        databaseLocation = location;
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static const QString & retrieve(const QString & account) {}

    /** --------------------------------------------------------------------------------------------------------------- **/

    static const QString & getHash(const QString & phrase) {
        return Crypto::hashMe(phrase);
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static const QString & getKey() {
        return managerKey;
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static const QString & getLocation() {
        return databaseLocation;
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static void openDatabase() {
        QSqlDatabase tmp = QSqlDatabase::addDatabase("QSQLITE", databaseLocation + "/Switch.db");
        tmp.setDatabaseName(databaseLocation + "/Switch.db");
        if(!tmp.open())
            QMessageBox::critical(0, tr("Cannot open database"), tr("Error") +":\n" + tmp.lastError().text(), QMessageBox::Ok);
        else {
            if(tmp.tables().size() < 5) {
                QSqlQuery query(tmp);
                query.prepare("CREATE TABLE IF NOT EXISTS GTalk (Username VARCHAR(255), Password VARCHAR(255))");
                if(!query.exec())
                    QMessageBox::critical(0, tr("Database error"), tr("Error") +":\n" + tmp.lastError().text(), QMessageBox::Ok);

                query.prepare("CREATE TABLE IF NOT EXISTS Facebook (Username VARCHAR(255), Password VARCHAR(255))");
                if(!query.exec())
                    QMessageBox::critical(0, tr("Database error"), tr("Error") +":\n" + tmp.lastError().text(), QMessageBox::Ok);

                query.prepare("CREATE TABLE IF NOT EXISTS Twitter (Username VARCHAR(255), Password VARCHAR(255))");
                if(!query.exec())
                    QMessageBox::critical(0, tr("Database error"), tr("Error") +":\n" + tmp.lastError().text(), QMessageBox::Ok);

                query.prepare("CREATE TABLE IF NOT EXISTS Skype (Username VARCHAR(255), Password VARCHAR(255))");
                if(!query.exec())
                    QMessageBox::critical(0, tr("Database error"), tr("Error") +":\n" + tmp.lastError().text(), QMessageBox::Ok);

                query.prepare("CREATE TABLE IF NOT EXISTS WLM (Username VARCHAR(255), Password VARCHAR(255))");
                if(!query.exec())
                    QMessageBox::critical(0, tr("Database error"), tr("Error") +":\n" + tmp.lastError().text(), QMessageBox::Ok);
            }
        }
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static void closeDatabase() {
        {
            QSqlDatabase tmp = QSqlDatabase::database(databaseLocation + "/Switch.db");
            if(tmp.isOpen())
                tmp.close();
        }
        QSqlDatabase::removeDatabase(databaseLocation + "/Switch.db");
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static QSqlDatabase getDatabase() {
        return QSqlDatabase::database(databaseLocation + "/Switch.db");
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

private:
    static QString managerKey;
    static QString databaseLocation;
};

/** --------------------------------------------------------------------------------------------------------------- **/

#endif // MANAGER_HPP
