#pragma once

#include <QWidget>

class ICommand;
class CCommandButton : public QWidget
{
    Q_OBJECT
public:
    explicit CCommandButton(QWidget *parent = nullptr);
    ~CCommandButton();

    void SetText(const QString &strText);
    void SetCommand(ICommand *pCmd);

protected:
    virtual void showEvent(QShowEvent *) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    virtual void enterEvent(QEvent *) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent *) Q_DECL_OVERRIDE;

    virtual void paintEvent(QPaintEvent *)Q_DECL_OVERRIDE;

signals:
    void SigClicked();  //按钮按下信号

private slots:
    void SlotClicked(); //按钮按下槽函数

private:
    ICommand *m_pCommand;   //命令类，按下后会执行该命令

    bool m_blIsPressed; //是否在按压
    bool m_blMoveout;   //鼠标是否已经移出去
    bool m_blHaover;    //鼠标在本控件区域内悬浮

    QString m_strText;
};

