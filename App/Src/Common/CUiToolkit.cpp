#include "CUiToolkit.h"

CUiToolkit *CUiToolkit::p_Instance = NULL;

CUiToolkit *CUiToolkit::GetInstance()
{
    if (!p_Instance)
    {
        p_Instance = new CUiToolkit();
    }
    return p_Instance;
}

void CUiToolkit::SaveMainWindowPtr(QWidget *p_MainWindow)
{
    m_pMainWindow = p_MainWindow;
}

QWidget *CUiToolkit::GetMainWindow()
{
    return m_pMainWindow;
}

CUiToolkit::CUiToolkit(QObject *parent)
    : QObject(parent)
    , m_pMainWindow(NULL)
{

}
