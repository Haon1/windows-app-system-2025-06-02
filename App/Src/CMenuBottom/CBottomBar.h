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
    QWidget                 *m_pContentWidget;  //���ݿռ䣬 �����Ű�ť
    QHBoxLayout             *m_pHLayout;    //ˮƽ���֣�����m_pContentWidget����

    QList<CCommandButton*>  m_listBtn;  //��ŵײ�����ť�� �������ڹ���
    QList<ICommand *>       m_listCmd;  //��������࣬ ���������ͷ�
};
