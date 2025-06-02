#include "CWarningDialog.h"
#include "Global_Common.h"
#include "CUiToolkit.h"
#include "ui_WarningDialog.h"

#include <QGraphicsDropShadowEffect>
#include <QPainter>

CWarningDialog::CWarningDialog(QWidget *parent)
    : QDialog((parent == NULL) ? g_UiToolkit->GetMainWindow() : parent)
    , m_pUi(new Ui::WarningDialog)
{
    m_pUi->setupUi(this);
//    setAttribute(Qt::WA_StyledBackground, true);  //使样式表生效
//    setAttribute(Qt::WA_TranslucentBackground, true); //全透明
//    setWindowOpacity(0.7);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //无边框


    connect(m_pUi->btn_cancel, SIGNAL(clicked()), this, SLOT(SlotBtnClicked()));
    connect(m_pUi->btn_ok,     SIGNAL(clicked()), this, SLOT(SlotBtnClicked()));
}

CWarningDialog::~CWarningDialog()
{
    delete m_pUi;
}

void CWarningDialog::SetText(const QString &strText)
{
    m_pUi->lb_text->setText(strText);
}

bool CWarningDialog::ShowWarningDialog()
{
    MoveToParentCenter();
    return QDialog::exec();
}


void CWarningDialog::MoveToParentCenter()
{
    QWidget *p_Parent = parentWidget();
    //父窗体左上角在整个屏幕的点
    QPoint pt_ParentTopLeft = p_Parent->geometry().topLeft();
    INT32 s32_X = (p_Parent->width() - width()) / 2;
    INT32 s32_Y = (p_Parent->height() - height()) / 2;
    //居中显示
    move(s32_X + pt_ParentTopLeft.x(),
         s32_Y + pt_ParentTopLeft.y());
}

void CWarningDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
}

void CWarningDialog::SlotBtnClicked()
{
    QObject *p_Obj = sender();
    if (!p_Obj)
    {
        return ;
    }

    if (p_Obj == m_pUi->btn_cancel)
    {
        reject();
    }
    else if (p_Obj == m_pUi->btn_ok)
    {
        accept();
    }
}

void CWarningDialog::resizeEvent(QResizeEvent *)
{

}
