#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card_loader.h"
#include "deck_loader.h"
#include "deck_saver.h"
#include "card_button.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //testwalem wyrównanie od lewej do prawej przy dodawaniu zamiast tak jak jest bazowo
    // ui->layout_reki->layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    //  ui->layout_reki->layout()->setSpacing(20);
    int test = 42;

    card_loader zaladuj;
    karta* testowa_karta = new karta;
    zaladuj.zaladuj_karte(test, testowa_karta);


    ui->Plansza->setStyleSheet(
        "border-image: url(:/gwont_plansza_templatka.png) 0 0 0 0 stretch stretch;"
    );
    qDebug() << QPixmap(":/plansza.jpg").isNull();
    qDebug() << QPixmap(":/gwont_plansza_templatka.png").isNull();

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


void MainWindow::on_button_dobierz_clicked()
{
    //tworze testwa karte czy się dodają poprawnie
    karta* nowaKartaDane = new karta();
    nowaKartaDane->setName("Bogata kurcze piechota");
    nowaKartaDane->setSilaBaz(100);
    nowaKartaDane->updateSila(false, false, 0); //updatuje sile na 1

    nowaKartaDane->setLeg(false);

    Card_Button *przyciskKarty = new Card_Button(nowaKartaDane, this);
    przyciskKarty->getCardData();
    przyciskKarty->refresh();
    ui->layout_reki->addWidget(przyciskKarty);


    connect(przyciskKarty, &Card_Button::clicked, this, [=]() {
        qDebug() << "Wybrano karte: " << nowaKartaDane->getNazwa();


        //usuwanie karty po kliknieciu, tak jakbyś ja przeniósł na planszę
        ui->layout_reki->removeWidget(przyciskKarty);
        przyciskKarty->hide();
    });
}

