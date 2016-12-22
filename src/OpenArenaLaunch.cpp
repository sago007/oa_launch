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

static void InitializeOaProfiles(OaProfileCollection& collection) {
    OaProfile p1;
    p1.homepath = "test1";
    p1.modName = "";
    p1.profileName = "Test 1";
    collection.profiles["test1"] = p1;
    p1.homepath = "test2";
    p1.modName = "";
    p1.profileName = "Test 2";
    collection.profiles["test2"] = p1;
    p1.homepath = "";
    p1.modName = "oax";
    p1.profileName = "OAX";
    collection.profiles["oax"] = p1;
}

OpenArenaLaunch::OpenArenaLaunch()
{
    InitializeOaProfiles(this->profileCollection);
}

void OpenArenaLaunch::setProfile( int value ) {
    this->profileNumber = value;
    if (value == 1) {
        profileId = "test1";
        activeProfile = profileCollection.profiles["test1"];
    }
    else if (value == 2) {
        profileId = "test2";
        activeProfile = profileCollection.profiles["test2"];
    }
    else if (value == 3) {
        profileId = "oax";
        activeProfile = profileCollection.profiles["oax"];
    }
    else {
        profileId = "";
        activeProfile = OaProfile();
    }
}


std::string OpenArenaLaunch::getProfileDir() {
    std::string ret;
    if (activeProfile.homepath.length() > 0) {
        ret = this->profileBaseDir+activeProfile.homepath;
    }
    return ret;
}

std::string OpenArenaLaunch::getModName() {
    std::string ret;
    if (activeProfile.modName.length() > 0) {
        ret = activeProfile.modName;
    }
    return ret;
}

bool OpenArenaLaunch::profileModified() {
    return activeProfile != profileCollection.profiles[profileId];
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
