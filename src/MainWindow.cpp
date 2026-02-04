#include "MainWindow.hpp"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *in_parent) : QMainWindow(in_parent)
{
    setWindowTitle("yt-dlp-qt");
    setMinimumWidth(500);

    _url_edit = new QLineEdit(this);
    _url_edit->setPlaceholderText("Enter YouTube video link..");

    _download_button = new QPushButton("Download", this);

    _progress_bar = new QProgressBar(this);
    _progress_bar->setRange(0, 100);
    _progress_bar->setValue(0);

    _status_label = new QLabel("Ready", this);
    _status_label->setAlignment(Qt::AlignCenter);

    QWidget* central_widget = new QWidget(this);
    setCentralWidget(central_widget);

    QVBoxLayout* layout = new QVBoxLayout(central_widget);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->addWidget(new QLabel("Link:", this));

    layout->addWidget(_url_edit);
    layout->addWidget(_progress_bar);
    layout->addWidget(_status_label);
    layout->addWidget(_download_button);

    _downloader = new Downloader(this);

    connect(_download_button, &QPushButton::clicked, this, &MainWindow::onDownloadClicked);
    connect(_downloader, &Downloader::progressChanged, _progress_bar, &QProgressBar::setValue);
    connect(_downloader, &Downloader::statusChanged, _status_label, &QLabel::setText);
    connect(_downloader, &Downloader::downloadFinished, this, &MainWindow::showFinishedMessage);
}

void MainWindow::onDownloadClicked()
{
    QString url = _url_edit->text().trimmed();
    if(url.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Please, enter link");
        return;
    }

    _download_button->setEnabled(false);
    _progress_bar->setValue(0);
    _downloader->startDownload(url);
}

void MainWindow::showFinishedMessage(bool in_success, const QString &in_message)
{
    _download_button->setEnabled(true);
    if(in_success)
    {
        QMessageBox::information(this, "Success!", in_message);
    }
    {
        QMessageBox::critical(this, "Eror", in_message);
    }
}
