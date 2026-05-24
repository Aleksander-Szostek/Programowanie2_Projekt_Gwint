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
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());

    Gra = new gra();
    //connect(Gra, &gra::dodanieKarty, this, &MainWindow::obsugaDodanejKarty);
    connect(Gra, &gra::nakazRysowaniaKarty, this, &MainWindow::obslugaRysowaniaKarty);
    connect(Gra, &gra::nakazCzyszczeniaLayoutu, this, &MainWindow::obslugaCzyszczeniaLayoutu);
    connect(Gra, &gra::nakazAktualizacjiPunkt, this, &MainWindow::obslugaAktualizacjiPunkt);
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


    qDebug() << QPixmap(":/plansza.jpg").isNull();


    //    ui->label->setText(karci.nazwa);
    //else
    //    ui->label->setText("To nie melee");
    //testowałem czy odczyt kategorii i frakcji działa (działa)


                    // ten frakment daje nam vernona rocha, co za temerię zrobi wszystko
    int test = 42;

    card_loader zaladuj;
    karta* testowa_karta = new karta;
    zaladuj.zaladuj_karte(test, testowa_karta);

    ui->label->setText(testowa_karta->getNazwa() + " " + QString::number(testowa_karta->getSila()) + " " + testowa_karta->getFlavor());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{

}


void MainWindow::on_button_dobierz_clicked() {
    Gra->graczZagrajKarte(0,2);
}
//{
//    //tworze testwa karte czy się dodają poprawnie
//    //tak sobie dodałem wczytywanie kart losowych
//    karta* nowaKartaDane = new karta();
//    //nowaKartaDane->setName("Bogata kurcze piechota");
//    //nowaKartaDane->setSilaBaz(100);
//
//
//    card_loader karta;
//    karta.zaladuj_karte((rand()%250 + 1),nowaKartaDane);
//    //nowaKartaDane->updateSila(false, false, 0);   niepotrzebne bo card loader to też robi
//    qDebug()<<"kategoria:" <<nowaKartaDane->getKategoria();
//    //nowaKartaDane->setLeg(false);
//
//    Card_Button *przyciskKarty = new Card_Button(nowaKartaDane, ui->layout_reki->parentWidget());
//    przyciskKarty->getCardData();
//    przyciskKarty->refresh();
//    ui->layout_reki->addWidget(przyciskKarty);
//
//
//connect(przyciskKarty, &Card_Button::clicked, this, [=]() {
//
//    qDebug() << "Wybrano karte: " << nowaKartaDane->getNazwa();
//    ui->layout_reki->removeWidget(przyciskKarty);
//    przyciskKarty->hide();
//    przyciskKarty->deleteLater();
//
//    Gra->zagranoKarte(przyciskKarty->getIndeks(),1);
//
//}


