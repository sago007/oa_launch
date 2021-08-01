#ifndef OA_PROFILES
#define OA_PROFILES
#include <string>
#include <map>
#include "cereal/archives/json.hpp"
#include "cereal/types/string.hpp"

struct OaProfile {
    std::string profileName;
    std::string modName;
    std::string homepath;
    bool operator==(const OaProfile& other) {
        if (profileName != other.profileName) {
            return false;
        }
        if (modName != other.modName) {
            return false;
        }
        if (homepath != other.homepath) {
            return false;
        }
        return true;
    }
    bool operator !=(const OaProfile& other) {
        return !(*this == other);
    }

    template<class Archive>
    void serialize(Archive & archive) {
        archive( CEREAL_NVP(profileName), CEREAL_NVP(modName), CEREAL_NVP(homepath));
    }
};

#endif // OA_PROFILES

