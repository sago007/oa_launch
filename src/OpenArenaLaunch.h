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

#ifndef OA_LAUNCH_H
#define OA_LAUNCH_H
#include <string>
#include <vector>
#include "oa_profiles.h"
#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"

//Note: Try to keep it QT free.

struct LauncherConfig {
    std::string exe_path;
    std::vector<OaProfile> profiles;

    template<class Archive>
    void serialize(Archive & archive) {
        archive( CEREAL_NVP(exe_path), CEREAL_NVP(profiles));
    }
};

class OpenArenaLaunch
{
public:
    OpenArenaLaunch();
    int Launch();
    void setProfile(std::size_t profileNumber);
    int getProfile() {return profileNumber;}
    LauncherConfig config;
    const OaProfile& getProfile(int id);
    std::vector<std::string> getArguments();
    std::string getProfileDir();
	std::string getModName();
    std::string profileBaseDir;
    std::string profileConfigFile = "config.json";
    std::string openarena_path_bin = "/bighome/poul/games/openarena-0.8.8/openarena.x86_64";
    bool profileModified();
    int profileNumber;
    std::string profileId;
    OaProfile activeProfile;
    void SaveToFile();
    void LoadFromFile();
    size_t SaveProfile(const OaProfile& profile);
    size_t RemoveProfile(size_t index);
    size_t ProfileMoveUp(size_t index);
    size_t ProfileMoveDown(size_t index);
};

#endif // OA_LAUNCH_H
