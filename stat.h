#ifndef STAT_H
#define STAT_H
#ifndef STATISTIQUE_H
#define STATISTIQUE_H


#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <string>
#include <QPainter>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

QT_CHARTS_USE_NAMESPACE

class Statistique
{
    QChart *chart;
    QChartView *chartView;
public:
    Statistique();
    QChartView *Preparechart();
};


#endif // STATISTIQUE_H


#endif // STAT_H