void MainWindow::on_wyczysc_button_clicked()
{
//    Gra->gameClear(kartyNaPlanszy, ui->player1_melee);
    Gra->gameClear();
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
    ui->kol0_szer->changeSize(kol0 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol1_szer->changeSize(kol1 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol2_szer->changeSize(kol2 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol3_szer->changeSize(kol3 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol4_szer->changeSize(kol4 * Size.rwidth() , 0 , QSizePolicy::Fixed);
//    ui->kol5_szer->changeSize(kol5 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol6_szer->changeSize(kol6 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol7_szer->changeSize(kol7 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol8_szer->changeSize(kol8 * Size.rwidth() , 0 , QSizePolicy::Fixed);

    ui->wier1_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier2_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier3_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier4_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier5_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier6_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier7_wys->changeSize(0 , wier7 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier8_wys->changeSize(0 , wier8 * Size.rheight() , QSizePolicy::Fixed);

    Gra->zainicjalizuj_gre("deck1.txt","deck1.txt");
}

void MainWindow::resizeEvent(QResizeEvent *a){

    QSize Size = this->size();
    ui->kol0_szer->changeSize(kol0 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol1_szer->changeSize(kol1 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol2_szer->changeSize(kol2 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol3_szer->changeSize(kol3 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol4_szer->changeSize(kol4 * Size.rwidth() , 0 , QSizePolicy::Fixed);
//    ui->kol5_szer->changeSize(kol5 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol6_szer->changeSize(kol6 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol7_szer->changeSize(kol7 * Size.rwidth() , 0 , QSizePolicy::Fixed);
    ui->kol8_szer->changeSize(kol8 * Size.rwidth() , 0 , QSizePolicy::Fixed);

    ui->wier1_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier2_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier3_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier4_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier5_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier6_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier7_wys->changeSize(0 , wier7 * Size.rheight() , QSizePolicy::Expanding);
    ui->wier8_wys->changeSize(0 , wier8 * Size.rheight() , QSizePolicy::Fixed);

}/*
void MainWindow::obsugaDodanejKarty(karta* nowaKarta, gra::RzadPlanszy rzad){
    QLayout* docelowyLayout = nullptr;
    switch(rzad) {
    case gra::P1_Melee: docelowyLayout = ui->player1_melee; break;
    // Założyłem przykładowe nazwy dla pozostałych Twoich layoutów:
    case gra::P1_Range: docelowyLayout = ui->player1_ranged; break;
    case gra::P1_Siege: docelowyLayout = ui->player1_siege; break;

    case gra::P2_Melee: docelowyLayout = ui->player2_melee; break;
    case gra::P2_Range: docelowyLayout = ui->player2_ranged; break;
    case gra::P2_Siege: docelowyLayout = ui->player2_siege; break;

    default: return;
    }

    if (!docelowyLayout) return;

    // 2. Tworzymy nowy fizyczny przycisk na planszy (wskazujemy centralwidget lub 'this' jako parent)
    Card_Button* nowyPrzycisk = new Card_Button(nowaKarta, this);
    nowyPrzycisk->refresh();

    // 3. Dodajemy go do widoku i zapamiętujemy w wektorze w MainWindow
    docelowyLayout->addWidget(nowyPrzycisk);

    // Zamiast jednego wektora, najlepiej trzymać je globalnie w MainWindow,
    // aby móc je później łatwo wyczyścić przy gameClear
    kartyNaPlanszy.push_back(nowyPrzycisk);

    qDebug() << "Narysowano karte w GUI:" << nowaKarta->getNazwa();

};*/

// Funkcja pomocnicza zwracająca wskaźnik do layoutu na podstawie enuma
QLayout* MainWindow::getLayoutByEnum(gra::RzadPlanszy rzad) {
    //return ui->player2_melee; testowalem czy w ogole dziala
    switch(rzad) {
    case gra::P1_Hand: return ui->layout_reki;
    case gra::P1_Melee: return ui->player1_melee;
    case gra::P1_Range: return ui->player1_ranged;
    case gra::P1_Siege: return ui->player1_siege;
    case gra::P2_Melee: return ui->player2_melee;
    case gra::P2_Range: return ui->player2_ranged;
    case gra::P2_Siege: return ui->player2_siege;
    //case gra::P2_Hand: return ;
    //case gra::P1_Spell: return ui->player2_siege_horn; aby na razie sie nie pokazywala reszta
    default: return nullptr;
    }
}

void MainWindow::obslugaCzyszczeniaLayoutu(gra::RzadPlanszy rzad) {
    QLayout* layout = getLayoutByEnum(rzad);
    if (!layout) return;


    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            QWidget* widget = item->widget();
            widget->hide();
            widget->deleteLater();
        }
        delete item;
    }
}

void MainWindow::obslugaRysowaniaKarty(karta* nowaKarta, gra::RzadPlanszy rzad, int indeks, int nr_gr) {
    QLayout* docelowyLayout = getLayoutByEnum(rzad);
    if (!docelowyLayout) return;


    Card_Button* nowyPrzycisk = new Card_Button(nowaKarta, this);
    connect(nowyPrzycisk, &Card_Button::clicked, Gra, [=](){
        //Gra->graczZagrajKarte(indeks, nr_gr);
        Gra->zagranoKarte(indeks,nr_gr);
    });
    if (rzad == gra::P1_Hand) {
        connect(nowyPrzycisk, &Card_Button::clicked, Gra, [=](){
            Gra->graczZagrajKarte(indeks, nr_gr);
        });
    }
    else {
        connect(nowyPrzycisk, &Card_Button::clicked, Gra, [=](){
            Gra->wybranoKarte(rzad, indeks);
        });
    }

    nowyPrzycisk->refresh();
    docelowyLayout->addWidget(nowyPrzycisk);

}

void MainWindow::obslugaAktualizacjiPunkt(int punkty[12]){
    ui->player1_melee_nr->setText(QString::number(punkty[0]));
    ui->player1_ranged_nr->setText(QString::number(punkty[1]));
    ui->player1_siege_nr->setText(QString::number(punkty[2]));
    ui->player2_melee_nr->setText(QString::number(punkty[3]));
    ui->player2_ranged_nr->setText(QString::number(punkty[4]));
    ui->player2_siege_nr->setText(QString::number(punkty[5]));

    ui->player1_kart_w_talii->setText("Talia: " + QString::number(punkty[6]));
    ui->player2_kart_w_talii->setText("Talia: " + QString::number(punkty[7]));
    ui->player1_kart_w_rece->setText("Karty: " + QString::number(punkty[8]) + "\n" + "Punkty: " + QString::number(punkty[10]));
    ui->player2_kart_w_rece->setText("Karty: " + QString::number(punkty[9]) + "\n" + "Punkty: " + QString::number(punkty[11]));

}
void MainWindow::on_p1_pas_clicked()
{
    Gra->graczPas(1);
}


void MainWindow::on_p2_pas_clicked()
{
    Gra->graczPas(2);
}

