QT       += core gui sql printsupport network charts multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    absence.cpp \
    connexion.cpp \
    gesabs.cpp \
    gesprofil.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    profil.cpp \
    smtp.cpp \
    stats.cpp

HEADERS += \
    absence.h \
    connexion.h \
    gesabs.h \
    gesprofil.h \
    login.h \
    mainwindow.h \
    profil.h \
    smtp.h \
    stats.h

FORMS += \
    gesabs.ui \
    gesprofil.ui \
    login.ui \
    mainwindow.ui \
    stats.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    ../abc.mp3 \
    image/acceuil.png \
    image/acceuilpr.png \
    image/ajbtn.png \
    image/ajbtnp.png \
    image/ajout.png \
    image/ajoutabs.png \
    image/ajoutlvr.png \
    image/ajoutlvs.png \
    image/annbtn.png \
    image/annbtnp.png \
    image/back.png \
    image/backing.png \
    image/bouton_ajouter-un-profil.png \
    image/bouton_modifier-un-profil.png \
    image/bouton_supprimer-un-profil.png \
    image/btnliv.png \
    image/btnlivpr.png \
    image/btnlivrpr.png \
    image/btnlvr.png \
    image/charts.png \
    image/cherchbtn.png \
    image/cherchbtnpr.png \
    image/exit.png \
    image/exit1.png \
    image/gg.png \
    image/ggabs.png \
    image/modabs.png \
    image/modifbtn.png \
    image/modifbtndia.png \
    image/modifbtnpr.png \
    image/modiflvbtnpr.png \
    image/motabs.png \
    image/motpr.png \
    image/print.png \
    image/reload.png \
    image/rpl.png \
    image/suppabs.png \
    image/suppbtn.png \
    image/suppbtnlvpr.png \
    image/suppbtnpr.png \
    image/title.png \
    image/titlepr.png \
    image/triup.png \
    image/unnamed.png
