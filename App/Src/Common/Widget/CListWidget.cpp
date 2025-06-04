#include "CListWidget.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include <QScroller>
#include <QMouseEvent>
#include <QDebug>

class CListWidgetItemDelegate : public QStyledItemDelegate
{
public:
    static const int ITEM_STATE = Qt::UserRole+1;

    enum EM_ITEM_STATE
    {
        E_ITEM_STATE_NORMAL = 0,    //常规状态
        E_ITEM_STATE_HIGHLIGHT,     //按压状态
        E_ITEM_STATE_HOVER,         //鼠标悬停
    };

    CListWidgetItemDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {
        SetColor();
    }

    virtual void SetColor()
    {
        m_clrNormal       = QColor("#ECF5FF");
        m_clrSelected     = QColor("#409EFF");
        m_clrHighLight    = QColor("#3A8EE6");
        m_clrDisable      = QColor("#A0CFFF");
        m_clrBorder       = QColor("#B3D8FF");
        m_clrTextSelected = QColor("#ffffff");
        m_clrTextNormal   = QColor("#409EFF");;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const override
    {
        painter->setRenderHint(QPainter::Antialiasing);
        QRect _rect = option.rect.adjusted(5, 0, -5, -10);  //矩形
        QString str_Text = index.data().toString();         //文本

        QColor clr_Background;  //背景色
        QColor clr_Text = QColor("#ffffff");
        bool bl_IsDrawBorder = false;
        if (E_ITEM_STATE_HIGHLIGHT == index.data(ITEM_STATE)
                && (option.state & QStyle::State_Enabled)
                && (index.flags() & Qt::ItemIsSelectable))
        {
            clr_Background = m_clrHighLight;
            clr_Text       = m_clrTextSelected;
        }
        else if (E_ITEM_STATE_HOVER == index.data(ITEM_STATE)
            && (option.state & QStyle::State_Enabled)
            && (index.flags() & Qt::ItemIsSelectable))
        {
            clr_Background = m_clrSelected;
            clr_Text       = m_clrTextSelected;
        }
        else
        {
            if (option.state & QStyle::State_Selected)  //选中（当前行）
            {
                       clr_Background = m_clrSelected;
                       clr_Text       = m_clrTextSelected;
            }
            else    //常规状态E_ITEM_STATE_NORMAL == index.data(ITEM_STATE)
            {
                clr_Background  = m_clrNormal;
                clr_Text        = m_clrTextNormal;
                bl_IsDrawBorder = true;
            }
        }

        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(clr_Background));
        painter->drawRoundedRect(_rect.adjusted(2,2,-2,-2), 4, 4);

        if (bl_IsDrawBorder)    //绘制边框
        {
            painter->save();
            painter->setPen(m_clrBorder);
            painter->drawRoundedRect(_rect.adjusted(1,1,-1,-1), 4, 4);
            painter->restore();
        }

        QPen pen;
        pen.setColor(clr_Text);
        pen.setWidth(2);
        painter->setPen(pen);
        QFont font;
        font.setFamily("黑体");
        font.setPixelSize(25);
        font.setWeight(QFont::DemiBold);
        painter->setFont(font);
        painter->drawText(_rect, Qt::AlignCenter ,str_Text);
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override
    {

        return QStyledItemDelegate::sizeHint(option, index);
    }
private:
    QColor m_clrNormal;
    QColor m_clrSelected;
    QColor m_clrHighLight;
    QColor m_clrDisable;
    QColor m_clrBorder;
    QColor m_clrTextSelected;
    QColor m_clrTextNormal;
};

CListWidget::CListWidget(QWidget *parent)
    : QListWidget(parent)
    , m_sizeWdtSize(160,600)
    , m_sizeItemSize(150, 70)
    , m_iClickedId(-1)
{
    setMouseTracking(true);
    setFrameShape(QFrame::NoFrame);
    this->setItemDelegate(new CListWidgetItemDelegate(this));
//    this->setSpacing(2);   //item间隔(上下左右)

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QScroller *p_Scroller = QScroller::scroller(this->viewport());
    if (p_Scroller)
    {
        QScroller::grabGesture(this->viewport(), QScroller::LeftMouseButtonGesture);
        QScrollerProperties prop = p_Scroller->scrollerProperties();
        prop.setScrollMetric(QScrollerProperties::MinimumVelocity, 0);
        prop.setScrollMetric(QScrollerProperties::MaximumVelocity, 0.01);
        prop.setScrollMetric(QScrollerProperties::DragStartDistance, 0.02);
        prop.setScrollMetric(QScrollerProperties::OvershootDragDistanceFactor, 0);
        prop.setScrollMetric(QScrollerProperties::OvershootScrollDistanceFactor, 0);
        p_Scroller->setScrollerProperties(prop);
    }
}

void CListWidget::mousePressEvent(QMouseEvent *event)
{
    if (!event)
    {
        return ;
    }

    QPoint pos = event->pos();
    QListWidgetItem *p_Item = itemAt(pos);

    if (p_Item)
    {
        SetClickedId(row(p_Item));
        if (p_Item->flags() & Qt::ItemIsSelectable)
        {
            ProcessHighLight(row(p_Item));
        }
        else
        {
            ClearHighLight();
        }
    }

}

void CListWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!event)
    {
        return ;
    }
    ClearHighLight();
    QPoint pos = event->pos();
    QListWidgetItem *p_Item = itemAt(pos);
    if (p_Item && (p_Item->flags() & Qt::ItemIsSelectable))
    {
        int r = row(p_Item);
        if (r != -1 && GetClickedId() == r)
        {
            setCurrentRow(r);
        }
    }
}

void CListWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!event)
    {
        return ;
    }
    QPoint pos = event->pos();
    QListWidgetItem *p_Item = itemAt(pos);
    if (p_Item && (p_Item->flags() & Qt::ItemIsSelectable))
    {
        ProcessHover(row(p_Item));
    }
}

void CListWidget::leaveEvent(QEvent */*event*/)
{
    ClearHighLight();
    SetClickedId(-1);
}

void CListWidget::resizeEvent(QResizeEvent *event)
{
    this->setFixedWidth(m_sizeWdtSize.width());
    for (int i = 0; i < count(); i++)
    {
        this->item(i)->setSizeHint(m_sizeItemSize);
        this->item(i)->setTextAlignment(Qt::AlignCenter);
    }

    QListWidget::resizeEvent(event);
}

void CListWidget::ProcessHighLight(int iHighLightRow)
{
    for (int i = 0; i < this->count(); i++)
    {
        QListWidgetItem *p_Item = item(i);
        if (i == iHighLightRow)
        {
            p_Item->setData(CListWidgetItemDelegate::ITEM_STATE, CListWidgetItemDelegate::E_ITEM_STATE_HIGHLIGHT);
        }
        else
        {
            p_Item->setData(CListWidgetItemDelegate::ITEM_STATE, CListWidgetItemDelegate::E_ITEM_STATE_NORMAL);
        }
    }
}

void CListWidget::ProcessHover(int iHoverRow)
{
    for (int i = 0; i < this->count(); i++)
    {
        QListWidgetItem *p_Item = item(i);
        if (i == iHoverRow)
        {
            p_Item->setData(CListWidgetItemDelegate::ITEM_STATE, CListWidgetItemDelegate::E_ITEM_STATE_HOVER);
        }
        else
        {
            p_Item->setData(CListWidgetItemDelegate::ITEM_STATE, CListWidgetItemDelegate::E_ITEM_STATE_NORMAL);
        }
    }
}

void CListWidget::ClearHighLight()
{
    ProcessHighLight(-1);
}

void CListWidget::SetClickedId(int iClickedId)
{
    m_iClickedId = iClickedId;
}

int CListWidget::GetClickedId()
{
    return m_iClickedId;
}
