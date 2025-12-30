#include "mainwindow.h"
#include <QApplication>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QList>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Pharmacy Inventory Management System");
    setMinimumSize(600, 500);

    // Central widget
    QWidget *centralWidget = new QWidget;
    centralWidget->setStyleSheet("background-color: #F0F8FF;");
    setCentralWidget(centralWidget);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Title
    QLabel *titleLabel = new QLabel("Pharmacy Inventory Management System");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2E8B57; margin: 10px;");
    mainLayout->addWidget(titleLabel);

    // Drugs section
    QGroupBox *drugsGroup = new QGroupBox("Drug Management");
    drugsGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #4682B4; border-radius: 5px; margin-top: 1ex; } "
                              "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    QVBoxLayout *drugsLayout = new QVBoxLayout(drugsGroup);

    QPushButton *addDrugBtn = new QPushButton("➕ Add Drug");
    QPushButton *findDrugNameBtn = new QPushButton("🔍 Find Drug by Name");
    QPushButton *findDrugIdBtn = new QPushButton("🔍 Find Drug by ID");
    QPushButton *displayDrugsBtn = new QPushButton("📋 Display All Drugs");
    QPushButton *exportDrugsBtn = new QPushButton("💾 Export Drugs");
    QPushButton *discardExpiredBtn = new QPushButton("🗑️ Discard Expired Drugs");
    QPushButton *clearDrugsBtn = new QPushButton("🧹 Clear Drug Tree");
    QPushButton *updateDrugQtyBtn = new QPushButton("📦 Update Drug Quantity");

    QList<QPushButton*> drugButtons = {addDrugBtn, findDrugNameBtn, findDrugIdBtn, displayDrugsBtn, exportDrugsBtn, discardExpiredBtn, clearDrugsBtn, updateDrugQtyBtn};
    for (auto btn : drugButtons) {
        btn->setStyleSheet("QPushButton { background-color: #87CEEB; color: white; border: none; padding: 10px; border-radius: 5px; font-size: 12px; } "
                           "QPushButton:hover { background-color: #4682B4; } "
                           "QPushButton:pressed { background-color: #2E8B57; }");
        drugsLayout->addWidget(btn);
    }

    connect(addDrugBtn, &QPushButton::clicked, this, &MainWindow::addDrug);
    connect(findDrugNameBtn, &QPushButton::clicked, this, &MainWindow::findDrugName);
    connect(findDrugIdBtn, &QPushButton::clicked, this, &MainWindow::findDrugId);
    connect(displayDrugsBtn, &QPushButton::clicked, this, &MainWindow::displayDrugs);
    connect(exportDrugsBtn, &QPushButton::clicked, this, &MainWindow::exportDrugs);
    connect(discardExpiredBtn, &QPushButton::clicked, this, &MainWindow::discardExpired);
    connect(clearDrugsBtn, &QPushButton::clicked, this, &MainWindow::clearDrugs);
    connect(updateDrugQtyBtn, &QPushButton::clicked, this, &MainWindow::updateDrugQuantity);

    mainLayout->addWidget(drugsGroup);

    // Patients section
    QGroupBox *patientsGroup = new QGroupBox("Patient Management");
    patientsGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 2px solid #FF6347; border-radius: 5px; margin-top: 1ex; } "
                                 "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }");
    QVBoxLayout *patientsLayout = new QVBoxLayout(patientsGroup);

    QPushButton *addPatientBtn = new QPushButton("➕ Add Patient");
    QPushButton *dequeuePatientBtn = new QPushButton("🚶 Dequeue Patient");
    QPushButton *displayPatientsBtn = new QPushButton("📋 Display Patients");
    QPushButton *exportPatientsBtn = new QPushButton("💾 Export Patients");

    QList<QPushButton*> patientButtons = {addPatientBtn, dequeuePatientBtn, displayPatientsBtn, exportPatientsBtn};
    for (auto btn : patientButtons) {
        btn->setStyleSheet("QPushButton { background-color: #FFA07A; color: white; border: none; padding: 10px; border-radius: 5px; font-size: 12px; } "
                           "QPushButton:hover { background-color: #FF6347; } "
                           "QPushButton:pressed { background-color: #DC143C; }");
        patientsLayout->addWidget(btn);
    }

    connect(addPatientBtn, &QPushButton::clicked, this, &MainWindow::addPatient);
    connect(dequeuePatientBtn, &QPushButton::clicked, this, &MainWindow::dequeuePatient);
    connect(displayPatientsBtn, &QPushButton::clicked, this, &MainWindow::displayPatients);
    connect(exportPatientsBtn, &QPushButton::clicked, this, &MainWindow::exportPatients);

    mainLayout->addWidget(patientsGroup);

    // Status bar
    statusBar()->showMessage("Ready");
}

