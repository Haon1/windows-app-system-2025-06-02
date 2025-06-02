#pragma once
#include <QObject>

class CUiToolkit : public QObject
{
    Q_OBJECT
public:
    static CUiToolkit *GetInstance();
    //保存MainWindow指针
    void SaveMainWindowPtr(QWidget *p_MainWindow);

    QWidget *GetMainWindow();
private:
    explicit CUiToolkit(QObject *parent = nullptr);

private:
    static CUiToolkit *p_Instance;
    QWidget *m_pMainWindow; //主界面指针
};

#define g_UiToolkit CUiToolkit::GetInstance()
