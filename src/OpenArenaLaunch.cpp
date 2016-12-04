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

#include "OpenArenaLaunchh.h"
#include "QDebug"

OpenArenaLaunch::OpenArenaLaunch()
{

}

void OpenArenaLaunch::setProfile( int value ) {
    this->profileNumber = value;
}

std::string OpenArenaLaunch::getProfileDir() {
    std::string ret;
    if (profileNumber == 1) {
        ret = this->profileBaseDir+"test1";
    }
    else if (profileNumber == 2) {
        ret = this->profileBaseDir+"test2";
    }
    return ret;
}

std::string OpenArenaLaunch::getModName() {
    std::string ret;
    if (profileNumber == 3) {
        ret = "oax";
    }
    return ret;
}

std::vector<std::string> OpenArenaLaunch::getArguments() {
    std::vector<std::string> arguments;
    std::string profileHomePath = getProfileDir();
    if (profileHomePath.length() > 0) {
        arguments.push_back("+set");
        arguments.push_back("fs_homepath");
        arguments.push_back(profileHomePath);
    }
    std::string modName = getModName();
    if (modName.length() > 0) {
        arguments.push_back("+set");
        arguments.push_back("fs_game");
        arguments.push_back(modName);
    }
    return arguments;
}

int OpenArenaLaunch::Launch() {
    //All these QProcess things should be moved out from OpenArenaLauncher so nothing needs QT
    if (!process) {
        process = new QProcess();
    }
    if (process->pid()) {
        return 1;
    }
    qDebug() << "Launching profile: " << profileNumber << ", with: " << openarena_path_bin.c_str();
    QStringList finalArguments;
    const auto& arguments = getArguments();
    for (const std::string& value : arguments) {
        finalArguments.push_back(QString::fromUtf8(value.c_str()));
    }
    process->start(openarena_path_bin.c_str(), finalArguments);
    return 0;
}
