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


    m_pTopStatusView = new CTopsView(this);             //״̬��
    m_pCenterWidget  = new CContentWidget(this);        //���Ĵ���
    m_pBottomWidget  = new CBottomBar(this);            //�ײ���

    ver_Layout->addWidget(m_pTopStatusView);
    ver_Layout->addWidget(m_pCenterWidget);
    ver_Layout->addWidget(m_pBottomWidget);
}
