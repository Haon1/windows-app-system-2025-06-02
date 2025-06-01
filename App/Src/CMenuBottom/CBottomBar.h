#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include "CShadowBottomWidget.h"

class ICommand;
class CCommandButton;
class CBottomBar : public CShadowBottomWidget
{
    Q_OBJECT
public:
    explicit CBottomBar(QWidget *parent = nullptr);
    ~CBottomBar();

protected:
    void InitWidget();
private:
    QWidget                 *m_pContentWidget;  //内容空间， 用来放按钮
    QHBoxLayout             *m_pHLayout;    //水平布局，用于m_pContentWidget布局

    QList<CCommandButton*>  m_listBtn;  //存放底部栏按钮， 后续用于管理
    QList<ICommand *>       m_listCmd;  //存放命令类， 后续用于释放
};
