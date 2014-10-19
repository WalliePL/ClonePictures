#ifndef PICTURESHRINKERWIDGET_H
#define PICTURESHRINKERWIDGET_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QProgressBar>
#include "pictoreshrinkercontroller.h"

namespace Ui {
class PictureShrinkerWidget;
}

class PictureShrinkerWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit PictureShrinkerWidget(QWidget *parent = 0);
    ~PictureShrinkerWidget();

    QString getPath(void);
    QString getSavePath(void);
    int getHeigh(void);
    int getWidth(void);

signals:

public slots:
    void updateProgress(int progress);
    void okButtonCliced(void);
    void cancelCliced(void);
    void browswerCliced(void);
    void setSourcePath(QString path);
    void setDestinationPath(QString path);
    void error(QString string);

private:
    void init(void);
    void createConnection(void);

private:
    Ui::PictureShrinkerWidget *ui;
    QGridLayout *_layout;

    QLabel *_sourceLabel;
    QLineEdit *_sourceLine;
    QPushButton *_sourceButton;

    QLabel *_destinationLabel;
    QLineEdit *_destinationLine;
    QPushButton *_destinationButton;

    QLabel *_widthLabel;
    QSpinBox *_widthValue;
    QLabel *_heightLabel;
    QSpinBox *_heightValue;

    QProgressBar *_progressBar;

    QPushButton *_okButton;
    QPushButton *_cancelButton;
    PictoreShrinkerController *_pictureController;
};

#endif // PICTURESHRINKERWIDGET_H