void MainWindow::addDrug() {
    QString name = QInputDialog::getText(this, "Add Drug", "Enter drug name:");
    if (name.isEmpty()) return;
    int id = QInputDialog::getInt(this, "Add Drug", "Enter ID:");
    int qty = QInputDialog::getInt(this, "Add Drug", "Enter quantity:");
    QString expiry = QInputDialog::getText(this, "Add Drug", "Enter expiry date (YYYY-MM-DD):");
    if (expiry.isEmpty()) return;

    if (dr.idExists(id)) {
        QMessageBox::warning(this, "Error", "Drug with this ID already exists.");
        return;
    }

    dr.addDrug(name.toStdString(), id, qty, expiry.toStdString());
    QMessageBox::information(this, "Success", "Drug added successfully.");
}

void MainWindow::findDrugName() {
    QString name = QInputDialog::getText(this, "Find Drug", "Enter drug name:");
    if (name.isEmpty()) return;
    QString info = QString::fromStdString(dr.getDrugDetailsByName(name.toStdString()));
    QMessageBox::information(this, "Drug Info", info);
}

void MainWindow::findDrugId() {
    int id = QInputDialog::getInt(this, "Find Drug", "Enter drug ID:");
    QString info = QString::fromStdString(dr.getDrugDetailsById(id));
    QMessageBox::information(this, "Drug Info", info);
}

void MainWindow::displayDrugs() {
    QString text = QString::fromStdString(dr.getAllDrugs());
    showTextDialog("All Drugs", text);
}

void MainWindow::exportDrugs() {
    QString filename = QInputDialog::getText(this, "Export Drugs", "Enter filename:");
    if (filename.isEmpty()) return;
    dr.exportToFile(filename.toStdString());
    QMessageBox::information(this, "Success", "Drugs exported successfully.");
}

void MainWindow::discardExpired() {
    dr.discardExpiredFromCSV("drugs.csv");
    QMessageBox::information(this, "Success", "Expired drugs discarded.");
}

void MainWindow::clearDrugs() {
    dr.clearTree();
    QMessageBox::information(this, "Success", "Drug tree cleared.");
}

void MainWindow::updateDrugQuantity() {
    QString name = QInputDialog::getText(this, "Update Drug Quantity", "Enter drug name:");
    if (name.isEmpty()) return;
    if (!dr.nameExists(name.toStdString())) {
        QMessageBox::warning(this, "Error", "Drug not found.");
        return;
    }
    int newQty = QInputDialog::getInt(this, "Update Drug Quantity", "Enter new quantity:");
    QString newExpiry = QInputDialog::getText(this, "Update Drug Quantity", "Enter new expiry date (YYYY-MM-DD):");
    if (newExpiry.isEmpty()) return;
    dr.updateQuantity(name.toStdString(), newQty, newExpiry.toStdString());
    QMessageBox::information(this, "Success", "Drug quantity and expiry updated successfully.");
}

void MainWindow::addPatient() {
    QString name = QInputDialog::getText(this, "Add Patient", "Enter patient name:");
    if (name.isEmpty()) return;
    int id = QInputDialog::getInt(this, "Add Patient", "Enter ID:");
    if (pq.enqueue(id, name.toStdString())) {
        QMessageBox::information(this, "Success", "Patient added successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Patient with this ID already exists.");
    }
}

void MainWindow::dequeuePatient() {
    QString msg = QString::fromStdString(pq.dequeueMessage());
    QMessageBox::information(this, "Dequeue", msg);
}

void MainWindow::displayPatients() {
    QString text = QString::fromStdString(pq.getAllPatients());
    showTextDialog("All Patients", text);
}

void MainWindow::exportPatients() {
    QString filename = QInputDialog::getText(this, "Export Patients", "Enter filename:");
    if (filename.isEmpty()) return;
    pq.exportToFile(filename.toStdString());
    QMessageBox::information(this, "Success", "Patients exported successfully.");
}

void MainWindow::showTextDialog(const QString &title, const QString &text) {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle(title);
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setPlainText(text);
    textEdit->setReadOnly(true);
    layout->addWidget(textEdit);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);
    connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
    layout->addWidget(buttonBox);
    dialog->exec();
}