#ifndef ADMINPANEL_H
#define ADMINPANEL_H

#include <QWidget>
#include <QString>
#include <QVector>
#include <QLineEdit>

namespace Ui {
class AdminPanel;
}

class AdminPanel : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanel(QWidget *parent = 0);
    ~AdminPanel();

private slots:
    void on_browseButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::AdminPanel *ui;
    struct ImageProperties
    {
      QString absPath;
      QVector<float> cooridnates;
    };
    ImageProperties imageProperties;
};

#endif // ADMINPANEL_H
