#ifndef PICTORESHRINKERCONTROLLER_H
#define PICTORESHRINKERCONTROLLER_H

#include <QObject>
#include <QString>
#include <QMutex>
#include <QFileInfo>
#include "pictureshrinker.h"

class PictoreShrinkerController : public QObject
{
    Q_OBJECT
public:
    explicit PictoreShrinkerController(QObject *parent = 0);
    ~PictoreShrinkerController();

signals:
    void error(QString string);
    void progress(int progress);

public slots:
    void startProcessing(void);
    void setPath(QString path);
    void setSavePath(QString path);
    void setScale(int widthPercent, int heightPercent);
    void processDone(void);

protected:
    QString _path;
    QString _savePath;
    int _widthPercent;
    int _heightPercent;

    int _actualPicture;
    int _pictures;
    QFileInfoList _list;
    QMutex *_mutex;
};

#endif // PICTORESHRINKERCONTROLLER_H
