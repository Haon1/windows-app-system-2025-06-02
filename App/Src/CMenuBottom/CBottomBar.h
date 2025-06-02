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
    QWidget                 *m_pContentWidget;  //���ݿռ䣬 �����Ű�ť
    QHBoxLayout             *m_pHLayout;    //ˮƽ���֣�����m_pContentWidget����

    QList<stBtnInfo>        m_listBtnInfo;  //��ŵײ�����ť��Ϣ�� �������ڹ���

    CWarningDialog          *m_pWarningDialog;
};
