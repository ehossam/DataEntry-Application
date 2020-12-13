#ifndef IMAGESDIRECTORY_H
#define IMAGESDIRECTORY_H
#include <QString>
#include <poppler-qt5.h>
#include <QVector>
#include <QImage>


class ImagesDirectory
{
    static QString dirPath;
    static QString currImagePath;
public:
    static void saveDirectory(QString dirPath, QVector<float> coordinates);
    static QVector<QImage> loadImage();
    static QVector<float> getCoorinates();
    static void saveProcessedImage(QString, QString, QString);
};

#endif // IMAGESDIRECTORY_H
