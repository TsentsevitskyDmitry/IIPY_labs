#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <windows.h>
#include <iostream>
#include <QThread>
#include "updater.h"

using namespace std;
#define BITMASK_LEN 24
#define BUFF_SIZE 1024


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void updateInfo();
private:
    Ui::MainWindow *ui;
    int getDiskCount();
    void showHardInfo(UINT nDriveNumber);
    void showSizeInfo(UINT nDriveNumber);
    void showPartInfo(UINT nDriveNumber);

    int currentIndex;
    Updater* updater;
signals:
    void closeUpdater();
};

#endif // MAINWINDOW_H
