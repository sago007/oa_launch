#ifndef OA_LAUNCH_H
#define OA_LAUNCH_H
#include <string>
#include "QProcess"

class OpenArenaLaunch
{
public:
    OpenArenaLaunch();
    int Launch();
    void setProfile(int profileNumber);
    std::vector<std::string> getArguments();
    std::string profileBaseDir;
    std::string openarena_path_bin = "/bighome/poul/games/openarena-0.8.8/openarena.x86_64";
private:
    QProcess* process = nullptr;
    int profileNumber;
};

#endif // OA_LAUNCH_H
