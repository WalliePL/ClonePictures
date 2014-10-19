#include "pictoreshrinkercontroller.h"
#include <QDir>
#include <QDebug>
#include <QMutexLocker>

PictoreShrinkerController::PictoreShrinkerController(QObject *parent) :
    QObject(parent),
    _path(QString()),
    _savePath(QString()),
    _widthPercent(100),
    _heightPercent(100),

    _actualPicture(0),
    _pictures(0),
    _list(QFileInfoList())
{
    this->_mutex = new QMutex();
}

PictoreShrinkerController::~PictoreShrinkerController()
{

}

void PictoreShrinkerController::startProcessing(void)
{
    if (this->_path.isEmpty())
    {
        emit this->error(PictoreShrinkerController::tr("Missing path to file"));
        return;
    }

    if (this->_savePath.isEmpty())
    {
        emit this->error(PictoreShrinkerController::tr("Missing save path"));
        return;
    }

    if (this->_widthPercent < 0)
    {
        emit this->error(PictoreShrinkerController::tr("Bad width"));
        return;
    }

    if (this->_heightPercent < 0)
    {
        emit this->error(PictoreShrinkerController::tr("Bad height"));
        return;
    }

    this->_actualPicture = 0;
    QDir dir(this->_path);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);

    this->_list = dir.entryInfoList();
    this->_pictures = this->_list.size();
    int startAmount = this->_pictures;
    int i = 0;
    if (this->_pictures > 10)
    {
        startAmount = 10;
    }

    for (i = 0; i < startAmount; ++i)
    {
        QFileInfo fileInfo =  this->_list.at(this->_actualPicture);

        PictureShrinker *shrinkThread = new PictureShrinker();
        Q_ASSERT (shrinkThread);
        shrinkThread->setPath(QDir::toNativeSeparators(this->_path + QDir::separator() + fileInfo.fileName()));
        shrinkThread->setSavePath(this->_savePath);
        shrinkThread->setScale(this->_widthPercent, this->_heightPercent);

        this->connect(shrinkThread, SIGNAL(finished()), this, SLOT(processDone()), Qt::QueuedConnection);

        this->_actualPicture++;
        shrinkThread->start();
    }
}

void PictoreShrinkerController::setPath(QString path)
{
    if (this->_path != path)
    {
        this->_path = path;
    }
}

void PictoreShrinkerController::setSavePath(QString path)
{
    if (this->_savePath != path)
    {
        this->_savePath = path;
    }
}

void PictoreShrinkerController::setScale(int widthPercent, int heightPercent)
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

void PictoreShrinkerController::processDone(void)
{
    PictureShrinker *shrinkedThread = qobject_cast<PictureShrinker *>(this->sender());
    Q_ASSERT (shrinkedThread);

    shrinkedThread->deleteLater();

    emit this->progress((float(this->_actualPicture) / float(this->_pictures)) * 100);

    if (this->_actualPicture < this->_pictures)
    {
        QFileInfo fileInfo =  this->_list.at(this->_actualPicture);

        PictureShrinker *shrinkThread = new PictureShrinker();
        Q_ASSERT (shrinkThread);
        shrinkThread->setPath(QDir::toNativeSeparators(this->_path + QDir::separator() + fileInfo.fileName()));
        shrinkThread->setSavePath(this->_savePath);
        shrinkThread->setScale(this->_widthPercent, this->_heightPercent);

        this->connect(shrinkThread, SIGNAL(finished()), this, SLOT(processDone()), Qt::QueuedConnection);

        this->_actualPicture++;
        shrinkThread->start();
    }
}
