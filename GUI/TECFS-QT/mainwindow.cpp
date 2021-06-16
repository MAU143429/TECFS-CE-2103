#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cerobot.h"
#include "cesearch.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ceRobotBtn_clicked()
{
    ceROBOT *robot = new ceROBOT(this);
    this->hide();
    robot->show();
}

void MainWindow::on_ceSearchBtn_clicked()
{
    ceSEARCH *search = new ceSEARCH(this);
    this->hide();
    search->show();
}
