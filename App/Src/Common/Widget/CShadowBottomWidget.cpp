#include "CShadowBottomWidget.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>

const int S32_SHADOW_X_OFFSET = 0;
const int S32_SHADOW_Y_OFFSET = -4;
const int S32_SHADOW_BLUR_RADIUS = 10;
const QColor COLOR_SHADOW = QColor(0,0,0,25);
const QColor COLOR_BACKGROUND = QColor(255,255,255);

CShadowBottomWidget::CShadowBottomWidget(QWidget *parent)
    : QWidget(parent)
{
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(S32_SHADOW_X_OFFSET, S32_SHADOW_Y_OFFSET);
    effect->setColor(COLOR_SHADOW);
    effect->setBlurRadius(S32_SHADOW_BLUR_RADIUS);
    setGraphicsEffect(effect);
}

void CShadowBottomWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(COLOR_BACKGROUND));
    painter.drawRect(rect());
}
