#include "cerobot.h"
#include "ui_cerobot.h"
#include <QFileDialog>
#include "../Objects/TypeMessage.h"
#include "../UtilJSON/JSON_Management.h"

ceROBOT::ceROBOT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ceROBOT)
{
    ui->setupUi(this);
    string path;
}

ceROBOT::~ceROBOT()
{
    delete ui;
}

//Funcion del boton para subir una carpeta.
void ceROBOT::on_uploadBtn_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this, "Select a Directory");
}

//Funcion del boton para subir al server.
void ceROBOT::on_pushBtn_clicked()
{
    if( true){

    }else{
        auto robotMsg = new TypeMessage();
        robotMsg->setAppName("CEROBOT");
        robotMsg->setPath("");
        robotMsg->setClientType("APP");

        string jsonMsg = JSON_Management::TypeMessageToJSON(robotMsg);

    }
}

//Boton para ir al menu principal
void ceROBOT::on_backBtn_clicked()
{
    this->hide();
    this->parentWidget()->show();
}
