#pragma once
#include <QObject>
#include <QMap>
#include "Global_Common.h"

class CMainWindow;
class IThreadHandler;
class CThread;
class CAppSystem : public QObject
{
    Q_OBJECT
public:

    //线程任务ID枚举
    enum EM_THREAD_HANDLER
    {
        E_THREAD_HANDLER_START = 0,
        E_THREAD_HANDLER_DATA_COLLECT = E_THREAD_HANDLER_START, //数据采集
        E_THREAD_HANDLER_TEST,  //测试用

        E_THREAD_HANDLER_MAX
    };

    ~CAppSystem();
    static CAppSystem *GetInstance();

    //系统初始化
    VOID Initialize();
private:
    CAppSystem();
    static CAppSystem *m_pInstance;

    //创建UI
    VOID CreateUi();
    VOID CreateThreadHandlers();    //创建线程任务
    VOID CreateSysThread();         //创建线程

    CMainWindow                 *m_pMainWindow;         //程序主窗口， 内部包含顶部栏，中心区域、底部栏， 一共三部分
    QMap<int, IThreadHandler*>  m_mapThreadHandlers;    //线程任务map, key是线程任务id枚举， value是线程任务指针
    QList<CThread*>             m_listThread;           //线程列表
};

//定义一个宏方便调用
#define g_AppSystem CAppSystem::GetInstance()

