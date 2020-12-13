#include "userpanel.h"
#include "ui_userpanel.h"
#include <imagesdirectory.h>
#include <QImage>
#include <QVector>
#include <QDebug>
#include <QRect>
#include <QPixmap>
#include <user.h>
#include <QMessageBox>
#include <databasemanager.h>

UserPanel::UserPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserPanel)
{
    ui->setupUi(this);
    loadImage();
}

UserPanel::~UserPanel()
{
    delete ui;
}

void UserPanel::loadImage()
{
    //get the image and make sure it is correct
    try
    {
        QVector<QImage> imageToShow;
        qDebug()<< QString("loading images");
        imageToShow=ImagesDirectory::loadImage();
        if(imageToShow.length()==3)
        {
        QLabel * imagesLabels[] ={ui->label, ui->label_2, ui->label_3};
        int iter=0;
        for(QImage i : imageToShow)
        {
            QImage image1= i.scaled(imagesLabels[iter]->width(), imagesLabels[iter]->height(), Qt::IgnoreAspectRatio);
            imagesLabels[iter]->setPixmap(QPixmap::fromImage(image1));
            iter++;
        }
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle("No Images To show");
            msgBox.setText("All Images Are Processed");
            msgBox.exec();
        }
    }
    catch(...)
    {

    }
}


void UserPanel::on_pushButton_2_clicked()
{
    //logout
    User::logOut();
}


void UserPanel::on_lineEdit_3_returnPressed()
{
  editEnded();
}

void UserPanel::on_lineEdit_3_editingFinished()
{
  editEnded();
}

void UserPanel::editEnded()
{
    QString lineText=ui->lineEdit->text();
    QString lineText_2=ui->lineEdit_2->text();
    QString lineText_3=ui->lineEdit_3->text();

    //log out user and show the session history
    if(lineText!=""&&lineText_2!=""&&lineText_3!="")
    {
        int numOfChars= lineText.length()+
                lineText_2.length()+
                lineText_3.length();
        User::incrementChars(numOfChars);

        ImagesDirectory::saveProcessedImage(lineText,lineText_2,lineText_3);

        loadImage(); //load next image

    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Null Data");
        msgBox.setText("Please Enter Valid Data First");
        msgBox.exec();
        return;
    }
}
