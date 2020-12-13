#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QSignalMapper>
#include <QPushButton>
#include <QObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_signInButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    void openAdminPanel();
//    QSignalMapper *signalMapper;
//    QPushButton *signInButton;
};

#endif // MAINWINDOW_H
