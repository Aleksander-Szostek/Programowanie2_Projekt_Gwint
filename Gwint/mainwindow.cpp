#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card_loader.h"
#include "deck_loader.h"
#include "deck_saver.h"
#include "card_button.h"
#include "card_button_talia.h"
#include "gra.h"
#include "i_constant_valuse.h"
// one sa do wczytywania plikow
#include <QDir>
#include <QFileInfoList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    zmianaStrony(0);

    //blokuje na sztywno rozmiar, karty nie rozwalauja ui ale nie da się zwiększyć ekranu
    this->setMinimumSize(this->size());
    this->setMaximumSize(this->size());

    Gra = new gra();

    connect(Gra, &gra::nakazRysowaniaKarty, this, &MainWindow::obslugaRysowaniaKarty);
    connect(Gra, &gra::nakazCzyszczeniaLayoutu, this, &MainWindow::obslugaCzyszczeniaLayoutu);
    connect(Gra, &gra::nakazAktualizacjiPunkt, this, &MainWindow::obslugaAktualizacjiPunkt);
    connect(Gra, &gra::nakazZmianyStrony, this, &MainWindow::zmianaStrony);
    connect(Gra, &gra::nakazShowGS, this, &MainWindow::zmianaGSLabel);

    ui->comboBox->addItem("Królestwa Północy");
    ui->comboBox->addItem("Nilfgard");
    ui->comboBox->addItem("Potwory");
    ui->comboBox->addItem("Scoia'tael");
    ui->comboBox->addItem("Skelige");

    //ui->layout_prawy->setAlignment(Qt::AlignLeft | Qt::AlignTop);


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

    odswiezListeTalii();
    //    ui->label->setText(karci.nazwa);
    //else
    //    ui->label->setText("To nie melee");
    //testowałem czy odczyt kategorii i frakcji działa (działa)


                    // ten frakment daje nam vernona rocha, co za temerię zrobi wszystko
    int test = 42;

    card_loader zaladuj;
    karta* testowa_karta = new karta;
    zaladuj.zaladuj_karte(test, testowa_karta);

    //ui->label->setText(testowa_karta->getNazwa() + " " + QString::number(testowa_karta->getSila()) + " " + testowa_karta->getFlavor());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_dobierz_clicked() {
    Gra->graczZagrajKarte(0,2);
}

void MainWindow::on_wyczysc_button_clicked()
{
    Gra->gameClear();
}

//funkcja pozwala na przejście z menu do planszy po kliknięciu start
void MainWindow::on_Start_Button_clicked()
{
    //this->showMaximized();
    zmianaStrony(1);

    Gra->zainicjalizuj_gre(ui->talie->currentText(),ui->talie_bot->currentText());
}

// Funkcja pomocnicza zwracająca wskaźnik do layoutu na podstawie enuma
QLayout* MainWindow::getLayoutByEnum(RzadPlanszy rzad) {
    switch(rzad) {
    case P1_Hand: return ui->layout_reki;

    case P1_Melee: return ui->player1_melee;
    case P1_Range: return ui->player1_ranged;
    case P1_Siege: return ui->player1_siege;
    case P2_Melee: return ui->player2_melee;
    case P2_Range: return ui->player2_ranged;
    case P2_Siege: return ui->player2_siege;

    case P1_Melee_Horn: return ui->player1_melee_horn;
    case P1_Range_Horn: return ui->player1_ranged_horn;
    case P1_Siege_Horn: return ui->player1_siege_horn;
    case P2_Melee_Horn: return ui->player2_melee_horn;
    case P2_Range_Horn: return ui->player2_ranged_horn;
    case P2_Siege_Horn: return ui->player2_siege_horn;

    case Weather: return ui->pogoda;

    case P1_Leader: return ui->player1_leader;
    case P2_Leader: return ui->player2_leader;

    default: return nullptr;
    }
}

