#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColor>
#include "eshapes.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonAstroid_clicked()
{
    this->ui->renderArea->setShape(EShapes::Astroid)
                        ->setBackgroundColor(Qt::GlobalColor::red)
                        ->repaint();
}

void MainWindow::on_buttonCycloid_clicked()
{
    this->ui->renderArea->setShape(EShapes::Cycloid)
                        ->setBackgroundColor(Qt::GlobalColor::green)
                        ->repaint();
}

void MainWindow::on_buttonHuygens_clicked()
{
    this->ui->renderArea->setShape(EShapes::HuygensCicloid)
                        ->setBackgroundColor(Qt::GlobalColor::blue)
                        ->repaint();
}

void MainWindow::on_buttonHypoCycloid_clicked()
{
    this->ui->renderArea->setShape(EShapes::HypoCycloid)
                        ->setBackgroundColor(Qt::GlobalColor::yellow)
                        ->repaint();
}
