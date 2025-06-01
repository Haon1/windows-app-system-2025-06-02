#include "CListWidget.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include <QDebug>

const int s32_HEIGHT = 84;

class CListWidgetItemDelegate : public QStyledItemDelegate
{
public:
    CListWidgetItemDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent)
    {

    }
protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const override
    {
        painter->setRenderHint(QPainter::Antialiasing);
        QRect _rect = option.rect.adjusted(5, 0, -5, -10);
        QString str_Text = index.data().toString();

        QColor clr_Background;
        QColor clr_Text = QColor("#ffffff");

        if (option.state & QStyle::State_Selected)
        {
            clr_Background = QColor("#0085ff");
        }
        else if (option.state & QStyle::State_Enabled)
        {
            clr_Background = QColor("#e4efff");
            clr_Text       = QColor("#000000");
        }
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(clr_Background));
        painter->drawRoundedRect(_rect.adjusted(2,2,-2,-2), 4, 4);

        QPen pen;
        pen.setColor(clr_Text);
        pen.setWidth(2);
        painter->setPen(pen);
        QFont font;
        font.setFamily("ºÚÌå");
        font.setPixelSize(30);
        font.setWeight(75);
        painter->setFont(font);
        painter->drawText(_rect, Qt::AlignCenter ,str_Text);
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override
    {
        Q_UNUSED(index)
        return QSize(option.rect.width(), s32_HEIGHT);
    }
};

CListWidget::CListWidget(QWidget *parent)
    :QListWidget(parent)
{
    this->setItemDelegate(new CListWidgetItemDelegate(this));
}
