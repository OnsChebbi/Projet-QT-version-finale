#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gesprofil.h"
#include "gesabs.h"
#include "ui_gesabs.h"
#include "ui_gesprofil.h"
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->close();
        gesprofil *pr;
        pr = new gesprofil();
        pr->showFullScreen();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->close();
        gesabs *ok;
            ok = new gesabs();
            ok->showFullScreen();
}



void MainWindow::on_play_clicked()
{
    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("C:/Users/HP/Desktop/projet/image/ok.mp3"));
    player->play();
}

void MainWindow::on_muted_clicked()
{

    player->pause();
}



void MainWindow::on_pushButton_2_clicked()
{
    this->close();
}


