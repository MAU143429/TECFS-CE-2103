#ifndef CEROBOT_H
#define CEROBOT_H

#include <QMainWindow>

namespace Ui {
class ceROBOT;
}

class ceROBOT : public QMainWindow
{
    Q_OBJECT

public:
    explicit ceROBOT(QWidget *parent = nullptr);
    ~ceROBOT();

private slots:
    void on_uploadBtn_clicked();

    void on_pushBtn_clicked();

    void on_backBtn_clicked();

private:
    Ui::ceROBOT *ui;
};

#endif // CEROBOT_H
