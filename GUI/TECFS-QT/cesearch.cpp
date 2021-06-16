#include "cesearch.h"
#include "ui_cesearch.h"
#include <QMessageBox>

ceSEARCH::ceSEARCH(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ceSEARCH)
{
    ui->setupUi(this);
}

ceSEARCH::~ceSEARCH()
{
    delete ui;
}

//Funcion del boton de atras.
void ceSEARCH::on_backBtn_clicked()
{
    this->hide();
    this->parentWidget()->show();
}

//Funcion del boton de buscar.
void ceSEARCH::on_searchBtn_clicked()
{
    if(ui->searchBar->text() == nullptr or ui->searchBar->text() == ""){
        ui->resultLabel->setText("error");
    }else{
        // busqueda
    }
}
