#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card_loader.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int test = 30;

    card_loader zaladuj;
    karta::Card karci = zaladuj.zaladuj_karte(test);

    ui->label->setText(karci.nazwa);
}

MainWindow::~MainWindow()
{
    delete ui;
}
