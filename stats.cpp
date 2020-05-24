#include "stats.h"
#include "ui_stats.h"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <string>
#include <QPainter>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QSqlQuery>
#include "profil.h"
QT_CHARTS_USE_NAMESPACE
stats::stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stats)
{
    ui->setupUi(this);
    QSqlQuery query;

       int count1=0;
       int count2=0;
       int count3=0;
       int count4=0;
       int count5=0;

       if(query.exec("select role from PROFIL"))
       {
       while(query.next())
         {
            if(query.value(0).toString()=="Administrateur"){
                count1++; }
            else if(query.value(0).toString()=="Agent de guichet"){
                count2++;}
            else if(query.value(0).toString()=="Agent de livraison"){
                count3++;}
            else if(query.value(0).toString()=="Agent de facture"){
                count4++;}
            else if(query.value(0).toString()=="Agent financier"){
                count5++;}

          }
        }
       QPieSeries *series;
       series = new QPieSeries();


       series->append("Administrateur", count1);
       series->append("Agent de guichet", count2);
       series->append("Agent de livraison", count3);
       series->append("Agent de facture", count4);
       series->append("Agent financier", count5);


       QPieSlice *slice = series->slices().at(0);
       slice->setExploded();
       slice->setLabelVisible();
       slice->setPen(QPen(Qt::darkGreen, 5));
       slice->setBrush(Qt::green);

       QChart *chart = new QChart();
       chart->addSeries(series);
       chart->setTitle("Statistique des profils selon leurs roles.");


        QChartView *chartview = new QChartView(chart);
        chartview->resize(811,491);
        chartview->setParent(ui->frame);
}

stats::~stats()
{
    delete ui;
}
