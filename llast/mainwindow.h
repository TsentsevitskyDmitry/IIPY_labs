#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Service/USBService.h"
#include "Service/DriveService.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    USBService usbService;
    DriveService driveService;

    QThread usbServiceThread;
    QThread driveServiceThread;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateUSBInfo();
    void updateDriveInfo();

private slots:
    void on_updateButton_clicked();
    void on_ejectButton_clicked();
};

#endif // MAINWINDOW_H
