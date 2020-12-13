#ifndef USERPANEL_H
#define USERPANEL_H

#include <QWidget>

namespace Ui {
class UserPanel;
}

class UserPanel : public QWidget
{
    Q_OBJECT

public:
    explicit UserPanel(QWidget *parent = 0);
    ~UserPanel();

private slots:

    void on_pushButton_2_clicked();
    void on_lineEdit_3_returnPressed();

    void on_lineEdit_3_editingFinished();

private:
    Ui::UserPanel *ui;
    void loadImage();
    void editEnded();
};

#endif // USERPANEL_H
