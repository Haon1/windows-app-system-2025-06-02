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
    CTopsView           *m_pTopStatusView;  //状态栏
    CContentWidget      *m_pCenterWidget;   //中间窗体
    CBottomBar          *m_pBottomWidget;   //底部栏
};

#endif // CMAINWINDOW_H
