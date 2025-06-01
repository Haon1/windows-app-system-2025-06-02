#pragma once

#include <QWidget>
#include <QMap>
#include "Global_Common.h"

namespace Ui {
class ContentWidget;
}

class IWidgetCreator;
class CContentWidget : public QWidget
{
    Q_OBJECT

public:
    struct stContentCreator_STUR
    {
        INT8            m_s8PageIndex;  //页面枚举
        IWidgetCreator *m_pCreator;     //窗体创建类
    };

    //页面枚举
    enum EM_PAGE
    {
        E_PAGE_START = 0,
        E_PAGE_ONE = E_PAGE_START,
        E_PAGE_TWO,
        E_PAGE_THREE,

        E_PAGE_MAX,
    };

    explicit CContentWidget(QWidget *parent = nullptr);
    ~CContentWidget();

private:
    VOID SetItemAlignment();
    VOID SetCurrentIndex(INT16 s16TabIndex);
    QWidget *CreatePage(const INT16 &s16PageIndex);

private slots:
    void SlotCurrentRowChanged(int iCurrentIndex);

protected:
    virtual void showEvent(QShowEvent *) Q_DECL_OVERRIDE;

private:
    Ui::ContentWidget *m_pUi;

    INT16                        m_s16TabIndex;  //当前页索引
    QMap<QString, QWidget*>     m_mapPageWidget;
    QList<stContentCreator_STUR> m_listContentCreator;

};
