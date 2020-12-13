#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <adminpanel.h>
#include <memory>
#include<QDebug>
#include <userpanel.h>
#include <user.h>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_7->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_signInButton_clicked()
{
    //User Login

    //first check the credintials
    if(User::verifyUser(ui->lineEdit->text(),ui->lineEdit_2->text(),false))
    {
        qDebug()<<"Credentials Match";
        static unique_ptr<QWidget> userPanel = make_unique<UserPanel>();
        userPanel->show();
        userPanel->activateWindow();
        userPanel->raise();
        this->hide();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid Login");
        msgBox.setText("The username and Password don't match.\nPlease Register first or make sure username/password match");
        msgBox.exec();
    }

}

void MainWindow::on_pushButton_clicked()
{
    //admin Login
    if(User::verifyUser(ui->lineEdit->text(),ui->lineEdit_2->text(),true))
    {
        //the sign in button will get to the admin or user dpending on the type
        static unique_ptr<QWidget> adminPanel = make_unique<AdminPanel>();
        adminPanel->show();
        adminPanel->activateWindow();
        adminPanel->raise();
        this->hide();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid Login");
        msgBox.setText("The username and Password don't match.\nIf you're not admin please login as a user and make sure username/password match");
        msgBox.exec();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    //Before registering the user make sure username and pass follow the guildlines
    int i;
    bool flag_upper =false;
    bool flag_lower=false;
    bool flag_num= false;

    bool flag_specialOrSpace= false;

    for(i='A'; i<='Z'; i++)
    {
        if (ui->lineEdit_7->text().contains(char(i)))
                flag_upper=true;
    }
    for(i='a'; i<='z'; i++)
    {
        if (ui->lineEdit_7->text().contains(char(i)))
                flag_lower=true;
    }
    for(i='0'; i<='9'; i++)
    {
        if (ui->lineEdit_7->text().contains(char(i)))
                flag_num=true;
    }

    qDebug()<< flag_lower<<flag_upper<< flag_num;
    for (i=0;i<=47;i++)
    {
        if (ui->lineEdit_6->text().contains(char(i)))
            flag_specialOrSpace=true;
    }

    for (i=58;i<=64;i++)
    {
        if (ui->lineEdit_6->text().contains(char(i)))
            flag_specialOrSpace=true;
    }


    for(i=123;i<=255;i++)
    {
        if (ui->lineEdit_6->text().contains(char(i)))
            flag_specialOrSpace=true;
    }

    if(flag_lower && flag_num && flag_upper&& !flag_specialOrSpace){
        User::registerNewUser(ui->lineEdit_6->text(), ui->lineEdit_7->text(),
                              ui->lineEdit_3->text(),ui->lineEdit_4->text(),
                              ui->lineEdit_5->text());
    }
    else if(flag_specialOrSpace)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid Username");
        msgBox.setText("The Username must not contain any special characters or space");
        msgBox.exec();
       }
        else
        {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Invalid Password");
        msgBox.setText("The Password must contain at least 1 uppercase letter, 1 Lower case letter and 1 number");
        msgBox.exec();
        }


}
