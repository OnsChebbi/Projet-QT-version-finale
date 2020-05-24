#include "mainwindow.h"
#include "gesprofil.h"
#include "gesabs.h"
#include "ui_gesabs.h"
#include <QMessageBox>
#include <QRect>
#include <QPrinter>
#include <QtPrintSupport>
#include <QPrintDialog>
#include <QValidator>
#include "ui_gesprofil.h"
#include "smtp.h"
#include<iostream>
#include <QPainter>
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <string>
#include <QMediaPlayer>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include "stats.h"
#include "ui_stats.h"



gesprofil::gesprofil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gesprofil)
{

    ui->setupUi(this);

    ui->tabprofil->setModel(tmpprofil.afficherprofil());
    int i = tmpprofil.nombreProfils();
     QString nombre;
     nombre.setNum(i);
     ui->nbr->setText(nombre);

}
      gesprofil::~gesprofil()
        {
            delete ui;
        }
        void gesprofil::closeWin()
        {
         this->close();
            this->deleteLater();
        }

        void gesprofil::on_acceuilbtn_clicked()
        {
            MainWindow *main;
            main = new MainWindow();
            main->showFullScreen();
            delay = new QTimer(this);
           connect(delay,SIGNAL(timeout()),this,SLOT(closeWin()));
           delay->start(500);

        }

        void gesprofil::on_quitter_clicked()
        {

                   this->close();


        }


        void gesprofil::on_pushButton_5_clicked()
        {   QString id= ui->id->text();
            QString nom= ui->nom->text();
            QString prenom= ui->prenom->text();
            QString role= ui->role->currentText();
            QString adresse= ui->adresse_2->text();
            QString mdp= ui->mdp->text();
            QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

            if(!regex.match(adresse).hasMatch())
            {


                ui->adresse_2->setStyleSheet("QLineEdit { color: red;}");
                QMessageBox::critical(nullptr, QObject::tr("Ajouter un profil"),
                                      QObject::tr("Vérifier votre adresse !.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);}


            else
            {     profil p(id,nom,prenom,role,adresse,mdp);

                bool test=p.ajouterprofil();
                if(test)
                {

                    ui->tabprofil->setModel(tmpprofil.afficherprofil());//refresh
                    QMessageBox::information(nullptr, QObject::tr("Ajouter un profil"),
                                             QObject::tr("Profil ajouté.\n"
                                                         "Click Cancel to exit."), QMessageBox::Cancel);
                    Smtp* smtp = new Smtp("smartpost2a10@gmail.com", "SMARTpost210", "smtp.gmail.com", 465);
                    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                    QString adresse= ui->adresse_2->text();
                    smtp->sendMail("smartpost2a10@gmail.com", adresse , "B",0);

                    QMessageBox::information( 0, tr( "Qt Simple SMTP client" ), tr( "Un mail de bienvenue a été envoyé !\n\n" ) );

                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Ajouter un profil"),
                                          QObject::tr("Erreur !.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }





void gesprofil::on_pushButton_6_clicked()
{
    QString id = ui->id2->text();
    bool test=tmpprofil.supprimerprofil(id);
    if(test)
    {ui->tabprofil->setModel(tmpprofil.afficherprofil());//refresh
        QMessageBox::information(nullptr, QObject::tr("Supprimer un profil"),
                    QObject::tr("Profil supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un profil"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

//modifier ok
void gesprofil::on_pushButton_8_clicked()
{
    QString id = ui->id->text();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
    QString role= ui->role->currentText();
    QString adresse= ui->adresse_2->text();
    QString mdp= ui->mdp->text();
    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    if(!regex.match(adresse).hasMatch())
    {


                ui->adresse_2->setStyleSheet("QLineEdit { color: red;}");
                QMessageBox::critical(nullptr, QObject::tr("Ajouter un profil"),
                                 QObject::tr("Vérifier votre adresse !.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}


else
   {
    profil p ;
  bool test=p.modifierprofil(id,nom,prenom,role,adresse,mdp);

  if(test)

    {
      ui->tabprofil->setModel(tmpprofil.afficherprofil());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un profil"),
                    QObject::tr("Profil modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un profil"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
}
void gesprofil::on_pushButton2_clicked()
{
    this->close();
        gesabs *ok;
            ok = new gesabs();
            ok->showFullScreen();

}

void gesprofil::on_pushButton_7_clicked()
{
    QString id=ui->idr->text();
      ui->tabprofil->setModel(tmpprofil.recherche(id));


}

void gesprofil::on_reload_clicked()
{
    profil p;
    ui->tabprofil->setModel(tmpprofil.afficherprofil());
}

QString gesprofil::get_adresse()
{
    QString adresse= ui->adresse_2->text();
    return adresse;
}



void gesprofil::on_print_clicked()
{   QDateTime date;
    QDateTime datecreation = date.currentDateTime();
        QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;

           QPdfWriter pdf("C:/Users/HP/Desktop/PDFprofils.pdf");
           QPainter painter(&pdf);
          int i = 4000;


               painter.setPen(Qt::blue);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(1100,1200,"Liste Des Profils");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 15));
               painter.drawText(1100,2000,afficheDC);
               painter.drawRect(100,100,7300,2600);
               painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/HP/Desktop/projet/print.png"));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(200,3300,"ID ");
               painter.drawText(1300,3300,"Nom");
               painter.drawText(2100,3300,"Prénom");
               painter.drawText(3200,3300,"Role");
               painter.drawText(4500,3300,"Adresse e-mail");
               painter.drawText(7000,3300,"Mot de passe");

               QSqlQuery query;
               query.prepare("select * from PROFIL ");
               query.exec();
               while (query.next())
               {

                   painter.drawText(200,i,query.value(0).toString());
                   painter.drawText(1300,i,query.value(1).toString());
                   painter.drawText(2100,i,query.value(2).toString());
                   painter.drawText(3200,i,query.value(3).toString());
                   painter.drawText(4500,i,query.value(4).toString());
                    painter.drawText(7000,i,query.value(5).toString());


                  i = i + 400;


               }
               int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);

QDesktopServices service;

                   if (reponse == QMessageBox::Yes)
                   {
                       service.openUrl(QUrl("C:/Users/HP/Desktop/Pdfprofils.pdf"));
                       painter.end();
                   }
                   if (reponse == QMessageBox::No)
                   {
                        painter.end();
                   }}


/*void gesprofil::on_up_clicked()
{
    ui->tabprofil->setModel(tmpprofil.trinom());

}

*/

void gesprofil::on_up_clicked()
{
     ui->tabprofil->setModel(tmpprofil.trinom());
}


void gesprofil::on_pushButton_9_clicked()
{

    QString id = ui->id->text();
    QString nom= ui->nom->text();
    QString prenom= ui->prenom->text();
    QString role= ui->role->currentText();
    QString adresse= ui->adresse_2->text();
    QString mdp= ui->mdp->text();
    QRegularExpression regex("^[0-9a-zA-Z]+([0-9a-zA-Z]*[-._+])*[0-9a-zA-Z]+@[0-9a-zA-Z]+([-.][0-9a-zA-Z]+)*([0-9a-zA-Z]*[.])[a-zA-Z]{2,6}$");

    if(!regex.match(adresse).hasMatch())
    {


                ui->adresse_2->setStyleSheet("QLineEdit { color: red;}");
                QMessageBox::critical(nullptr, QObject::tr("Ajouter un profil"),
                                 QObject::tr("Vérifier votre adresse !.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);}


else
   {
    profil p ;
  bool test=p.modifierprofil(id,nom,prenom,role,adresse,mdp);

  if(test)

    {
      ui->tabprofil->setModel(tmpprofil.afficherprofil());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier un profil"),
                    QObject::tr("Profil modifié.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modifier un profil"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

}

void gesprofil::on_charts_clicked()
{


    stats st;
    st.setModal(true);
    st.exec();




}





QString gesprofil::adresse()
{

    QString adresse =ui->adresse_2->text();

    return adresse;
}




void gesprofil::on_tabprofil_activated(const QModelIndex &index)
{
    QString val = ui->tabprofil->model()->data(index).toString() ;
       QSqlQuery qry;
       qry.prepare(" SELECT * from PROFIL where ID='"+val+"'");
       if (qry.exec())
       {
           while (qry.next()) {
               ui->id->setText(qry.value(0).toString()) ;
               ui->id2->setText(qry.value(0).toString()) ;
               ui->nom->setText(qry.value(1).toString());

                  ui->prenom->setText(qry.value(2).toString()) ;
               ui->role->setCurrentText(qry.value(3).toString()) ;

              ui->adresse_2->setText(qry.value(4).toString()) ;
              ui->mdp->setText(qry.value(5).toString()) ;




              }
              ui->tabprofil->setModel(tmpprofil.afficherprofil());
      }
}
