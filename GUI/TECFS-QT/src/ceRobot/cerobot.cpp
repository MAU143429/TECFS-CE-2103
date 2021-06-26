#include "cerobot.h"
#include "ui_cerobot.h"
#include <QFileDialog>
#include "../Objects/TypeMessage.h"
#include "../UtilJSON/JSON_Management.h"
#include "../Algorithms/HuffmanCompression.h"
#include "../Socket/Client.h"

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
    ui->pathLine->setText(filePath);
}

//Funcion del boton para subir al server.
void ceROBOT::on_pushBtn_clicked()
{
    if(ui->pathLine->text() == "Direccion de la carpeta"){
        ui->statusLabel->setText("Error, debes cargar una carpeta.");
    }else{

        ui->statusLabel->setText("Enviando directorio...");
        auto robotMsg = new TypeMessage();
        robotMsg->setAppName("CEROBOT");
        robotMsg->setPath(ui->pathLine->text().toStdString());
        robotMsg->setClientType("APP");
        string jsonMsg = JSON_Management::TypeMessageToJSON(robotMsg);

        Client::getInstance()->Send(jsonMsg.c_str());

        string response;
        while(response.empty()){
            response = Client::getInstance()->ReadString();
        }
        Client::getInstance()->setResponse("");
        auto huffmanMessage = new Huffman_Message();
        huffmanMessage = JSON_Management::DeserializetoHuffmanMessage(response);
        string msg = HuffmanCompression::Decode_Huffman(huffmanMessage->getCompress_Code(),huffmanMessage->getHuffman_Table());
        string status = JSON_Management::GetJSONString("Save_Status", msg);
        if(status == "TRUE"){
            ui->statusLabel->setText("Los datos fueron almacenados");
        }else{
            ui->statusLabel->setText("Error, los datos NO fueron almacenados");
        }
    }
}

//Boton para ir al menu principal
void ceROBOT::on_backBtn_clicked()
{
    this->hide();
    this->parentWidget()->show();
}
