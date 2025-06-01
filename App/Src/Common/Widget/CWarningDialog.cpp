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
    this->setAttribute(Qt::WA_StyledBackground, true);  //ʹ��ʽ����Ч
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint); //�ޱ߿�

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
    //p.drawRoundedRect(bmp.rect(), 20, 20); //�ĸ��Ƕ���Բ��
    //ֻҪ�ϱ߽�Բ��
    int arcR = 5; //Բ����С
    QRect rect = this->rect().adjusted(0, 0, 0, 0);
    QPainterPath path;
    //��ʱ��
    path.moveTo(arcR, 0);
    //���Ͻ�
    path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
    path.lineTo(0, rect.height()-arcR);
    //���½�
    path.arcTo(0, rect.height() - arcR * 2 , arcR * 2, arcR * 2, 180.0f, 90.0f);
    path.lineTo(rect.width(), rect.height());
    //���½�
    path.arcTo(rect.width() - arcR * 2, rect.height() - arcR * 2 , arcR * 2, arcR * 2, 270.0f, 90.0f);
    path.lineTo(rect.width(), arcR);
    //���Ͻ�
    path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
    path.lineTo(arcR, 0);
    p.drawPath(path);
    //���д��������ӣ���Ȼ�޷��ﵽ��������ʾ
    p.fillPath(path, QBrush(Qt::red));
    setMask(bmp);

    return QDialog::resizeEvent(e);
}
#endif
