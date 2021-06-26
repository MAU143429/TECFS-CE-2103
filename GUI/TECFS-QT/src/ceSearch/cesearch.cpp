#include "cesearch.h"
#include "ui_cesearch.h"
#include <QMessageBox>
#include "../Objects/TypeMessage.h"
#include "../UtilJSON/JSON_Management.h"
#include "../Algorithms/HuffmanCompression.h"
#include "../Socket/Client.h"
#include "../../../lib/DataStructures/SimplyList.h"

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
        Client::getInstance()->Send(jsonMsg.c_str());

        string response;
        while(response.empty()){
            response = Client::getInstance()->ReadString();
        }
        Client::getInstance()->setResponse("");
        auto huffmanMessage = new Huffman_Message();
        huffmanMessage = JSON_Management::DeserializetoHuffmanMessage(response);
        string msg = HuffmanCompression::Decode_Huffman(huffmanMessage->getCompress_Code(),huffmanMessage->getHuffman_Table());

        auto blockBools = new SimplyLinkedList<bool>();
        blockBools->append(false);
        for (int i = 1; i < 9; ++i) {
            if (JSON_Management::GetJSONString("KW_B"+to_string(i),response).size() > 0 ){
                blockBools->append(true);
            }else{
                blockBools->append(false);
            }
        }
        for (int i = 0; i < blockBools->getLen(); ++i) {
            if(blockBools->get(i) == true){
                string title = JSON_Management::GetJSONString("KW_B" + to_string(i), response);
                ui->listWidget->addItem(QString::fromStdString(title));
            }
        }

    }
}

void ceSEARCH::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    auto bookMsg = new TypeMessage();
    bookMsg->setAppName("CESEARCH");
    bookMsg->setFileName(item->text().toStdString());
    bookMsg->setClientType("APP");
    string jsonMsg = JSON_Management::TypeMessageToJSON(bookMsg);
    Client::getInstance()->Send(jsonMsg.c_str());

    string response;
    while(response.empty()){
        response = Client::getInstance()->ReadString();
    }
    Client::getInstance()->setResponse("");
    auto huffmanMessage = new Huffman_Message();
    huffmanMessage = JSON_Management::DeserializetoHuffmanMessage(response);
    string msg = HuffmanCompression::Decode_Huffman(huffmanMessage->getCompress_Code(),huffmanMessage->getHuffman_Table());

    string text = JSON_Management::GetJSONString("Text",msg);
    for (int i = 0; i < text.length(); ++i) {
        char c = text[i];
        string output;
        if(c == ':'){
            ui->textEdit->append(output.c_str());
            output.clear();
        }else{
            output.push_back(c);
        }

    }
}
