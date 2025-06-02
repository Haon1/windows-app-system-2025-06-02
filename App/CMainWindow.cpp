#include "CMainWindow.h"
#include "CTopsView.h"
#include "CContentWidget.h"
#include "CBottomBar.h"
#include "CShadowBottomWidget.h"
#include <QVBoxLayout>

CMainWindow::CMainWindow(QWidget *parent)
    : QWidget(parent)
    , m_pTopStatusView(NULL)
    , m_pCenterWidget(NULL)
    , m_pBottomWidget(NULL)
{
    this->setFixedSize(1280, 800);
    CreateContent();
}

CMainWindow::~CMainWindow()
{
    RELEASEIF(m_pTopStatusView);
    RELEASEIF(m_pCenterWidget);
    RELEASEIF(m_pBottomWidget);
}

VOID CMainWindow::CreateContent()
{
    QVBoxLayout *ver_Layout = new QVBoxLayout(this);
    if (!ver_Layout)
    {
        return ;
    }
    ver_Layout->setContentsMargins(3,0,3,3);
    ver_Layout->setSpacing(0);


    m_pTopStatusView = new CTopsView(this);             //状态栏
    m_pCenterWidget  = new CContentWidget(this);        //中心窗体
    m_pBottomWidget  = new CBottomBar(this);            //底部栏

    ver_Layout->addWidget(m_pTopStatusView);
    ver_Layout->addWidget(m_pCenterWidget);
    ver_Layout->addWidget(m_pBottomWidget);
}
