#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "card_button_talia.h"
#include "gra.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_button_dobierz_clicked();

    void on_wyczysc_button_clicked();

    void on_Start_Button_clicked();

    void on_p2_pas_clicked();

    void on_p1_pas_clicked();

    void on_nextRundaBtn_clicked();

    void on_player2_siege_nr_clicked();

    void on_player2_ranged_nr_clicked();

    void on_player2_melee_nr_clicked();

    void on_player1_melee_nr_clicked();

    void on_player1_ranged_nr_clicked();

    void on_player1_siege_nr_clicked();
    void on_Talia_Button_clicked();

    void on_powrot_Button_clicked();

    void on_zapisz_Button_clicked();

    void odswierzanieKartWTalii();


    void on_comboBox_currentIndexChanged(int index);


    void obslugaDodaniaDoTalii(karta* daneKarty);
    void odswiezListeTalii();

    //void usunZTalii(Card_Button_Talia* przycisk);

private:
    Ui::MainWindow *ui;
    gra *Gra; // dodaje tutaj Gra aby nie znikała tak jak to zrobiłem wcześniej

    void obslugaRysowaniaKarty(karta* nowaKarta, RzadPlanszy rzad, int indeks, int nr_gr);
    void obslugaCzyszczeniaLayoutu(RzadPlanszy rzad);
    void obslugaAktualizacjiPunkt(int punkty[6]);
    QLayout* getLayoutByEnum(RzadPlanszy rzad);
    void zmianaStrony(int indeks);
    void zmianaGSLabel(StanGry GameState, bool p1_pas, bool p2_pas);

    int pointsStorage[12];

    std::vector<karta*> wybraneKarty;
    std::vector<Card_Button*> kartyWTalii;
    //void resizeEvent(QResizeEvent *a) override;
    //void obsugaDodanejKarty(karta* daneKarty, gra::RzadPlanszy rzad);
    //void obslugaCzyszczeniaLayoutu(gra::RzadPlanszy rzad);
    

    void obslugaRysowaniaKartDoTalii(); //to do zrobienia jeszcze
    
};
#endif // MAINWINDOW_H
