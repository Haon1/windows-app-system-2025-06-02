#ifndef CSHADOWBUTTOMWIDGET_H
#define CSHADOWBUTTOMWIDGET_H

#include <QWidget>

class CShadowBottomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CShadowBottomWidget(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *);

};

#endif // CSHADOWBUTTOMWIDGET_H
