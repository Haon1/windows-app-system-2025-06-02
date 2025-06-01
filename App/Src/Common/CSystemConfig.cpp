#include "CSystemConfig.h"
#include <QDebug>
#include <QFile>

CSystemConfig *CSystemConfig::m_pInstance = NULL;

CSystemConfig *CSystemConfig::GetInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new CSystemConfig(CONFIG_FILE);
    }
    return m_pInstance;
}

CSystemConfig::CSystemConfig(QString strConfigFileName)
{
    QFile file(strConfigFileName);
    if (!file.exists())
    {
        qDebug() << strConfigFileName << "is not exist!";
    }
}
