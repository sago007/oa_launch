#include "OpenArenaLaunchh.h"
#include "QDebug"

OpenArenaLaunch::OpenArenaLaunch()
{

}

void OpenArenaLaunch::setProfile( int value ) {
    this->profileNumber = value;
}

std::vector<std::string> OpenArenaLaunch::getArguments() {
    std::vector<std::string> arguments;
    if (profileNumber == 1) {
        arguments.push_back("+set");
        arguments.push_back("fs_homepath");
        arguments.push_back(this->profileBaseDir+"test1");
    }
    else if (profileNumber == 2) {

    }
    else if (profileNumber == 3) {
        arguments.push_back("+set");
        arguments.push_back("fs_game");
        arguments.push_back("oax");
    }
    return arguments;
}

int OpenArenaLaunch::Launch() {
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
