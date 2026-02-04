#include "Downloader.hpp"
#include <QRegularExpression>
#include <QDebug>

Downloader::Downloader(QObject *in_parent) : QObject(in_parent)
{
    _process = new QProcess(this);

    connect(_process, &QProcess::readyReadStandardOutput, this, &Downloader::handleReadyRead);
    connect(_process, &QProcess::finished, this, &Downloader::handleProcessFinished);
}

Downloader::~Downloader()
{
    if(!_process)
        return;

    if(_process->state() != QProcess::Running)
        return;

    _process->terminate();
    _process->waitForFinished(3000);
}

void Downloader::startDownload(const QString &in_url)
{
    if(in_url.isEmpty())
        return;

    if(!_process)
        return;

    if(_process->state() != QProcess::NotRunning)
        return;

    QStringList arguments;
    arguments << "--newline" << "--progress" << in_url;

    emit statusChanged("Preparing to download");

    _process->start("yt-dlp", arguments);
    if(!_process->waitForStarted())
    {
        emit downloadFinished(false, "Failed to start yt-dlp. Make sure it's installed and present in the PATH");
        emit statusChanged("Launch error");
    }
}

void Downloader::handleReadyRead()
{
    if(!_process)
        return;

    QString output = _process->readAllStandardOutput();

    static QRegularExpression re("\\[download\\]\\s+([\\d\\.]+)%");
    QRegularExpressionMatch match = re.match(output);
    if(match.hasMatch() && match.capturedLength() > 2)
    {
        QString progerss_str = match.captured(1);
        double progress_value = progerss_str.toDouble();

        emit progressChanged(static_cast<int>(progress_value));
        emit statusChanged(QString("Downloading: %1%").arg(progerss_str));
    }
}

void Downloader::handleProcessFinished(int in_exit_code)
{
    if(in_exit_code == 0)
    {
        emit progressChanged(100);
        emit downloadFinished(true, "Saved successfully");
        emit statusChanged("Ready");
    }
    else
    {
        QString error_output = _process->readAllStandardError();
        emit downloadFinished(false, "Downloading error. Code: " + QString::number(in_exit_code));
        emit statusChanged("Error");
        qDebug() << "yt-dlp error: " << error_output;
    }
}
