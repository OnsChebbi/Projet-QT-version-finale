#include "absence.h"
#include <QDebug>
#include <QString>
#include "profil.h"
#include<QSqlError>
#include <QMessageBox>


absence::absence()
{
    idabs="";
    dateabs="";
    heure="";
    justification="";

}
absence::absence(QString idabs,QString dateabs,QString heure,QString justification)
{
this->idabs=idabs;
this->dateabs=dateabs;
this->heure=heure;
this->justification=justification;

}
QString absence::get_idabs(){return idabs;}
QString absence::get_dateabs(){return dateabs;}
QString absence::get_heure(){return heure;}
QString absence::get_justification(){return justification;}

bool absence::ajouterabs()
{
    QSqlQuery query;

    query.prepare("INSERT into ABSENCE(IDABS,DATEABS,HEURE,JUSTIFICATION) VALUES (:idabs,:dateabs,:heure,:justification)");
    query.bindValue(":idabs", idabs);
    query.bindValue(":dateabs", dateabs);
    query.bindValue(":heure", heure);
    query.bindValue(":justification", justification);



    return    query.exec();
}

QSqlQueryModel * absence::afficherabs()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from ABSENCE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID de l'absence"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID de l'absent "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Justification"));


    return model;
}

QSqlQueryModel * absence::afficherabsnonjust()
{
    QSqlQueryModel * model= new QSqlQueryModel();


model->setQuery("select * from ABSENCE WHERE JUSTIFICATION='NonJustifiee'");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID de l'absence"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID de l'absent "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Justification"));


    return model;
}
bool absence::supprimerabs(QString id)
{
QSqlQuery query;

query.prepare("Delete from ABSENCE where ID = :id ");
query.bindValue(":id", id);
return    query.exec();
}

bool absence::modifierabs(QString idabs,QString dateabs,QString heure,QString justification)
{
    QSqlQuery query;
    query.prepare("UPDATE ABSENCE set DATEABS = :dateabs, HEURE = :heure, JUSTIFICATION = :justification  WHERE IDABS = :idabs");

    query.bindValue(":idabs",idabs);
    query.bindValue(":dateabs", dateabs);
    query.bindValue(":heure", heure);
    query.bindValue(":justification", justification);

    return    query.exec();
}

QSqlQueryModel *absence::rechercheabs(QString id)
{

    QSqlQueryModel *model=new QSqlQueryModel;
    QSqlQuery query;
    query.prepare("select * from ABSENCE where IDABS=:idabs");
    query.bindValue(":idabs",id);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID de l'absence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID de l'absent "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Justification"));
    query.exec();
    model->setQuery(query);

    return model;


}
QSqlQueryModel * absence::trier_date()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select * from ABSENCE Order by DATEABS DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID de l'absence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID de l'absent "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Justification"));
    return model;

}
QSqlQueryModel * absence::trier_id()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("Select * from ABSENCE Order by IDABS ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID de l'absence"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID de l'absent "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Heure"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Justification"));
    return model;

}

bool absence::check(QString idabs)
{    bool test1=0;
    QSqlQuery query;
    query.prepare("SELECT EXISTS(SELECT ID FROM PROFIL WHERE ID=:idabs LIMIT 1);");
    query.bindValue(":idabs",idabs);
    if (!query.exec()){
        test1=1;
    }
    else
    {
        if( query.next( ) )
            QMessageBox::information( NULL , "Test" , query.value( 0 ).toString( ) );
    }

return test1;
}


int absence::nombreABS()
{
    QSqlQuery query;
    query.prepare("select count(*) from ABSENCE");
    query.exec();
    query.next();

       return query.value(0).toInt();


}
