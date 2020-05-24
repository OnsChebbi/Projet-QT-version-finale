#ifndef ABSENCE_H
#define ABSENCE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class absence
{
public:
absence();
absence(QString,QString,QString,QString);
QString get_idabs();
QString get_dateabs();
QString get_heure();
QString get_justification();
bool ajouterabs();
QSqlQueryModel * afficherabs();
bool supprimerabs(QString id);
bool modifierabs(QString,QString,QString,QString);
bool recherche(QString id);
QSqlQueryModel * rechercheabs(QString id);
QSqlQueryModel * trier_date();
QSqlQueryModel * trier_id();
void makePlot();
QSqlQueryModel * afficherabsnonjust();

bool check(QString idabs);
int nombreABS();
private:
QString idabs;
QString dateabs;
QString heure;
QString justification;
};

#endif // ABSENCE_H
