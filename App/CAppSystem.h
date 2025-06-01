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

    //�߳�����IDö��
    enum EM_THREAD_HANDLER
    {
        E_THREAD_HANDLER_START = 0,
        E_THREAD_HANDLER_DATA_COLLECT = E_THREAD_HANDLER_START, //���ݲɼ�
        E_THREAD_HANDLER_TEST,  //������

        E_THREAD_HANDLER_MAX
    };

    ~CAppSystem();
    static CAppSystem *GetInstance();

    //ϵͳ��ʼ��
    VOID Initialize();
private:
    CAppSystem();
    static CAppSystem *m_pInstance;

    //����UI
    VOID CreateUi();
    VOID CreateThreadHandlers();    //�����߳�����
    VOID CreateSysThread();         //�����߳�

    CMainWindow                 *m_pMainWindow;         //���������ڣ� �ڲ��������������������򡢵ײ����� һ��������
    QMap<int, IThreadHandler*>  m_mapThreadHandlers;    //�߳�����map, key���߳�����idö�٣� value���߳�����ָ��
    QList<CThread*>             m_listThread;           //�߳��б�
};

//����һ���귽�����
#define g_AppSystem CAppSystem::GetInstance()

