#include "cesearch.h"
#include "ui_cesearch.h"
#include <QMessageBox>
#include "../Objects/TypeMessage.h"
#include "../UtilJSON/JSON_Management.h"
#include "../Algorithms/HuffmanCompression.h"

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
        ui->resultLabel->setText("Error, debes escribir una palabra en la barra de busqueda.");
    }else{
        auto searchMsg = new TypeMessage();
        searchMsg->setAppName("CESEARCH");
        searchMsg->setKeyWord(ui->searchBar->text().toStdString());
        searchMsg->setClientType("APP");

        string jsonMsg = JSON_Management::TypeMessageToJSON(searchMsg);
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
