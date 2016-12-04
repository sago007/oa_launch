/*
===========================================================================
oa_launch
Copyright (C) 2016 Poul Sander

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/

Source information and contacts persons can be found at
https://github.com/sago007/oa_launch
===========================================================================
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OpenArenaLaunchh.h"

extern OpenArenaLaunch oal;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString labelText("This requires that the following executable exists: ");
    labelText += QString(oal.openarena_path_bin.c_str());
    labelText += " or it will just crash";
    ui->labelPathToBin->setText(labelText);
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
    ui->profileDirEdit->setText(QString(oal.getProfileDir().c_str()));
    ui->modNameEdit->setText(QString(oal.getModName().c_str()));
}
