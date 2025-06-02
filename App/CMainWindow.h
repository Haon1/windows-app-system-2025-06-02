#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QWidget>
#include <Global_Common.h>
class CTopsView;
class CContentWidget;
class CBottomBar;
class CMainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

signals:

private:
    VOID CreateContent();

private:
    CTopsView           *m_pTopStatusView;  //״̬��
    CContentWidget      *m_pCenterWidget;   //�м䴰��
    CBottomBar          *m_pBottomWidget;   //�ײ���
};

#endif // CMAINWINDOW_H
