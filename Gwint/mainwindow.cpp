#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card_loader.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int test = 42;

    card_loader zaladuj;
    karta::Card karci = zaladuj.zaladuj_karte(test);



    //    ui->label->setText(karci.nazwa);
    //else
    //    ui->label->setText("To nie melee");
    //testowałem czy odczyt kategorii i frakcji działa (działa)

    ui->label->setText(karci.nazwa + " " + QString::number(karci.sila) + " " + karci.flavor_text);

    if (karci.legendarna)
        ui->label->setText(karci.nazwa);
}

MainWindow::~MainWindow()
{
    delete ui;
}
