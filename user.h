#ifndef USER_H
#define USER_H

#include <QString>
#include <memory>
#include <QElapsedTimer>

class User
{
    User();
    static QString username, password, firstName, lastName, emailAddress;
    static double sessionTime;
    static int numOfImages, numOfInputChars;
    static QElapsedTimer timer;

public:
    static bool verifyUser(QString username, QString password, bool isAdmin);
    static void registerNewUser(QString username, QString password, QString firstName,QString lastName,  QString emailAddress);
    static User* getUserInstance();
    static void incrementChars(int);
    static void logOut();
};

#endif // USER_H
