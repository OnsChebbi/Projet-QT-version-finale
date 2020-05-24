#ifndef GESPROFIL_H
#define GESPROFIL_H
#include <QMainWindow>
#include <QDialog>
#include <QMediaPlayer>
#include <QTimer>
#include "profil.h"

namespace Ui {
class gesprofil;
}

class gesprofil : public QMainWindow
{
    Q_OBJECT

public:
    explicit gesprofil(QWidget *parent = nullptr);
    ~gesprofil();
    QString adresse();
public slots:
    void save();
    QString get_adresse();
    void adjustTextColor();

private slots:
    void on_gespr_clicked();
    void closeWin();
     void on_quitter_clicked();
     void on_acceuilbtn_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_role_activated(const QString &arg1);

    void on_okk_clicked();

    void on_pushButton2_clicked();

    void on_pushButton_7_clicked();

    void on_reload_clicked();

    void on_print_clicked();

    void on_reload_2_clicked();

    void on_up_clicked();

    void on_total_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_9_clicked();

    void on_pushButton_2_clicked();

    void on_charts_clicked();

    //void mouseMoveEvent(QMouseEvent *event);
    void on_tabprofil_activated(const QModelIndex &index);

private:
    QTimer *delay;
    Ui::gesprofil *ui;
    profil tmpprofil;
     QMediaPlayer *player;
};

#endif // GESPROFIL_H
