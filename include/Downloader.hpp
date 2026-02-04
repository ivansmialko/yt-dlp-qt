#pragma once
#include <QObject>
#include <QProcess>
#include <QString>

class Downloader : public QObject
{
    Q_OBJECT

public:
    explicit Downloader(QObject* in_parent = nullptr);
    ~Downloader();

    void startDownload(const QString& in_url);

signals:
    void progressChanged(int in_percentage);
    void statusChanged(const QString& in_status);
    void downloadFinished(bool in_success, const QString& in_message);

private slots:
    void handleReadyRead();
    void handleProcessFinished(int in_exit_code);

private:
    QProcess* _process;

};