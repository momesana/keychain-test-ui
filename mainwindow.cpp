#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "./keychainclass.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_keychain(new KeyChainClass(this))
{
    ui->setupUi(this);

    connect(m_keychain, &KeyChainClass::keyStored, this, [=](const QString key) {
       ui->resultLabel->setText(QString("<p align='center' style='font-weight: bold;'>stored key '%1'</p>").arg(key));
    });
    connect(m_keychain, &KeyChainClass::keyRestored, this, [=](const QString key, const QString value) {
        ui->resultLabel->setText(QString("<p align='center' style='font-weight: bold; color: green'>Retrieved value is '%1'</p>").arg(value));
    });
    connect(m_keychain, &KeyChainClass::keyDeleted, this, [=](const QString key) {
        ui->resultLabel->setText(QString("<p align='center' style='font-weight: bold; color: orange'>Deleted key '%1'</p>").arg(key));
    });
    connect(m_keychain, &KeyChainClass::error, this, [=](const QString &error) {
        ui->resultLabel->setText(QString("<p align='center' style='font-weight: bold; color: red'>%1</p>").arg(error));
    });



    connect(ui->applyButton, &QPushButton::clicked, this, [=](){
        ui->resultLabel->clear();

        const QString service = ui->serviceLineEdit->text();
        const QString key = ui->keyLineEdit->text();

        switch(ui->actionComboBox->currentIndex()) {
        case 0: // READ
            m_keychain->readKey(key, service);
            break;
        case 1: // WRITE
            m_keychain->writeKey(key, ui->valueLineEdit->text(), service);
            break;
        case 2: // DELETE
            m_keychain->deleteKey(key,  service);
            break;
        }
    });

    connect(ui->serviceLineEdit, &QLineEdit::textChanged, ui->resultLabel, &QLabel::clear);
    connect(ui->keyLineEdit, &QLineEdit::textChanged, ui->resultLabel, &QLabel::clear);
    connect(ui->valueLineEdit, &QLineEdit::textChanged, ui->resultLabel, &QLabel::clear);

    connect(ui->actionComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::updateForm);
    updateForm();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateForm()
{
    const bool showValueFields = ui->actionComboBox->currentIndex() == 1;
    ui->valueLabel->setVisible(showValueFields);
    ui->valueLineEdit->setVisible(showValueFields);
    ui->resultLabel->clear();
}
