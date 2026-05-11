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


    kontener_kart Azbest;

    deck_loader Mieszacz_azbestu;

    Mieszacz_azbestu.load_deck(Azbest, "deck1.txt");

    deck_saver Wylewacz_azbestu;

    Wylewacz_azbestu.save_deck(Azbest, "deck2.txt");


    //    ui->label->setText(karci.nazwa);
    //else
    //    ui->label->setText("To nie melee");
    //testowałem czy odczyt kategorii i frakcji działa (działa)

    ui->label->setText(testowa_karta->nazwa + " " + QString::number(testowa_karta->sila) + " " + testowa_karta->flavor_text);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    kontener_kart Azbest;

    deck_loader Mieszacz_azbestu;

    Mieszacz_azbestu.load_deck(Azbest, "deck1.txt");

    ui->label->setText(QString::number(position) + "    " + Azbest.Ciag_kart[position]->nazwa);
}

