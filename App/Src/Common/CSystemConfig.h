#pragma once
#include <QObject>
#include "SystemCommom.h"

class CSystemConfig
{
public:
    static CSystemConfig *GetInstance();
private:
     CSystemConfig(QString strConfigFileName);
    static CSystemConfig *m_pInstance;
};

#define g_SystemConfig CSystemConfig::GetInstance()

