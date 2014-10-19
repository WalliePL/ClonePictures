#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include "pictureshrinkerwidget.h"
#include "ui_pictureshrinkerwidget.h"

PictureShrinkerWidget::PictureShrinkerWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PictureShrinkerWidget)
{
    ui->setupUi(this);
    this->init();
}

PictureShrinkerWidget::~PictureShrinkerWidget()
{
    delete ui;
}

QString PictureShrinkerWidget::getPath(void)
{
    return this->_sourceLine->text();
}

QString PictureShrinkerWidget::getSavePath(void)
{
    return this->_destinationLine->text();
}

int PictureShrinkerWidget::getHeigh(void)
{
    return this->_heightValue->value();
}

int PictureShrinkerWidget::getWidth(void)
{
    return this->_widthValue->value();
}

void PictureShrinkerWidget::updateProgress(int progress)
{
    if (progress > 100)
    {
        qWarning() << __FILE__ << __LINE__ << "To big progress value";
        progress = 100;
    }

    if (progress < 0)
    {
        qWarning() << __FILE__ << __LINE__ << "To smal progress value";
        progress = 0;
    }

    this->_progressBar->setValue(progress);
}

void PictureShrinkerWidget::okButtonCliced(void)
{

    if (this->_pictureController == nullptr)
    {
        qWarning() << __FILE__ <<__LINE__ << "Missing controler object";
        return;
    }

    this->_pictureController->setPath(this->getPath());
    this->_pictureController->setSavePath(this->getSavePath());
    this->_pictureController->setScale(this->getWidth(), this->getHeigh());

    this->_pictureController->startProcessing();
}

void PictureShrinkerWidget::cancelCliced(void)
{
    qDebug() << __FILE__ << __LINE__ << "Cancel";
}

void PictureShrinkerWidget::browswerCliced(void)
{
    QObject *sender = this->sender();
    Q_ASSERT (sender);

    QPushButton *button = qobject_cast<QPushButton*>(sender);
    if (button == nullptr)
    {
        qWarning() << __FILE__ <<__LINE__ << "Bad sender";
        return;
    }

    QString dir = QFileDialog::getExistingDirectory(this, PictureShrinkerWidget::tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    if (button == this->_sourceButton)
    {
        this->setSourcePath(dir);
    }

    if (button == this->_destinationButton)
    {
        this->setDestinationPath(dir);
    }
}

void PictureShrinkerWidget::setSourcePath(QString path)
{
    this->_sourceLine->setText(path);
}

void PictureShrinkerWidget::setDestinationPath(QString path)
{
    this->_destinationLine->setText(path);
}

void PictureShrinkerWidget::error(QString string)
{
    QMessageBox::warning(this,
                         PictureShrinkerWidget::tr("Error in processing files"),
                         string,
                         QMessageBox::Ok
                         | QMessageBox::Cancel,
                         QMessageBox::Ok);
}

void PictureShrinkerWidget::init(void)
{
    this->_pictureController = new PictoreShrinkerController(this->ui->centralWidget);

    this->_layout = new QGridLayout(this->ui->centralWidget);
    this->_layout->setHorizontalSpacing(2);
    this->_layout->setVerticalSpacing(2);

    int row = 0;

    this->_sourceLabel = new QLabel(this);
    this->_sourceLabel->setText(PictureShrinkerWidget::tr("Source:"));
    this->_layout->addWidget(this->_sourceLabel, row, 0, 1, 1);

    this->_sourceLine = new QLineEdit(this);
    this->_layout->addWidget(this->_sourceLine, row, 1, 1, 1);

    this->_sourceButton = new QPushButton(this);
    this->_sourceButton->setText("...");
    this->_layout->addWidget(this->_sourceButton, row, 2, 1, 1);

    row++;

    this->_destinationLabel = new QLabel(this);
    this->_destinationLabel->setText(PictureShrinkerWidget::tr("Destination:"));
    this->_layout->addWidget(this->_destinationLabel, row, 0, 1, 1);

    this->_destinationLine = new QLineEdit(this);
    this->_layout->addWidget(this->_destinationLine, row, 1, 1, 1);

    this->_destinationButton = new QPushButton(this);
    this->_destinationButton->setText("...");
    this->_layout->addWidget(this->_destinationButton, row, 2, 1, 1);

    row++;

    this->_heightLabel = new QLabel(this);
    this->_heightLabel->setText(PictureShrinkerWidget::tr("Height:"));
    this->_layout->addWidget(this->_heightLabel, row, 0, 1, 1);

    this->_heightValue = new QSpinBox(this);
    this->_layout->addWidget(this->_heightValue, row, 1, 1, 1);
    this->_heightValue->setMaximum(1000);
    this->_heightValue->setMinimum(0);
    this->_heightValue->setValue(100);

    row++;

    this->_widthLabel = new QLabel(this);
    this->_widthLabel->setText(PictureShrinkerWidget::tr("Width:"));
    this->_layout->addWidget(this->_widthLabel, row, 0, 1, 1);

    this->_widthValue = new QSpinBox(this);
    this->_layout->addWidget(this->_widthValue, row, 1, 1, 1);
    this->_widthValue->setMaximum(1000);
    this->_widthValue->setMinimum(0);
    this->_widthValue->setValue(100);

    row++;

    this->_progressBar = new QProgressBar(this);
    this->_progressBar->setTextVisible(false);
    this->_layout->addWidget(this->_progressBar, row, 0, 1, 3);

    row++;

    this->_cancelButton = new QPushButton(this);
    this->_cancelButton->setText(PictureShrinkerWidget::tr("Cancel"));
    this->_layout->addWidget(this->_cancelButton, row, 0, 1, 2);

    this->_okButton = new QPushButton(this);
    this->_okButton->setText(PictureShrinkerWidget::tr("OK"));
    this->_layout->addWidget(this->_okButton, row, 2, 1, 1);

    this->createConnection();
}

void PictureShrinkerWidget::createConnection(void)
{
    this->connect(this->_cancelButton, SIGNAL(clicked()), this, SLOT(cancelCliced()), Qt::UniqueConnection);

    this->connect(this->_okButton, SIGNAL(clicked()), this, SLOT(okButtonCliced()), Qt::UniqueConnection);

    this->connect(this->_sourceButton, SIGNAL(clicked()), this, SLOT(browswerCliced()), Qt::UniqueConnection);
    this->connect(this->_destinationButton, SIGNAL(clicked()), this, SLOT(browswerCliced()), Qt::UniqueConnection);

    this->connect(this->_pictureController, SIGNAL(progress(int)), this, SLOT(updateProgress(int)), Qt::UniqueConnection);
    this->connect(this->_pictureController, SIGNAL(done()), this, SLOT(done()), Qt::UniqueConnection);


}
