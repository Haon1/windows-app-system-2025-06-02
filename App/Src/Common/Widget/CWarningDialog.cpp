#include "CWarningDialog.h"
#include "Global_Common.h"
#include <QBitmap>
#include <QPainter>
#include "ui_WarningDialog.h"

CWarningDialog::CWarningDialog(QWidget *parent)
    : QDialog(parent)
    , m_pUi(new Ui::WarningDialog)
{
    m_pUi->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true);  //使样式表生效
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //无边框

    connect(m_pUi->btn_cancel, SIGNAL(clicked()), this, SLOT(SlotBtnClicked()));
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
    raise();
    show();
    return QDialog::exec();
}

void CWarningDialog::MoveToParentCenter()
{
    QWidget *p_Parent = parentWidget();
    INT32 s32_X = (p_Parent->width() - width()) / 2;
    INT32 s32_Y = (p_Parent->height() - height()) / 2;
    this->move(s32_X, s32_Y);
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
        return QDialog::reject();
    }
    else
    {
        return QDialog::accept();
    }
}

#if 0
void CWarningDialog::resizeEvent(QResizeEvent* e)
{
    QBitmap bmp(size());
    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::Antialiasing);
    //p.drawRoundedRect(bmp.rect(), 20, 20); //四个角都是圆弧
    //只要上边角圆弧
    int arcR = 5; //圆弧大小
    QRect rect = this->rect().adjusted(0, 0, 0, 0);
    QPainterPath path;
    //逆时针
    path.moveTo(arcR, 0);
    //左上角
    path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
    path.lineTo(0, rect.height()-arcR);
    //左下角
    path.arcTo(0, rect.height() - arcR * 2 , arcR * 2, arcR * 2, 180.0f, 90.0f);
    path.lineTo(rect.width(), rect.height());
    //右下角
    path.arcTo(rect.width() - arcR * 2, rect.height() - arcR * 2 , arcR * 2, arcR * 2, 270.0f, 90.0f);
    path.lineTo(rect.width(), arcR);
    //右上角
    path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
    path.lineTo(arcR, 0);
    p.drawPath(path);
    //此行代码必须添加，不然无法达到正常的显示
    p.fillPath(path, QBrush(Qt::red));
    setMask(bmp);

    return QDialog::resizeEvent(e);
}
#endif
