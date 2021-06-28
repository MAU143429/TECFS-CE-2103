#ifndef CESEARCH_H
#define CESEARCH_H

#include <QMainWindow>
#include <QListWidget>

namespace Ui {
class ceSEARCH;
}

class ceSEARCH : public QMainWindow
{
    Q_OBJECT

public:
    explicit ceSEARCH(QWidget *parent = nullptr);
    ~ceSEARCH();

private slots:
    void on_backBtn_clicked();

    void on_searchBtn_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::ceSEARCH *ui;
};

#endif // CESEARCH_H
