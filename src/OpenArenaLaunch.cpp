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

#include "OpenArenaLaunch.h"

static void InitializeOaProfiles(LauncherConfig& config) {
    OaProfile p1;
    p1.homepath = "";
    p1.modName = "";
    p1.profileName = "Default";
    config.profiles.push_back(p1);
    p1.homepath = "test1";
    p1.modName = "";
    p1.profileName = "Test 1";
    config.profiles.push_back(p1);
    p1.homepath = "test2";
    p1.modName = "";
    p1.profileName = "Test 2";
    config.profiles.push_back(p1);
    p1.homepath = "";
    p1.modName = "oax";
    p1.profileName = "OAX";
    config.profiles.push_back(p1);
}

OpenArenaLaunch::OpenArenaLaunch()
{
    InitializeOaProfiles(this->config);
}

void OpenArenaLaunch::setProfile( std::size_t value ) {
    this->profileNumber = value;
    if (value > 0 && value < this->config.profiles.size()) {
        activeProfile = config.profiles.at(value);
        profileId = activeProfile.profileName;
    }
    else {
        profileId = "";
        profileNumber = 0;
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
    return activeProfile != config.profiles[profileNumber];
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

size_t OpenArenaLaunch::SaveProfile(const OaProfile& profile) {
	if (profile.profileName == "Default") {
		return 0;  //Add error message
	}
	for (size_t i = 0; i < config.profiles.size(); ++i) {
		OaProfile& p = this->config.profiles.at(i);
		if (p.profileName == profile.profileName) {
			p = profile;
			return i;
		}
	}
	config.profiles.push_back(profile);
	return config.profiles.size()-1;
}

size_t OpenArenaLaunch::RemoveProfile(size_t index) {
    if (index >= config.profiles.size()) {
        return index;  //Tried to remove an element not yet in config
    }
    const OaProfile& profile = config.profiles.at(index);
    if (profile.profileName == "Default") {
        return 0;  // Cannot delete "Default"
    }
    config.profiles.erase(config.profiles.begin()+index);
    if (index >= config.profiles.size()) {
        index--;
    }
    return index;
}
