#pragma once
#include <QObject>

class CUiToolkit : public QObject
{
    Q_OBJECT
public:
    static CUiToolkit *GetInstance();
    //����MainWindowָ��
    void SaveMainWindowPtr(QWidget *p_MainWindow);

    QWidget *GetMainWindow();
private:
    explicit CUiToolkit(QObject *parent = nullptr);

private:
    static CUiToolkit *p_Instance;
    QWidget *m_pMainWindow; //������ָ��
};

#define g_UiToolkit CUiToolkit::GetInstance()
