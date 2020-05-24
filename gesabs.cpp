#include "mainwindow.h"
#include "gesabs.h"
#include "ui_gesabs.h"
#include "gesprofil.h"
#include "ui_gesprofil.h"
#include "absence.h"
#include <QMessageBox>
#include <QDate>
#include <QDebug>
#include<iostream>
#include <QTimer>
#include <QDateTime>
#include <QDate>
#include <QPrinter>
#include <QtPrintSupport>
#include <QPrintDialog>
#include <QDesktopServices>
#include "mainwindow.h"




 gesabs::gesabs(QWidget *parent):
     QMainWindow(parent),
    ui(new Ui::gesabs)
{

ui->setupUi(this);

ui->tababs->setModel(tmpabs.afficherabs());
int i = tmpabs.nombreABS();
 QString nombre;
 nombre.setNum(i);
 ui->nbr->setText(nombre);
}
  gesabs::~gesabs()
    {
        delete ui;
    }
    void gesabs::closeWin()
    {
     this->close();
        this->deleteLater();
    }

void gesabs::on_pushButton_5_clicked()
{

    QString idabs = ui->id->text();
    QString dateabs= ui->date->date().toString("dd / MM / yyyy ");
    QString heure= ui->heure->time().toString("hh : mm : ss ");
    QString justification= ui->justification->currentText();
    QSqlQuery query;
    query.prepare("SELECT ID FROM PROFIL WHERE ID=:idabs");
    query.bindValue(":idabs",idabs);
    query.exec();
     if (query.next()){
   ui->id->setStyleSheet("QLineEdit { color: green;}");
   absence a(idabs,dateabs,heure,justification);

  bool test=a.ajouterabs();

  if(test)
{

      ui->tababs->setModel(tmpabs.afficherabs());//refresh
QMessageBox::information(nullptr, QObject::tr("Ajouter une absence"),
                  QObject::tr("Absence ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une absence"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
     else
     {
           ui->id->setStyleSheet("QLineEdit { color: red;}");
           QMessageBox::critical(nullptr, QObject::tr("Id absent"),
                       QObject::tr("Ce profil n'existe pas !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
     }

}

void gesabs::on_quitter_clicked()
{
       this->close();
}

void gesabs::on_pushButton_6_clicked()
{

    QString id = ui->id2->text();
    bool test=tmpabs.supprimerabs(id);
    if(test)
    {ui->tababs->setModel(tmpabs.afficherabs());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer une absence"),
                    QObject::tr("Absence supprimée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une absence"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void gesabs::on_pushButton_8_clicked()
{
    QString idabs = ui->id->text();
    QString dateabs= ui->date->date().toString("dd / MM / yyyy ");
    QString heure= ui->heure->time().toString("hh : mm : ss ");
    QString justification= ui->justification->currentText();
    absence a;
  bool test=a.modifierabs(idabs,dateabs,heure,justification);

  if(test)

    {
      ui->tababs->setModel(tmpabs.afficherabs());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier une absence"),
                    QObject::tr("Absence modifiée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier une absence"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void gesabs::on_pushButton_7_clicked()
{
    QString id=ui->idr->text();
    ui->tababs->setModel(tmpabs.rechercheabs(id));
}

void gesabs::on_pushButton_clicked()
{
    this->close();
    gesprofil *pr;
    pr = new gesprofil();
    pr->showFullScreen();
}




void gesabs::on_print_clicked()
{   QDateTime date;
    QDateTime datecreation = date.currentDateTime();
        QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;

           QPdfWriter pdf("C:/Users/HP/Desktop/PDFabsence.pdf");
           QPainter painter(&pdf);
          int i = 4000;


               painter.setPen(Qt::blue);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(1100,1200,"Liste Des Absences");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 15));
               painter.drawText(1100,2000,afficheDC);
               painter.drawRect(100,100,7300,2600);
               painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/HP/Desktop/projet/print.png"));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(200,3300,"ID absence");
               painter.drawText(1300,3300,"ID absent");
               painter.drawText(2500,3300,"Date");
               painter.drawText(3900,3300,"Heure");
               painter.drawText(5300,3300,"Justification");

               QSqlQuery query;
               query.prepare("select * from ABSENCE ");
               query.exec();
               while (query.next())
               {

                   painter.drawText(200,i,query.value(0).toString());
                   painter.drawText(1300,i,query.value(1).toString());
                   painter.drawText(2500,i,query.value(2).toString());
                   painter.drawText(3900,i,query.value(3).toString());
                   painter.drawText(5300,i,query.value(4).toString());


                  i = i + 400;


               }
               int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);

QDesktopServices service;

                   if (reponse == QMessageBox::Yes)
                   {
                       service.openUrl(QUrl("C:/Users/HP/Desktop/Pdfabsence.pdf"));
                       painter.end();
                   }
                   if (reponse == QMessageBox::No)
                   {
                        painter.end();
                   }}

void gesabs::on_reloadd_clicked()
{

    ui->tababs->setModel(tmpabs.afficherabs());
}






/*
void gesabs::on_pushButton_9_clicked()
{
    this->close();
    statt pr;
        pr.setModal(true);
        pr.exec();
}*/

void gesabs::on_reloadd_2_clicked()
{
        ui->tababs->setModel(tmpabs.trier_id());
}


void gesabs::on_commandLinkButton_clicked()
{
     ui->tababs->setModel(tmpabs.afficherabsnonjust());
}



void gesabs::on_pushButton_2_clicked()
{
    ui->tababs->setModel(tmpabs.afficherabsnonjust());
}

void gesabs::on_acceuilbtn_clicked()
{
    MainWindow *main;
    main = new MainWindow();
    main->showFullScreen();
    delay = new QTimer(this);
   connect(delay,SIGNAL(timeout()),this,SLOT(closeWin()));
   delay->start(500);
}

void gesabs::on_tababs_activated(const QModelIndex &index)
{
    QString val = ui->tababs->model()->data(index).toString() ;
       QSqlQuery qry;
       qry.prepare(" SELECT * from ABSENCE where ID='"+val+"'");
       if (qry.exec())
       {
           while (qry.next()) {
               ui->id2->setText(qry.value(0).toString()) ;
               ui->id->setText(qry.value(1).toString());

                  ui->date->setDate(qry.value(2).toDate()) ;
               ui->heure->setTime(qry.value(3).toTime()) ;
               ui->justification->setCurrentText(qry.value(4).toString()) ;




              }
              ui->tababs->setModel(tmpabs.afficherabs());
      }
}
