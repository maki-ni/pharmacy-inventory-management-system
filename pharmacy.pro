QT += core gui widgets

TARGET = pharmacy
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    modules/DrugBST.cpp \
    modules/PatientQueue.cpp \
    modules/DateUtils.cpp

HEADERS += mainwindow.h \
    modules/DrugBST.h \
    modules/PatientQueue.h \
    modules/DateUtils.h