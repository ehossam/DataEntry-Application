#include "user.h"
#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QAbstractButton>
#include <QApplication>
#include <QObject>
#include <QPushButton>

QString User::username="";
QString User::password="";
QString User::firstName="";
QString User::lastName="";
QString User::emailAddress="";
double User::sessionTime=0;
int User::numOfImages=0;
int User::numOfInputChars=0;
QElapsedTimer User::timer;

using namespace std;

User::User(){}

bool User::verifyUser(QString username, QString password, bool isAdmin)
{
    QSqlDatabase * db= DataBaseManager::getDbInstance();
    QString querySyntax="";
    if(isAdmin)
    {
        //compare passwords
        querySyntax= QString("SELECT password FROM Admins WHERE username = \""+username+ "\"");
    }
    else
    {
        querySyntax= QString("SELECT password FROM Users WHERE username = \""+username+ "\"");
    }
    QSqlQuery query(*db);
    query.exec(querySyntax);
    QString resQuery="";

    if(query.first())
    {
        resQuery= query.value(0).toString();
        //qDebug()<< resQuery;
    }
    else
    {
        qDebug()<< "cannot Access users/admins table";
    }
    if(resQuery.compare(password)==0 &&resQuery!="")
    {
        if(!isAdmin)
        {
            //login and get results
            querySyntax= QString("SELECT * FROM Users WHERE username = \""+username+ "\"");
            QSqlQuery query(*db);
            query.exec(querySyntax);
            if(query.first())
            {
                User::username=query.value(0).toString();
                User::password=query.value(1).toString();
                User::firstName=query.value(2).toString();
                User::lastName=query.value(3).toString();
                User::emailAddress=query.value(4).toString();
            }


            timer.start();//session time
        }
        return 1;
    }
    else return 0;
}

void User::registerNewUser(QString username, QString password, QString firstName, QString lastName, QString emailAddress)
{
    QSqlDatabase * db= DataBaseManager::getDbInstance();
    QSqlQuery query(*db);

    //make sure it is not already registred
    QString querySyntax= QString("SELECT * FROM Users WHERE username = \""+username+ "\"");
    query.exec(querySyntax);
    int countQuery=0;
    while(query.next()) countQuery++;
    qDebug()<<countQuery;

    if(!countQuery)
    {
        User::username= username;
        User::password= password;
        User::firstName= firstName;
        User::lastName=lastName;
        User::emailAddress=emailAddress;
        QString querySyntax=QString("INSERT INTO Users (username,password,first_name,last_name,email_address) VALUES(\""+
                                    username+"\",\""+password+"\",\""+firstName+"\",\""+lastName+"\",\""+emailAddress+"\")");
        //qDebug()<<querySyntax;
        query.exec(querySyntax);
        qDebug()<< query.lastError();
        qDebug()<<"registered new user";
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Existing User");
        msgBox.setText("User Already Exits!\nPlease try Signing In");
        msgBox.exec();
    }
}

void User::incrementChars(int numChars)
{
    User::numOfInputChars+=numChars;
    User::numOfImages++;
}

void User::logOut()
{
    sessionTime=timer.elapsed()/1000;
    QString summaryText= "Username:  "+User::username+
              "\nFirstName:  "+User::firstName+
              "\nLastName:  "+User::lastName+
              "\nEmailAddress:  "+User::emailAddress+
              "\nSession Time in seconds:  "+QString::number( User::sessionTime)+
              "\nNumOfChars:  "+QString::number(User::numOfInputChars)+
              "\nNumOfImages:  "+QString::number(User::numOfImages);

    QMessageBox msgBox;
    msgBox.setWindowTitle("Session Summary");
    msgBox.setText(summaryText);

    QAbstractButton *confirmButton = msgBox.addButton(QObject::tr("Confirm Logout"), QMessageBox::YesRole);
    msgBox.addButton(QObject::tr("Get Back"), QMessageBox::NoRole);


    msgBox.exec();
    if(msgBox.clickedButton()== confirmButton)
    {
       qApp->exit();
    }

}
