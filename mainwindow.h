#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <portaudio.h>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_button1_clicked();
    void on_button2_clicked();
    void onCheckBoxToggled(bool checked); // Declaración del slot

private:
    Ui::MainWindow *ui;
    void fillComboBoxes();
    void fillComboBoxes2();
    void getSelectedValues();
    QProcess process; // Declarar el QProcess como miembro de la clase


};
#endif // MAINWINDOW_H
