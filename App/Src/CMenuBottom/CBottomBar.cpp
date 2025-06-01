#include "CBottomBar.h"
#include "CShadowBottomWidget.h"
#include "Global_Common.h"
#include "ICommand.h"
#include "CCommandButton.h"

CBottomBar::CBottomBar(QWidget *parent)
    : CShadowBottomWidget(parent)
    , m_pContentWidget(NULL)
{
    setObjectName("bottom_bar");
    m_listCmd.clear();
    InitWidget();
}

CBottomBar::~CBottomBar()
{
    RELEASEIF(m_pContentWidget);
    foreach (ICommand *cmd, m_listCmd)
    {
        RELEASEIF(cmd);
    }
    foreach (CCommandButton *btn, m_listBtn)
    {
        RELEASEIF(btn);
    }
}

void CBottomBar::InitWidget()
{
    QHBoxLayout *p_Layout = new QHBoxLayout(this);
    if (!p_Layout)
    {
        return ;
    }
    p_Layout->setContentsMargins(0,0,0,0);
    m_pContentWidget = new QWidget(this);
    p_Layout->addWidget(m_pContentWidget);

    //创建布局
    m_pHLayout = new QHBoxLayout(m_pContentWidget);
    m_pHLayout->setContentsMargins(3, 3, 20, 3);
    m_pHLayout->setSpacing(12);

    //加入一个弹簧在前面
    QSpacerItem *horizontalSpacer;
    horizontalSpacer = new QSpacerItem(785, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_pHLayout->addItem(horizontalSpacer);

    //创建按钮加入布局
    struct _stBtn
    {
        QString str_Text;
        ICommand *p_Cmd;
    }array[]=
    {
        {QObject::tr("Calendar"),   NULL},
        {QObject::tr("Weather"),    NULL},
        {QObject::tr("Clock"),      NULL},
        {QObject::tr("Settings"),   NULL},
        {QObject::tr("Camera"),     NULL},
        {QObject::tr("Menu"),       NULL},
    };
    for (UINT8 i = 0; i < ARRAYSIZE(array); i++)
    {
        CCommandButton *p_Btn = new CCommandButton(this);
        if (!p_Btn)
        {
            continue;
        }
        p_Btn->SetText(array[i].str_Text);
        p_Btn->SetCommand(array[i].p_Cmd);
        m_pHLayout->addWidget(p_Btn);

        m_listBtn.push_back(p_Btn);
        m_listCmd.push_back(array[i].p_Cmd);
    }
}
