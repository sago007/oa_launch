#ifndef PLATFORM_THINGS
#define PLATFORM_THINGS

inline std::string getDefaultBinaryPath() {
    std::string ret;
#ifdef _WIN32
    ret =  QString(QDir::currentPath()+"/openarena.exe").toUtf8().constData();
#else
    ret =  QString(QDir::currentPath()+"/openarena.x86_64").toUtf8().constData();
#endif
    return ret;
}

#endif // PLATFORM_THINGS

