#pragma once

#include <QListWidget>

class CListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit CListWidget(QWidget *parent = nullptr);
protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    virtual void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void ProcessHighLight(int iHighLightRow);
    void ProcessHover(int iHoverRow);
    void ClearHighLight();
    void SetClickedId(int iClickedId);
    int  GetClickedId();
private:
    QSize m_sizeWdtSize;
    QSize m_sizeItemSize;

    int   m_iClickedId;
};

