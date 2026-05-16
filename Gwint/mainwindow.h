#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "card_button.h"
#include <vector>
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
    void on_verticalSlider_sliderMoved(int position);

    void on_button_dobierz_clicked();

    void on_wyczysc_button_clicked();

    void on_Start_Button_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Card_Button*> kartyNaPlanszy; // dodaje karty ktore są już na planszy do vectora
    std::vector<karta*> daneKartNaPlanszy; // zapisuje dane kart obecnie na planszy aby moc je na nowo narysowac
    gra *Gra; // dodaje tutaj Gra aby nie znikała tak jak to zrobiłem wcześniej

};
#endif // MAINWINDOW_H
