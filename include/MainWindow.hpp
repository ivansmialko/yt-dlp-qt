#pragma once
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include "Downloader.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* in_parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onDownloadClicked();
    void showFinishedMessage(bool in_success, const QString& in_message);

private:
    Downloader* _downloader;

    QLineEdit* _url_edit;
    QPushButton* _download_button;
    QProgressBar* _progress_bar;
    QLabel* _status_label;
};
