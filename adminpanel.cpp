#include "adminpanel.h"
#include "ui_adminpanel.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QDir>
#include <QFileDialog>
#include "imagesdirectory.h"

AdminPanel::AdminPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPanel)
{
    ui->setupUi(this);
    auto layout = new QHBoxLayout(this); // "layout" it not a QWidget itself, it only manages QWidgets
    this->setLayout(layout); // set "layout" as the layout manager for "widget"
    qDebug()<<"adminPanelSHowed";
}

AdminPanel::~AdminPanel()
{
    delete ui;
}

void AdminPanel::on_browseButton_clicked()
{
    QFileDialog dialog;
    dialog.setDirectory(QDir::current());
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setOption(QFileDialog::ShowDirsOnly, false);
    dialog.exec();

    //get the abs path and pass it to the image directory handler class
    QString absPath=dialog.directory().absolutePath();
    imageProperties.absPath=absPath;
    qDebug() << absPath;

    ui->DirectoryLabel->setText(absPath);
    ui->DirectoryLabel->setAlignment(Qt::AlignCenter);
    //TODO Align all to the center
}

void AdminPanel::on_pushButton_clicked()
{
    //push the values of coordinates 1 by one
    QVector<float>tempCooridnates;
    QLineEdit* lineEdits[]={ui->lineEdit, ui->lineEdit_2, ui->lineEdit_3, ui->lineEdit_4,
                           ui->lineEdit_9, ui->lineEdit_10, ui->lineEdit_11, ui->lineEdit_12,
                           ui->lineEdit_17, ui->lineEdit_18, ui->lineEdit_19, ui->lineEdit_20};
    try
    {
        tempCooridnates.clear();
        for (QLineEdit * i: lineEdits)
        {
            tempCooridnates.push_back(i->text().toFloat());
            //qDebug()<<i->text().toFloat();
        }
    }
    catch (...)
    {
        qDebug()<< "Error Getting Cooridinate Values";
    }
    imageProperties.cooridnates.clear();
    imageProperties.cooridnates=tempCooridnates;
    if(imageProperties.absPath!="")
    {
    ImagesDirectory::saveDirectory(imageProperties.absPath,imageProperties.cooridnates);
    }
    else{
        qDebug()<< "Void Path";
    }
}
