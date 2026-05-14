#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card_loader.h"
#include "deck_loader.h"
#include "deck_saver.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int test = 42;

    card_loader zaladuj;
    karta* testowa_karta = new karta;
    zaladuj.zaladuj_karte(test, testowa_karta);


    //    ui->label->setText(karci.nazwa);
    //else
    //    ui->label->setText("To nie melee");
    //testowałem czy odczyt kategorii i frakcji działa (działa)

    ui->label->setText(testowa_karta->getNazwa() + " " + QString::number(testowa_karta->getSila()) + " " + testowa_karta->getFlavor());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{

}