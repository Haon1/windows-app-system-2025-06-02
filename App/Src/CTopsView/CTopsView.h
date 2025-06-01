#ifndef CTOPSVIEW_H
#define CTOPSVIEW_H

#include <QWidget>

namespace Ui {
class TopsView;
}

class CTopsView : public QWidget
{
    Q_OBJECT

public:
    explicit CTopsView(QWidget *parent = nullptr);
    ~CTopsView();

protected:
    virtual void resizeEvent(QResizeEvent *);

private:
    Ui::TopsView *ui;
};

#endif // CTOPSVIEW_H
