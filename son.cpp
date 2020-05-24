#include "son.h"

void  mettreMusique()
{
    QMediaPlayer * music_bouton=new QMediaPlayer();
    music_bouton->setMedia(QUrl("qrc:C:/Users/HP/Desktop/music.mp3"));
    music_bouton->play();
}
