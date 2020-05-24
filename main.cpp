#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <iostream>
#include <QDebug>
#include <QtSql/QSql>
#include <QtSql/QSqlQuery>
#include "login.h"
#include "ui_login.h"


#define q2c(string) string.toStdString()

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login l;


    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("Projet2A");
    db.setUserName("ons");
    db.setPassword("esprit20");

   QSqlQuery q;
    if(db.open())
    {
        std::cout << "Vous êtes maintenant connecté à " << q2c(db.hostName()) << std::endl;
        //db.close();
    }
    else
    {
        std::cout << "La connexion a échouée, désolé" << std::endl;
    //qDebug()<<"erreur:"<<db.lastError().text();

    }
    l.show();

    return a.exec();
}
