#include "mainwindow.h"
#include <QApplication>
#include "OpenArenaLaunchh.h"
#include <QDir>
#include <QStandardPaths>
#include "platform_things.h"

OpenArenaLaunch oal;

int main(int argc, char *argv[])
{
    oal.openarena_path_bin = getDefaultBinaryPath();
    oal.profileBaseDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).toUtf8().constData();
    oal.profileBaseDir += "openarena_launcher/profiles/";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
