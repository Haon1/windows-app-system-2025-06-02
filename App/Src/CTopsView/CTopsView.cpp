#include "CTopsView.h"
#include "ui_TopsView.h"

CTopsView::CTopsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopsView)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground, true);  //ʹ��ʽ����Ч
}

CTopsView::~CTopsView()
{
    delete ui;
}

void CTopsView::resizeEvent(QResizeEvent *)
{
    this->setFixedHeight(50);
}
