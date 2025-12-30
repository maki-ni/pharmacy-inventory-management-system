#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include "modules/DrugBST.h"
#include "modules/PatientQueue.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    DrugBST dr;
    PatientQueue pq;

private slots:
    void addDrug();
    void findDrugName();
    void findDrugId();
    void displayDrugs();
    void exportDrugs();
    void discardExpired();
    void clearDrugs();
    void updateDrugQuantity();
    void addPatient();
    void dequeuePatient();
    void displayPatients();
    void exportPatients();

private:
    void showTextDialog(const QString &title, const QString &text);
};

#endif // MAINWINDOW_H