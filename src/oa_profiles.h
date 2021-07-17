#ifndef OA_PROFILES
#define OA_PROFILES
#include <string>
#include <map>

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
};

#endif // OA_PROFILES

