#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card_loader.h"
#include "deck_loader.h"
#include "deck_saver.h"
#include "card_button.h"
#include "gra.h"
#include "i_constant_valuse.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    //blokuje na sztywno rozmiar, karty nie rozwalauja ui ale nie da się zwiększyć ekranu
    //this->setMinimumSize(this->size());
    //this->setMaximumSize(this->size());

    Gra = new gra();
    //testwalem wyrównanie od lewej do prawej przy dodawaniu zamiast tak jak jest bazowo
    // ui->layout_reki->layout()->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    //  ui->layout_reki->layout()->setSpacing(20);
    // QPixmap bg(":/plansza.jpg");

    //do dodania odległości miedzy layooutami aby były na stałe plus skalowanie całej planszy łącznie z kartami
    //ui->layout_plansza_test->addSpacing(150);

    this->setStyleSheet(
        "#centralwidget {"
        "background-color: #686965;"
        "}"
        );

    int test = 42;

    card_loader zaladuj;
    karta* testowa_karta = new karta;
    zaladuj.zaladuj_karte(test, testowa_karta);


    qDebug() << QPixmap(":/plansza.jpg").isNull();


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
    //tak sobie dodałem wczytywanie kart losowych
    karta* nowaKartaDane = new karta();
    //nowaKartaDane->setName("Bogata kurcze piechota");
    //nowaKartaDane->setSilaBaz(100);
    card_loader karta;
    karta.zaladuj_karte((rand()%50 + 1),nowaKartaDane);
    nowaKartaDane->updateSila(false, false, 0); //updatuje sile na 100

    nowaKartaDane->setLeg(false);

    Card_Button *przyciskKarty = new Card_Button(nowaKartaDane, ui->layout_reki->parentWidget());
    przyciskKarty->getCardData();
    przyciskKarty->refresh();
    ui->layout_reki->addWidget(przyciskKarty);


    connect(przyciskKarty, &Card_Button::clicked, this, [=]() {

        qDebug() << "Wybrano karte: " << nowaKartaDane->getNazwa();
        ui->layout_reki->removeWidget(przyciskKarty);
        przyciskKarty->hide();
        przyciskKarty->deleteLater();

        Gra->zagranoKarte(nowaKartaDane,kartyNaPlanszy,ui->player1_melee,this);
    });
}


void MainWindow::on_wyczysc_button_clicked()
{
    Gra->gameClear(kartyNaPlanszy, ui->player1_melee);
}



//funkcja pozwala na przejście z menu do planszy po kliknięciu start
void MainWindow::on_Start_Button_clicked()
{
    //this->showMaximized();
    ui->stackedWidget->setCurrentIndex(1);
    this->setStyleSheet(
        "#centralwidget {"
        "border-image: url(:/plansza.jpg) 0 0 0 0 stretch stretch;"
        "}"
        );

    QSize Size = this->size();
    ui->kol0_szer->changeSize(kol0 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol1_szer->changeSize(kol1 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol2_szer->changeSize(kol2 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol3_szer->changeSize(kol3 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol4_szer->changeSize(kol4 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol5_szer->changeSize(kol5 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol6_szer->changeSize(kol6 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol7_szer->changeSize(kol7 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol8_szer->changeSize(kol8 * Size.rwidth() , 0 , QSizePolicy::Preferred);

    ui->wier1_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Fixed);
    ui->wier2_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Fixed);
    ui->wier3_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Fixed);
    ui->wier4_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Fixed);
    ui->wier5_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Fixed);
    ui->wier6_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Fixed);
    ui->wier7_wys->changeSize(0 , wier7 * Size.rheight() , QSizePolicy::Fixed);
    ui->wier8_wys->changeSize(0 , wier8 * Size.rheight() , QSizePolicy::Fixed);
}

/*
void MainWindow::resizeEvent(QResizeEvent *a){

    QSize Size = this->size();
    ui->kol0_szer->changeSize(kol0 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol1_szer->changeSize(kol1 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol2_szer->changeSize(kol2 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol3_szer->changeSize(kol3 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol4_szer->changeSize(kol4 * Size.rwidth() , 0 , QSizePolicy::Preferred);
//    ui->kol5_szer->changeSize(kol5 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol6_szer->changeSize(kol6 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol7_szer->changeSize(kol7 * Size.rwidth() , 0 , QSizePolicy::Preferred);
    ui->kol8_szer->changeSize(kol8 * Size.rwidth() , 0 , QSizePolicy::Preferred);

    ui->wier1_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Preferred);
    ui->wier2_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Preferred);
    ui->wier3_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Preferred);
    ui->wier4_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Preferred);
    ui->wier5_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Preferred);
    ui->wier6_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Preferred);
    ui->wier7_wys->changeSize(0 , wier7 * Size.rheight() , QSizePolicy::Preferred);
    ui->wier8_wys->changeSize(0 , wier8 * Size.rheight() , QSizePolicy::Preferred);

}
*/