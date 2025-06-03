#include "CContentWidget.h"
#include "ui_ContentWidget.h"
#include "CListWidget.h"
#include "IWidgetCreator.h"
#include "CWarningDialog.h"
#include <QDebug>

CContentWidget::CContentWidget(QWidget *parent)
    : QWidget(parent)
    , m_pUi(new Ui::ContentWidget)
    , m_s16TabIndex(-1)
{
    m_pUi->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true);  //使样式表生效

    stContentCreator_STUR array_PagePointer[] =
    {
        {E_PAGE_ONE,    new CWidgetCreator<QWidget>()},
        {E_PAGE_TWO,    new CWidgetCreator<QWidget>()},
        {E_PAGE_THREE,  new CWidgetCreator<QWidget>()},
    };
    for (UINT8 i = 0; i < ARRAYSIZE(array_PagePointer); i++)
    {
        m_listContentCreator.push_back(array_PagePointer[i]);
    }

    SetCurrentIndex(0);
    //设置listWidget文本居中
    SetItemAlignment();
    connect(m_pUi->SideTab, SIGNAL(currentRowChanged(int)), this, SLOT(SlotCurrentRowChanged(int)));
}

CContentWidget::~CContentWidget()
{
    delete m_pUi;
    for (UINT8 i = 0; i < m_listContentCreator.count(); i++)
    {
        RELEASEIF(m_listContentCreator[i].m_pCreator);
    }

    QMap<QString, QWidget*>::const_iterator iter;
   for(iter= m_mapPageWidget.constBegin(); iter != m_mapPageWidget.constEnd(); ++iter)
   {
       if (iter.value())
       {
           delete iter.value();
       }
   }
}

VOID CContentWidget::SetCurrentIndex(INT16 s16TabIndex)
{
    INT16 s16_CurTabIndex = m_pUi->SideTab->currentRow();

    if (s16TabIndex == s16_CurTabIndex)
    {
        return ;
    }

    const BOOL bl_IndexValid = (0 <= s16TabIndex && s16TabIndex < m_pUi->SideTab->count());
    if (bl_IndexValid)
    {
        m_pUi->SideTab->setCurrentRow(s16TabIndex); //这里设置当前row， 会响应信号去切换页面
    }
}

QWidget *CContentWidget::CreatePage(const INT16 &s16PageIndex)
{
    for (UINT8 i = 0; i < m_listContentCreator.count(); i++)
    {
        if (s16PageIndex == m_listContentCreator.at(i).m_s8PageIndex)
        {
            stContentCreator_STUR *p_ContentCreator = &m_listContentCreator[i];
            if (p_ContentCreator)
            {
                IWidgetCreator *p_Creator = p_ContentCreator->m_pCreator;
                QWidget *p_PagePointer = qobject_cast<QWidget*>(p_Creator->create(m_pUi->stackedWidget));

                if (p_PagePointer)
                {
                    QString str_Key = QString("%1").arg(s16PageIndex);
                    m_mapPageWidget[str_Key] = p_PagePointer;
                    m_pUi->stackedWidget->addWidget(p_PagePointer);
                    return p_PagePointer;
                }
            }
        }
    }
    qCritical() << "------------------------ PageIndex:" << s16PageIndex << " Create Page fail.";
    return NULL;
}

void CContentWidget::SlotCurrentRowChanged(int iCurrentIndex)
{
    const BOOL bl_IndexValid = (0 <= iCurrentIndex && iCurrentIndex < m_pUi->SideTab->count());

    if (m_s16TabIndex != iCurrentIndex && bl_IndexValid)
    {
        m_s16TabIndex = iCurrentIndex;
    }

    QString str_Key = QString("%1").arg(m_s16TabIndex);
    if (m_mapPageWidget.contains(str_Key))
    {
        m_pUi->stackedWidget->setCurrentWidget(m_mapPageWidget[str_Key]);
    }
    else
    {
        QWidget *p_Widget = CreatePage(m_s16TabIndex);
        m_pUi->stackedWidget->setCurrentWidget(p_Widget);
    }
}

void CContentWidget::showEvent(QShowEvent *)
{

}

void CContentWidget::SetItemAlignment()
{
    m_pUi->SideTab->setItemAlignment(Qt::AlignCenter);
    for (INT32 i = 0; i < m_pUi->SideTab->count(); i++)
    {
        QListWidgetItem *p_Item = m_pUi->SideTab->item(i);
        if (p_Item)
        {
            p_Item->setTextAlignment(Qt::AlignCenter);
        }
    }
}
