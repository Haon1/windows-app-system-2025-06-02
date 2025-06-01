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
    void SigClicked();  //��ť�����ź�

private slots:
    void SlotClicked(); //��ť���²ۺ���

private:
    ICommand *m_pCommand;   //�����࣬���º��ִ�и�����

    bool m_blIsPressed; //�Ƿ��ڰ�ѹ
    bool m_blMoveout;   //����Ƿ��Ѿ��Ƴ�ȥ
    bool m_blHaover;    //����ڱ��ؼ�����������

    QString m_strText;
};

