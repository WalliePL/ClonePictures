#ifndef PICTURESHRINKER_H
#define PICTURESHRINKER_H

#include <QThread>
#include <QString>

class PictureShrinker : public QThread
{
    Q_OBJECT
public:
    explicit PictureShrinker(QObject *parent = 0);
    void setPath(QString path);
    void setSavePath(QString path);
    void setScale(int widthPercent, int heightPercent);


signals:
    void error(QString errorText);
    void pictureScaled(void);

public slots:

protected:
    virtual void run();

protected:
    QString _path;
    QString _savePath;
    int _widthPercent;
    int _heightPercent;
};

#endif // PICTURESHRINKER_H
