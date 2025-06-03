#include "CCommandButton.h"
#include "ICommand.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>

namespace
{
QColor CLR_NORMAL  = QColor("#409eff"); //平常颜色
QColor CLR_HANOVER = QColor("#66b1ff"); //鼠标悬浮颜色
QColor CLR_PRESSED = QColor("#3a8ee6"); //按下颜色
int    S32_BORDER_RADIUS = 5;           //圆角像素
}

CCommandButton::CCommandButton(QWidget *parent)
    : QWidget(parent)
    , m_pCommand(NULL)
    , m_blIsPressed(false)
    , m_blMoveout(false)
    , m_blHaover(false)
    , m_strText("")
{
    connect(this, SIGNAL(SigClicked()), this, SLOT(SlotClicked()));
}

CCommandButton::~CCommandButton()
{

}

void CCommandButton::SetText(const QString &strText)
{
    m_strText = strText;
}

void CCommandButton::SetCommand(ICommand *pCmd)
{
    if (!m_pCommand)
    {
        m_pCommand = pCmd;
    }
}

void CCommandButton::showEvent(QShowEvent *)
{
    m_blIsPressed = false;
    m_blMoveout   = false;
    m_blHaover    = false;
}

void CCommandButton::mousePressEvent(QMouseEvent *)
{
    m_blIsPressed = true;
    m_blHaover    = false;
    update();
}

void CCommandButton::mouseReleaseEvent(QMouseEvent *)
{
    if (!m_blMoveout)
    {
        emit SigClicked();  //正常释放，发信号执行点击事件
        m_blIsPressed = false;
        update();
    }
}

void CCommandButton::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标移出
    if (!rect().contains(event->pos()))
    {
        m_blIsPressed = false;
        m_blMoveout   = true;
        m_blHaover    = false;
        update();
    }
}

void CCommandButton::enterEvent(QEvent *)
{
    m_blHaover = true;
    update();
}

void CCommandButton::leaveEvent(QEvent *)
{
    m_blHaover = false;
    update();
}

void CCommandButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect _rect = rect().adjusted(2, 2, -2, -2);

    QColor clr_Background = CLR_NORMAL;
    if (m_blHaover)
    {
        clr_Background = CLR_HANOVER;
    }
    else if (m_blIsPressed)
    {
        clr_Background = CLR_PRESSED;
    }

    QBrush brush(clr_Background);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    //绘制背景色
    painter.drawRoundedRect(_rect, S32_BORDER_RADIUS, S32_BORDER_RADIUS);

    //绘制文本
    QPen pen;
    pen.setColor("#ffffff");
    pen.setWidth(2);
    painter.setPen(pen);
//    QFont font = painter.font();
//    font.setPixelSize(20);
//    font.setWeight(57);
    painter.drawText(_rect, Qt::AlignCenter | Qt::TextWordWrap, m_strText);
}

void CCommandButton::SlotClicked()
{
    if (m_pCommand)
    {
        //执行命令
        m_pCommand->Execute();
    }
}