void MainWindow::obslugaCzyszczeniaLayoutu(RzadPlanszy rzad) {
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

void MainWindow::obslugaRysowaniaKarty(karta* nowaKarta, RzadPlanszy rzad, int indeks, int nr_gr){
    QLayout* docelowyLayout = getLayoutByEnum(rzad);
    if (!docelowyLayout) return;

    Card_Button* nowyPrzycisk = new Card_Button(nowaKarta, this);

    if (rzad == P1_Hand) {

        connect(nowyPrzycisk, &Card_Button::clicked, Gra, [=](){
            qDebug() << "Zagrano karte: " + nowaKarta->getNazwa() + "   Gracz: " + QString::number(nr_gr);
            Gra->graczZagrajKarte(indeks, nr_gr);
            qDebug() << "Koniec connecta";
        });

    }
    else {

        connect(nowyPrzycisk, &Card_Button::clicked, Gra, [=](){
            qDebug() << "Wybrano karte: " + nowaKarta->getNazwa();
            Gra->wybranoKarte(rzad, indeks);
            qDebug() << "Koniec connecta";
        });

    }

    nowyPrzycisk->refresh();
    docelowyLayout->addWidget(nowyPrzycisk);
}

void MainWindow::obslugaAktualizacjiPunkt(int punkty[12]){
    ui->player1_melee_nr->setText(QString::number(punkty[int(Pkt::p1_M)]));
    ui->player1_ranged_nr->setText(QString::number(punkty[int(Pkt::p1_R)]));
    ui->player1_siege_nr->setText(QString::number(punkty[int(Pkt::p1_S)]));
    ui->player2_melee_nr->setText(QString::number(punkty[int(Pkt::p2_M)]));
    ui->player2_ranged_nr->setText(QString::number(punkty[int(Pkt::p2_R)]));
    ui->player2_siege_nr->setText(QString::number(punkty[int(Pkt::p2_S)]));

    ui->player1_kart_w_talii->setText("Talia: " + QString::number(punkty[int(Pkt::p1_DS)]));
    ui->player2_kart_w_talii->setText("Talia: " + QString::number(punkty[int(Pkt::p2_DS)]));
    ui->player1_kart_w_rece->setText("Karty: " + QString::number(punkty[int(Pkt::p1_HS)]) + "\n" +
                                     "Punkty: " + QString::number(punkty[int(Pkt::p1_GS)]));
    ui->player2_kart_w_rece->setText("Karty: " + QString::number(punkty[int(Pkt::p2_HS)]) + "\n" +
                                     "Punkty: " + QString::number(punkty[int(Pkt::p2_GS)]));

    for (int i = 0; i < 12; i++) {
        pointsStorage[i] = punkty[i];
    }
}
void MainWindow::on_p1_pas_clicked() {
    Gra->graczPas(1);
}
void MainWindow::on_p2_pas_clicked() {
    Gra->graczPas(2);
}

void MainWindow::zmianaStrony(int indeks) {
    ui->stackedWidget->setCurrentIndex(indeks);

    switch (indeks) {
        case 0: {
            this->setStyleSheet(
                "#centralwidget {"
                "background-color: #686965;"
                "}"
            );

            odswiezListeTalii();

            ui->WRundy_1->setText("");
            ui->WRundy_2->setText("");
            ui->WRundy_3->setText("");
            ui->WM_1->setText("");
            ui->WM_2->setText("");
            ui->WM_3->setText("");
            ui->WR_1->setText("");
            ui->WR_2->setText("");
            ui->WR_3->setText("");
            ui->WS_1->setText("");
            ui->WS_2->setText("");
            ui->WS_3->setText("");

            break;
        }



        case 1: {
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

            //ui->wier1_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
            //ui->wier2_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
            //ui->wier3_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
            //ui->wier4_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
            //ui->wier5_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
            //ui->wier6_wys->changeSize(0 , wier1_6 * Size.rheight() , QSizePolicy::Expanding);
            //ui->wier7_wys->changeSize(0 , wier7 * Size.rheight() , QSizePolicy::Expanding);

            ui->player2_melee_nr->setMinimumSize(0 , (wier1_6 * Size.rheight()));
            ui->player2_ranged_nr->setMinimumSize(0 , (wier1_6 * Size.rheight()));
            ui->player2_siege_nr->setMinimumSize(0 , (wier1_6 * Size.rheight()));
            ui->player1_melee_nr->setMinimumSize(0 , (wier1_6 * Size.rheight()));
            ui->player1_ranged_nr->setMinimumSize(0 , (wier1_6 * Size.rheight()));
            ui->player1_siege_nr->setMinimumSize(0 , (wier1_6 * Size.rheight()));
            break;
        }



        case 2: {
            this->setStyleSheet(
                "#centralwidget {"
                "background-color: #686965;"
                "}"
                );

            switch(Gra->getNrRundy()){
                case 1: {
                    ui->WM_1->setText(QString::number(pointsStorage[int(Pkt::p1_M)]) +
                                      " / " +
                                      QString::number(pointsStorage[int(Pkt::p2_M)]));

                    ui->WR_1->setText(QString::number(pointsStorage[int(Pkt::p1_R)]) +
                                      " / " +
                                      QString::number(pointsStorage[int(Pkt::p2_R)]));

                    ui->WS_1->setText(QString::number(pointsStorage[int(Pkt::p1_S)]) +
                                      " / " +
                                      QString::number(pointsStorage[int(Pkt::p2_S)]));

                    ui->WRundy_1->setText(QString::number(pointsStorage[int(Pkt::p1_GS)]) +
                                          " / " +
                                          QString::number(pointsStorage[int(Pkt::p2_GS)])
                                          );
                    break;
                }

                case 2: {
                    ui->WM_2->setText(QString::number(pointsStorage[int(Pkt::p1_M)]) +
                                      " / " +
                                      QString::number(pointsStorage[int(Pkt::p2_M)]));

                    ui->WR_2->setText(QString::number(pointsStorage[int(Pkt::p1_R)]) +
                                      " / " +
                                      QString::number(pointsStorage[int(Pkt::p2_R)]));

                    ui->WS_2->setText(QString::number(pointsStorage[int(Pkt::p1_S)]) +
                                      " / " +
                                      QString::number(pointsStorage[int(Pkt::p2_S)]));

                    ui->WRundy_2->setText(QString::number(pointsStorage[int(Pkt::p1_GS)]) +
                                          " / " +
                                          QString::number(pointsStorage[int(Pkt::p2_GS)]));
                    break;
                }

                case 3: {
                    ui->WM_3->setText(QString::number(pointsStorage[int(Pkt::p1_M)]) +
                                      " / " +
                                      QString::number(pointsStorage[int(Pkt::p2_M)]));

                    ui->WR_3->setText(QString::number(pointsStorage[int(Pkt::p1_R)]) +
                                      " / " +
                                      QString::number(pointsStorage[int(Pkt::p2_R)]));

                    ui->WS_3->setText(QString::number(pointsStorage[int(Pkt::p1_S)]) +
                                      " / " +
                                      QString::number(pointsStorage[int(Pkt::p2_S)]));

                    ui->WRundy_3->setText(QString::number(pointsStorage[int(Pkt::p1_GS)]) +
                                          " / " +
                                          QString::number(pointsStorage[int(Pkt::p2_GS)]));
                    break;
                }

                default:
                    break;
            }

            if (Gra->getGameState() == StanGry::KoniecGry) {
                ui->nextRundaBtn->setText("Koniec gry");
            }
            else {
                ui->nextRundaBtn->setText("Następna runda");
            }
        }



        case 3: {
            odswierzanieKartWTalii();
            odswiezListeTalii();
        }



        default:
            break;
}
}
void MainWindow::on_nextRundaBtn_clicked() {
    if (Gra->getGameState() == KoniecGry)
        zmianaStrony(0);
    else
        zmianaStrony(1);
}

void MainWindow::zmianaGSLabel(StanGry GameState, bool p1_pas, bool p2_pas){
    if (p1_pas)
        this->ui->p1_pas->setStyleSheet("background-color: darkgray");
    else
        this->ui->p1_pas->setStyleSheet("background-color: white");

    if (p2_pas)
        this->ui->p2_pas->setStyleSheet("background-color: darkgray");
    else
        this->ui->p2_pas->setStyleSheet("background-color: white");
}

void MainWindow::on_player2_siege_nr_clicked() {
    Gra->wybranoLinie(P2_Siege);
    return;
}
void MainWindow::on_player2_ranged_nr_clicked() {
    Gra->wybranoLinie(P2_Range);
    return;
}
void MainWindow::on_player2_melee_nr_clicked() {
    Gra->wybranoLinie(P2_Melee);
    return;
}
void MainWindow::on_player1_melee_nr_clicked() {
    Gra->wybranoLinie(P1_Melee);
    return;
}
void MainWindow::on_player1_ranged_nr_clicked() {
    Gra->wybranoLinie(P1_Range);
    return;
}
void MainWindow::on_player1_siege_nr_clicked() {
    Gra->wybranoLinie(P1_Siege);
    return;
}
void MainWindow::obslugaDodaniaDoTalii(karta* daneKarty)
{

    if (!daneKarty) return;
    //dodaje aby nie dalo się zmieniać typu talii w trakcie robienia swojej
    if (wybraneKarty.empty()) {
        ui->comboBox->setEnabled(false);
    }

    karta* kopiaKarty = new karta(*daneKarty);
    wybraneKarty.push_back(kopiaKarty);


    Card_Button* przyciskDodany = new Card_Button(kopiaKarty, this);
    przyciskDodany->refresh();

    ui->layout_lewy->addWidget(przyciskDodany,wybraneKarty.size()/7,wybraneKarty.size()%7);


    connect(przyciskDodany, &Card_Button::clicked, this, [=]() {
        ui->layout_lewy->removeWidget(przyciskDodany);
        //to auto sam przypisuje tym zmiennej, tak jest łatwiej
        auto iterator = std::find(wybraneKarty.begin(), wybraneKarty.end(), kopiaKarty);
        if (iterator != wybraneKarty.end()) {
            wybraneKarty.erase(iterator);
        }
         qDebug()<<"Usunieto z talii: "<<kopiaKarty->getNazwa();
        delete kopiaKarty;
        przyciskDodany->deleteLater();

        if (wybraneKarty.empty()) {
            ui->comboBox->setEnabled(true);
        }

    });

    qDebug() << "Dodano do tworzonej talii: " << kopiaKarty->getNazwa()<< " Rozmiar talii: " << wybraneKarty.size();
}


void MainWindow::odswierzanieKartWTalii(){
    QString wybranaFrakcja = ui->comboBox->currentText();
    Frakcja szukanaFrakcja=Frakcja::Polnoc;
    if(wybranaFrakcja=="Królestwa Północy"){
        szukanaFrakcja = Frakcja::Polnoc;
    }
    else if(wybranaFrakcja=="Nilfgard"){
        szukanaFrakcja = Frakcja::Nilfgard;
    }
    else if(wybranaFrakcja=="Potwory"){
        szukanaFrakcja = Frakcja::Potwory;
    }
    else if(wybranaFrakcja=="Scoia'tael"){
        szukanaFrakcja = Frakcja::Elfy;
    }
    else if(wybranaFrakcja=="Skelige"){
        szukanaFrakcja = Frakcja::Skelige;
    }
    QGridLayout* layoutPrawy = ui->layout_prawy;

    if (!layoutPrawy) return;


    QLayoutItem* item;
    while ((item = layoutPrawy->takeAt(0)) != nullptr) {
        if (item->widget()) {
            QWidget* widget = item->widget();
            widget->hide();
            widget->deleteLater();
        }
        delete item;
    }

    card_loader zaladuj;
    int i=0;
    for(int idKarty=0; idKarty<=328;idKarty++){

        karta* sprawdzanaKarta = new karta();
        zaladuj.zaladuj_karte(idKarty, sprawdzanaKarta);

        if((sprawdzanaKarta->getFrakcja() == szukanaFrakcja || sprawdzanaKarta->getFrakcja() == Frakcja::Neutral)
            && sprawdzanaKarta->getNazwa() != "Error: niezdefiniowany typ karty"
            && sprawdzanaKarta->getMax() != 0) {


            Card_Button_Talia* nowaKartaFrakcji = new Card_Button_Talia(sprawdzanaKarta, this);
            nowaKartaFrakcji->refresh();


            connect(nowaKartaFrakcji, &Card_Button_Talia::clicked, this, [=]() {
                obslugaDodaniaDoTalii(sprawdzanaKarta);
            });

            layoutPrawy->addWidget(nowaKartaFrakcji, i / 7, i % 7);
            i++;
            // -------------------------

        }
        else{
            delete sprawdzanaKarta;
        }
    }

}

void MainWindow::odswiezListeTalii()
{
    ui->talie->clear();
    ui->talie_bot->clear();
    QDir katalog(QDir::currentPath());

    QFileInfoList pliki = katalog.entryInfoList(
        QStringList() << "*.txt",
        QDir::Files
        );

    for (const QFileInfo &plik : pliki)
    {
        if (plik.fileName() != "cards_list.txt" && plik.fileName() != "CMakeCache.txt")
        {
            ui->talie->addItem(plik.fileName());
            ui->talie_bot->addItem(plik.fileName());
        }
    }
}


void MainWindow::on_Talia_Button_clicked()
{
    zmianaStrony(3);
}


void MainWindow::on_powrot_Button_clicked()
{
    zmianaStrony(0);
}


void MainWindow::on_zapisz_Button_clicked()
{
    QString nazwa_pliku = ui->zapisz_tekst->toPlainText().trimmed(); //to trimmed powoduje usuniecie białych znakow spacja /n itp
    qDebug()<<"Nazwa pliku: "<<nazwa_pliku;

    //tu jeszcze musze zrobic sprawdzanie poprawnosci nazwy pliku czy np nie ma enterow, spacji albo czy w ogole jest
    if (nazwa_pliku.isEmpty() || nazwa_pliku.contains('/') || nazwa_pliku.contains('\\')) {
        ui->zapisz_tekst->setStyleSheet("background-color: #a63535; color: white;");
        qDebug() << "Niepoprawna nazwa pliku!";
        return;
    }

    if (!nazwa_pliku.endsWith(".txt")) {
        nazwa_pliku += ".txt";
    }

    if (wybraneKarty.empty()) {
        qDebug() << "Nie można zapisać pustej talii";
        return;
    }
    deck nowaTalia;

    nowaTalia.makeDeckZUI(wybraneKarty);
    if (nowaTalia.DeckValid) {
        qDebug() << "Talia poprawna";
        deck_saver saver;
        saver.save_deck(nowaTalia, nazwa_pliku);
    }
    else {
        qDebug() << "Talia niepoprawna";
        ui->zapisz_tekst->setStyleSheet("background-color: #a63535;");
    }

}

void MainWindow::obslugaRysowaniaKartDoTalii(){
    //bedzie rysowalo wszystkie karty z danej talii
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    odswierzanieKartWTalii();
}

