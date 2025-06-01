#include "CStyleLoader.h"
#include <QFile>
#include <QApplication>

CStyleLoader::CStyleLoader(QObject *parent) : QObject(parent)
{

}

void CStyleLoader::SetStyle(const QString &strQssFile)
{
    QFile qss(strQssFile);
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}
