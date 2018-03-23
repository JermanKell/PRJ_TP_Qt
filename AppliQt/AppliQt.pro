#-------------------------------------------------
#
# Project created by QtCreator 2018-02-13T10:46:37
#
#-------------------------------------------------

QT       += core gui
QT       += sql
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AppliQt
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += . \
    Modèle \
    Vue \
    Controleur

SOURCES += \
    main.cpp \
    c_init_bd.cpp \
    #Modèle
    Modele/client.cpp \
    Modele/personnel.cpp \
    Modele/RendezVous.cpp \
    #Vue
    Vue/mainwindow.cpp \
    Vue/connexionwindow.cpp \
    Vue/ajouterclientwindow.cpp \
    Vue/modifierclientwindow.cpp \
    Vue/ajouterpersonnelwindow.cpp \
    Vue/modifierpersonnelwindow.cpp \
    Vue/aproposwindow.cpp \
    #Controleur
    Controleur/dbconnexion.cpp \
    Controleur/dbmanager_identification.cpp \
    Controleur/dbmanager_client.cpp \
    Controleur/dbmanager_personnel.cpp \
    Controleur/Gestion_Client.cpp \
    Controleur/Gestion_Creneau.cpp

HEADERS += \
    c_init_bd.h \
    #Modèle
    Modele/client.h \
    Modele/personnel.h \
    Modele/RendezVous.h \
    #Vue
    Vue/mainwindow.h \
    Vue/connexionwindow.h \
    Vue/ajouterclientwindow.h \
    Vue/modifierclientwindow.h \
    Vue/ajouterpersonnelwindow.h \
    Vue/modifierpersonnelwindow.h \
    Vue/aproposwindow.h \
    #Controleur
    Controleur/dbconnexion.h \
    Controleur/dbmanager_identification.h \
    Controleur/dbmanager_client.h \
    Controleur/dbmanager_personnel.h \
    Controleur/Gestion_Client.h \
    Controleur/Gestion_Creneau.h \
    Controleur/FoncteurTrieRessource.h

FORMS += \
    #Vue
    Vue/mainwindow.ui \
    Vue/connexionwindow.ui \
    Vue/ajouterclientwindow.ui \
    Vue/modifierclientwindow.ui \
    Vue/ajouterpersonnelwindow.ui \
    Vue/modifierpersonnelwindow.ui \
    Vue/aproposwindow.ui
