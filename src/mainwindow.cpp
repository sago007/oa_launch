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
#include "OpenArenaLaunch.h"
#include "QDebug"
#include "QProcess"
#include <QPixmap>
#include "OpenArenaLaunch.h"

extern OpenArenaLaunch oal;


void MainWindow::RefreshModList() {
	std::size_t i = ui->profilesListWidget->currentRow();
	ui->profilesListWidget->clear();
	for (const OaProfile& p : oal.config.profiles) {
		ui->profilesListWidget->addItem(QString(p.profileName.c_str()));
	}
	ui->profilesListWidget->setCurrentRow(i);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString labelText("This requires that the following executable exists: ");
    labelText += QString(oal.openarena_path_bin.c_str());
    labelText += " or it will just crash";
    ui->labelPathToBin->setText(labelText);
	RefreshModList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

static QProcess* process = nullptr;

static int Launch() {
    //All these QProcess things should be moved out from OpenArenaLauncher so nothing needs QT
    if (!process) {
        process = new QProcess();
    }
    if (process->pid()) {
        return 1;
    }
    qDebug() << "Launching profile: " << oal.getProfile() << ", with: " << oal.openarena_path_bin.c_str();
    QStringList finalArguments;
    const auto& arguments = oal.getArguments();
    for (const std::string& value : arguments) {
        finalArguments.push_back(QString::fromUtf8(value.c_str()));
    }
    process->start(oal.openarena_path_bin.c_str(), finalArguments);
    bool started_success = process->waitForStarted();
    if (!started_success) {
        return 1;
    }
    return 0;
}

void MainWindow::on_pushButton_clicked()
{
    int returnCode = Launch();
    if (returnCode) {
        ui->statusBar->showMessage("Failed to start",5000);
    }
}

void MainWindow::on_profilesListWidget_currentItemChanged(QListWidgetItem*, QListWidgetItem*)
{
    std::size_t index = ui->profilesListWidget->currentRow();
    oal.setProfile(index);
	ui->profileDirFull->setText(to_qstring(oal.getProfileDir()));
	ui->profileDirEdit->setText(to_qstring(oal.activeProfile.homepath));
	ui->modNameEdit->setText(to_qstring(oal.getModName()));
	ui->profileNameEdit->setText(to_qstring(oal.activeProfile.profileName));
}

void MainWindow::on_saveButton_clicked()
{
	oal.activeProfile.modName = to_string(ui->modNameEdit->text());
	oal.activeProfile.homepath = to_string(ui->profileDirEdit->text());
	oal.activeProfile.profileName = to_string(ui->profileNameEdit->text());
    try {
        size_t index = oal.SaveProfile(oal.activeProfile);
        RefreshModList();
        ui->profilesListWidget->setCurrentRow(index);
    } catch (std::exception& e) {
        ui->statusBar->showMessage(e.what(),50000);
    }
}

void MainWindow::on_deleteButton_clicked()
{
    ui->statusBar->showMessage("", 0);
    size_t index = ui->profilesListWidget->currentRow(); // oal.SaveProfile(oal.activeProfile);
    try {
        oal.RemoveProfile(index);
    } catch (std::exception& e) {
        ui->statusBar->showMessage(e.what(),50000);
    }

    RefreshModList();
    ui->profilesListWidget->setCurrentRow(index);
}

void MainWindow::on_pushButtonUp_clicked()
{
    try {
        size_t index = ui->profilesListWidget->currentRow();
        size_t new_index = oal.ProfileMoveUp(index);
        RefreshModList();
        ui->profilesListWidget->setCurrentRow(new_index);
    } catch (std::exception& e) {
        ui->statusBar->showMessage(e.what(),50000);
    }
}

void MainWindow::on_pushButtonDown_clicked()
{
    try {
        size_t index = ui->profilesListWidget->currentRow();
        size_t new_index = oal.ProfileMoveDown(index);
        RefreshModList();
        ui->profilesListWidget->setCurrentRow(new_index);
    } catch (std::exception& e) {
        ui->statusBar->showMessage(e.what(),50000);
    }
}
