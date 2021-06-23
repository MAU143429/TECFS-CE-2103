#include "cerobot.h"
#include "ui_cerobot.h"
#include <QFileDialog>
#include "../Objects/TypeMessage.h"
#include "../UtilJSON/JSON_Management.h"
#include "../Algorithms/HuffmanCompression.h"

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
        auto robotMsg = new TypeMessage();
        robotMsg->setAppName("CEROBOT");
        robotMsg->setPath(ui->pathLine->text().toStdString());
        robotMsg->setClientType("APP");

        string jsonMsg = JSON_Management::TypeMessageToJSON(robotMsg);
        pair<string,SimplyLinkedList<Huffman_pair*>*> compressed;
        compressed = HuffmanCompression::buildHuffmanTree(jsonMsg);
        auto huffmanMsg = new Huffman_Message();
        huffmanMsg->setCompress_Code(compressed.first);
        for (int i = 0; i < compressed.second->getLen(); ++i) {
            huffmanMsg->getHuffman_Table()->append(compressed.second->get(i));
        }
        string finalMsg = JSON_Management::HuffmanMessageToJSON(huffmanMsg);

    }
}

//Boton para ir al menu principal
void ceROBOT::on_backBtn_clicked()
{
    this->hide();
    this->parentWidget()->show();
}
