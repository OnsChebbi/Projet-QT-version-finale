#ifndef GESABS_H
#define GESABS_H
#include <QMainWindow>
#include <QTimer>
#include "absence.h"


namespace Ui {
class gesabs;
}

class gesabs : public QMainWindow
{
    Q_OBJECT

public:
    explicit gesabs(QWidget *parent = nullptr);
    ~gesabs();

private slots:
    void closeWin();
     void on_quitter_clicked();


     void on_pushButton_5_clicked();

     void on_pushButton_6_clicked();

     void on_pushButton_8_clicked();

     void on_pushButton_clicked();

     void on_pushButton_7_clicked();

     void on_reload_clicked();

     void on_print_clicked();

     void on_reloadd_clicked();

     void on_pushButton_3_clicked();

     void on_choix_tri_currentTextChanged(const QString &arg1);

     void on_pushButton_4_clicked();

     void on_pushButton_2_clicked();

     void makePlot();
     void on_pushButton_9_clicked();

     void on_reloadd_2_clicked();

     void on_commandLinkButton_clicked();

     void on_acceuilbtn_clicked();

     void on_tababs_activated(const QModelIndex &index);

private:
    QTimer *delay;
    Ui::gesabs *ui;
    absence tmpabs;
};
#endif // GESABS_H
