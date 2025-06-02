#include "CBottomBar.h"
#include "CShadowBottomWidget.h"
#include "Global_Common.h"
#include "ICommand.h"
#include "CCommandButton.h"
#include "CWarningDialog.h"

CBottomBar::CBottomBar(QWidget *parent)
    : CShadowBottomWidget(parent)
    , m_pContentWidget(NULL)
{
    setObjectName("bottom_bar");
    InitWidget();
}

CBottomBar::~CBottomBar()
{
    RELEASEIF(m_pContentWidget);
    for (UINT8 i = 0; i < m_listBtnInfo.count(); i++)
    {
        RELEASEIF(m_listBtnInfo[i].m_pCmd);
        RELEASEIF(m_listBtnInfo[i].m_pBtn);
    }
    RELEASEIF(m_pWarningDialog);
}

void CBottomBar::ShowWarningDialog(const QString &strText)
{
    if (!m_pWarningDialog)
    {
        m_pWarningDialog = new CWarningDialog();
    }
    m_pWarningDialog->SetText(strText);
    m_pWarningDialog->ShowWarningDialog();
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
        //创建按钮
        CCommandButton *p_Btn = new CCommandButton(this);
        if (!p_Btn)
        {
            continue;
        }
        p_Btn->SetText(array[i].str_Text);
        p_Btn->SetCommand(array[i].p_Cmd);
        m_pHLayout->addWidget(p_Btn);

        //保存按钮和命令信息
        stBtnInfo st_BtnInfo;
        st_BtnInfo.m_pBtn = p_Btn;
        st_BtnInfo.m_pCmd = array[i].p_Cmd;
        m_listBtnInfo.push_back(st_BtnInfo);
        //这里信号槽测试用，功能实现后不需要
        connect(p_Btn, SIGNAL(SigClicked()), this, SLOT(SlotBtnClicked()));
    }
}

void CBottomBar::SlotBtnClicked()
{
    QObject *p_Obj = sender();
    if (!p_Obj)
    {
        return ;
    }
    for (UINT8 i = 0; i < m_listBtnInfo.count(); i++)
    {
        if (p_Obj == m_listBtnInfo.at(i).m_pBtn)
        {
            if (!m_listBtnInfo.at(i).m_pCmd)
            {
                //按钮命令为NULL则弹警告窗
                ShowWarningDialog(QObject::tr("Command is nullptr!"));
            }
        }
    }
}
