#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include "CShadowBottomWidget.h"

class CWarningDialog;
class ICommand;
class CCommandButton;
class CBottomBar : public CShadowBottomWidget
{
    Q_OBJECT
public:

    struct stBtnInfo
    {
        CCommandButton *m_pBtn;
        ICommand       *m_pCmd;
    };

    explicit CBottomBar(QWidget *parent = nullptr);
    ~CBottomBar();

    void ShowWarningDialog(const QString &strText);
protected:
    void InitWidget();

private slots:
    void SlotBtnClicked();
private:
    QWidget                 *m_pContentWidget;  //内容空间， 用来放按钮
    QHBoxLayout             *m_pHLayout;    //水平布局，用于m_pContentWidget布局

    QList<stBtnInfo>        m_listBtnInfo;  //存放底部栏按钮信息， 后续用于管理

    CWarningDialog          *m_pWarningDialog;
};
