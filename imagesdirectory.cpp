#include "imagesdirectory.h"
#include <memory>
#include <QSqlDatabase>
#include <databasemanager.h>
#include <QSqlQuery>
#include <QDir>
#include <QStringList>
#include <QDebug>
#include <QSqlError>
#include <QPixmap>
#include <QRect>

using namespace std;

QString ImagesDirectory::dirPath="";
QString ImagesDirectory::currImagePath="";


void ImagesDirectory::saveDirectory(QString dirPath, QVector<float> coordinates)
{
    QSqlDatabase * db= DataBaseManager::getDbInstance();
    ImagesDirectory::dirPath=dirPath;
    QString querySyntax= QString("UPDATE ImagesProperties SET path = \""+dirPath+ "\"");

    int countCordinates=0;
    QString num_i[]={"1","2","3"};
    for (QString i: num_i)
    {
            //qDebug()<<QString::number(coordinates[countCordinates]);
            querySyntax+=QString(", i"+i+"_x1 = "+QString::number(coordinates[countCordinates])+
                                 ", i"+i+"_x2 = "+QString::number(coordinates[countCordinates+1])+
                                 ", i"+i+"_y1 = "+QString::number(coordinates[countCordinates+2])+
                                 ", i"+i+"_y2 = "+QString::number(coordinates[countCordinates+3]));
            countCordinates+=4;
    }
    querySyntax+=QString(" LIMIT 1");
    QSqlQuery query(*db);
    query.exec(querySyntax);
    //qDebug()<<query.lastError();
    qDebug()<<"ImagesProperties Table Updated with errors:: "<< query.lastError();
}


QVector<QImage> ImagesDirectory::loadImage()
{
    QSqlDatabase * db= DataBaseManager::getDbInstance();
    QString querySyntax= QString("SELECT * FROM ImagesProperties LIMIT 1");
    QSqlQuery query(*db);
    query.exec(querySyntax);
    QString resQuery="";
    QVector<float> coordinates;


    //get the images location
    if(query.first())
    {
        resQuery= query.value(0).toString();
        qDebug()<< resQuery;
        coordinates.clear();
        for(int i=1; i<=12;i++) coordinates.push_back(query.value(i).toFloat());
    }
    else
    {
        qDebug()<< "cannot get Images Location or Coordinates";
    }

    dirPath=resQuery;
    QDir directory(dirPath);
    QStringList images = directory.entryList(QStringList() << "*.pdf" << "*.PDF",QDir::Files);
    QString filenamePath="";

    //get the processed images from the DB
    querySyntax=QString("SELECT imagePath FROM ProcessedImages");
    query.exec(querySyntax);

    QStringList processedImages;
    while (query.next())
    {
        //qDebug()<< query.value(0).toString();
        processedImages.append(query.value(0).toString());
    }


    //get the inProcess images from the DB (being processed by other Users)
    querySyntax=QString("SELECT imagePath FROM InProcessImages");
    query.exec(querySyntax);

    QStringList inProcessImages;
    while (query.next())
    {
        //qDebug()<< query.value(0).toString();
        inProcessImages.append(query.value(0).toString());
    }

    QVector<QImage> unprocImages;
    QVector<QImage> croppedImages;

    //check for unprocessed images
    for (auto filename: images)
    {
        filenamePath=QString(dirPath+"/"+filename);
        //qDebug()<< filenamePath;
        if(! (processedImages.contains(filenamePath) || inProcessImages.contains(filenamePath)))
        {
            qDebug()<< filenamePath;
            unprocImages.clear();
            //load the pdf document
            Poppler::Document* document = Poppler::Document::load(filenamePath);
            if (!document || document->isLocked()) {
              // ... error message ....
              qDebug()<<QString("Error Loading the unrprocessed file ") << filenamePath;
              delete document;
              break;
            }

            for(int i=0;i<=1;i++)
            {
            // Access page 0 of the PDF file
            //qDebug()<<QString("Getting Page 1 ") <<filenamePath;
            Poppler::Page* pdfPage = document->page(i);  // Document starts at page 0
            if (pdfPage == 0) {
              // ... error message ...
              break;
            }

            // Generate a QImage of the rendered page
            QImage image = pdfPage->renderToImage();
            if (image.isNull()) {
              // ... error message ...
              break;
            }

            // ... use image ...
            unprocImages.push_back(image);
            // after the usage, the page must be deleted
            delete pdfPage;
        }
           currImagePath=filenamePath;
            break;
        }
    }

    croppedImages.clear();
    int coordCount=0;
    if(unprocImages.length()==2)
    {
        for (int i=0;i<=2;i++)
        {
            //get the coordinates with the length
            float x= (coordinates[coordCount]<=coordinates[coordCount+1]) ? coordinates[coordCount] : coordinates[coordCount+1];
            float y= (coordinates[coordCount+2]<=coordinates[coordCount+3]) ? coordinates[coordCount+2] : coordinates[coordCount+3];
            float w= abs(coordinates[coordCount]- coordinates[coordCount+1]);
            float h= abs(coordinates[coordCount+2]- coordinates[coordCount+3]);
            QRect rect(x, y, w, h);
            QPixmap original;
            original.convertFromImage(unprocImages[i/2]);
            QPixmap cropped = original.copy(rect);
            QImage toPush= cropped.toImage();
            croppedImages.push_back(toPush);
            coordCount+=4;
        }
    }
    //being processed image
    querySyntax =QString("INSERT INTO InProcessImages VALUES (\""+filenamePath+"\")");
    query.exec(querySyntax);
    return croppedImages;
}

void ImagesDirectory::saveProcessedImage(QString i1, QString i2, QString i3)
{
    QSqlDatabase * db= DataBaseManager::getDbInstance();
    ImagesDirectory::dirPath=dirPath;
    QString querySyntax= QString("INSERT INTO ProcessedImages VALUES (\""+currImagePath+ "\",\""
                                 +i1+"\",\""+i2+"\",\""+i3+"\" )");
    QSqlQuery query(*db);
    query.exec(querySyntax);
    qDebug()<<query.lastError();

    //remove the image from the inprocess images
    querySyntax= QString("DELETE FROM InProcessImages WHERE imagePath=\""+currImagePath+"\"");
    query.exec(querySyntax);
    qDebug()<<query.lastError();

}
