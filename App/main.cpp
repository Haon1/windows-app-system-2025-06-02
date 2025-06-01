#include "CAppSystem.h"
#include "CStyleLoader.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //����ϵͳ��ʽ
    CStyleLoader::SetStyle(":\\theme\\style\\system.qss");

    if (g_AppSystem)
    {
        g_AppSystem->Initialize();
    }
    return a.exec();
}
