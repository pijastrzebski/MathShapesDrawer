#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonAstroid_clicked();

    void on_buttonCycloid_clicked();

    void on_buttonHuygens_clicked();

    void on_buttonHypoCycloid_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
