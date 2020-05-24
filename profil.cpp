#include "profil.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include "connexion.h"
#include "ui_gesprofil.h"


profil::profil()
{
    nom="";
    prenom="";
    role="";
    adresse="";
    mdp="";
}

profil::profil(QString id,QString nom,QString prenom,QString role,QString adresse,QString mdp)
{
this->id=id;
this->nom=nom;
this->prenom=prenom;
this->role=role;
this->adresse=adresse;
this->mdp=mdp;
}
QString profil::get_id(){return id;}
QString profil::get_nom(){return nom;}
QString profil::get_prenom(){return prenom;}
QString profil::get_role(){return role;}
QString profil::get_adresse(){return adresse;}
QString profil::get_mdp(){return mdp;}

bool profil::ajouterprofil()
{
    QSqlQuery query;

    query.prepare("INSERT into PROFIL(nom,prenom,role,adresse,mdp) VALUES (:nom,:prenom,:role,:adresse,:mdp)");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":role", role);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mdp", mdp);


    return    query.exec();
}

QSqlQueryModel * profil::afficherprofil()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from PROFIL");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("role"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse e-mail"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("mot de passe"));

    return model;
}

bool profil::supprimerprofil(QString id)
{
QSqlQuery query;

query.prepare("Delete from PROFIL where ID = :id ");
query.bindValue(":id", id);
return    query.exec();
}

bool profil::modifierprofil(QString id,QString nom,QString prenom,QString role,QString adresse,QString mdp)
{
    QSqlQuery query;
    query.prepare("UPDATE PROFIL set NOM=:nom, PRENOM=:prenom, ROLE=:role, ADRESSE=:adresse, MDP=:mdp  WHERE ID=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":role", role);
    query.bindValue(":adresse", adresse);
    query.bindValue(":mdp", mdp);
    return    query.exec();
}

QSqlQueryModel *profil::recherche(QString id)
{

    QSqlQueryModel *model=new QSqlQueryModel;
    QSqlQuery query;
    query.prepare("select * from PROFIL where ID = :id");
    query.bindValue(":id",id);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("role"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse e-mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mot de passe"));
    return model;


}

QSqlQueryModel *profil::trinom()
{

    QSqlQueryModel *model=new QSqlQueryModel;

     model->setQuery("Select * from PROFIL Order by NOM ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("role"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse e-mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("mot de passe"));
    return model;


}

int profil::nombreProfils()
{
    QSqlQuery query;
    query.prepare("select count(*) from PROFIL");
    query.exec();
    query.next();

       return query.value(0).toInt();


}
