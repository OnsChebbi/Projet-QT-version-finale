#include "login.h"
#include "ui_login.h"
#include <QProgressBar>
#include <QStatusBar>
#include <QSqlQuery>
#include <QDebug>
#include<iostream>
#include <QTimer>
#include "mainwindow.h"
#include "connexion.h"
#include "ui_mainwindow.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_valider_clicked()
{

     QString adresse= ui->adresse->text();
     QString mdp= ui->mdp->text();


    QSqlQuery query;
    QString select = "SELECT * FROM PROFIL WHERE ADRESSE=:adresse AND MDP=:mdp";

    query.prepare(select);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mdp", mdp);


    query.exec();
    if (query.exec())
    {
        if (query.next())
     {
            QMessageBox::information(nullptr, QObject::tr("Bienvenue"),
                                  QObject::tr("Vous etes connectés à notre application..\n"
                                              "Bienvenue"), QMessageBox::Cancel);
            this->close();
            MainWindow *main;
            main = new MainWindow();
            main->showFullScreen();
            delay = new QTimer(this);
           connect(delay,SIGNAL(timeout()),this,SLOT(closeWin()));
           delay->start(500);

            }
            else
            {  QMessageBox::critical(nullptr, QObject::tr("Ajouter un profil"),
                                     QObject::tr("Invalid username or password..\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

            }
        }



    }




