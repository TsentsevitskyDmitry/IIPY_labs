#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pciregreader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QListWidget listWidget;

    PciRegReader reader;
    devices = reader.readAll();

    foreach (PciDevice dev, devices) {
        ui->pciList->insertItem(0, dev.getDeviceID());
    }
    ui->pciList->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}
