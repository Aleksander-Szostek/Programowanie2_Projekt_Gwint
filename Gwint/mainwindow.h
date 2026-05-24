#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    gra *Gra; // dodaje tutaj Gra aby nie znikała tak jak to zrobiłem wcześniej

    void obslugaRysowaniaKarty(karta* nowaKarta, gra::RzadPlanszy rzad, int indeks, int nr_gr);
    void obslugaCzyszczeniaLayoutu(gra::RzadPlanszy rzad);
    void obslugaAktualizacjiPunkt(int punkty[6]);
    QLayout* getLayoutByEnum(gra::RzadPlanszy rzad);
    void zmianaStrony(int indeks);
    void zmianaGSLabel(StanGry GameState, bool p1_pas, bool p2_pas);

    int pointsStorage[12];

};
#endif // MAINWINDOW_H
