#ifndef PROFIL_H
#define PROFIL_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class profil
{
    public:
    profil();
    profil(QString,QString,QString,QString,QString,QString);
    QString get_id();
    QString get_nom();
    QString get_prenom();
    QString get_role();
    QString get_adresse();
    QString get_mdp();
    bool ajouterprofil();
    void adjustTextColor();
    QSqlQueryModel * afficherprofil();
    bool supprimerprofil(QString id);
    bool modifierprofil(QString,QString,QString,QString,QString,QString);
    QSqlQueryModel * recherche(QString id);
    QSqlQueryModel *trinom();
    QSqlQueryModel * total();
    QString id,nom,prenom,role,adresse,mdp;
    int nombreProfils();
};


#endif // PROFIL_H
