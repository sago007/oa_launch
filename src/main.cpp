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
#include <QApplication>
#include "OpenArenaLaunch.h"
#include <QDir>
#include <QStandardPaths>
#include "platform_things.h"

OpenArenaLaunch oal;

int main(int argc, char *argv[])
{
    oal.openarena_path_bin = getDefaultBinaryPath();
    oal.profileBaseDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toUtf8().constData();
    oal.profileBaseDir += "/openarena_launcher/profiles/";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
