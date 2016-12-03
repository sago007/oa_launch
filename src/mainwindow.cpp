#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OpenArenaLaunchh.h"

extern OpenArenaLaunch oal;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int returnCode = oal.Launch();
    if (returnCode) {
        statusBar()->showMessage("Already running",5000);
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    oal.setProfile(index);
}
