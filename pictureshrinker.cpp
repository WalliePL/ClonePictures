#include <QFileInfo>
#include <QDebug>
#include <QImage>
#include <QDir>
#include "pictureshrinker.h"

PictureShrinker::PictureShrinker(QObject *parent) :
    QThread(parent)
{
}

void PictureShrinker::setPath(QString path)
{
    if (this->_path != path)
    {
        this->_path = path;
    }
}

void PictureShrinker::setSavePath(QString path)
{
    if (this->_savePath != path)
    {
        this->_savePath = path;
    }
}

void PictureShrinker::setScale(int widthPercent, int heightPercent)
{
    if (this->_widthPercent != widthPercent)
    {
        this->_widthPercent = widthPercent;
    }

    if (this->_heightPercent != heightPercent)
    {
        this->_heightPercent = heightPercent;
    }
}

void PictureShrinker::run()
{
    if (this->_path.isEmpty())
    {
        emit this->error(PictureShrinker::tr("Missing path to file"));
        return;
    }

    if (this->_savePath.isEmpty())
    {
        emit this->error(PictureShrinker::tr("Missing save path"));
        return;
    }

    if (this->_widthPercent < 0)
    {
        emit this->error(PictureShrinker::tr("Bad width"));
        return;
    }

    if (this->_heightPercent < 0)
    {
        emit this->error(PictureShrinker::tr("Bad height"));
        return;
    }

    QImage *image = new QImage(this->_path);
    QImage newImage = image->scaled(float(this->_widthPercent)/100.0 * image->width(), float(this->_heightPercent)/100.0 * image->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QString pathToSave = QDir::toNativeSeparators(this->_savePath + QDir::separator() + QFileInfo(this->_path).fileName());

    qDebug() << __FILE__ << __LINE__ << "save to :" << pathToSave;
    newImage.save(pathToSave);

    delete image;
}
