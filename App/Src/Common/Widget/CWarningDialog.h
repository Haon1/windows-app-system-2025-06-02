#pragma once
#include <QDialog>

namespace Ui {
class WarningDialog;
}

class CWarningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CWarningDialog(QWidget *parent = nullptr);
    ~CWarningDialog();

    void SetText(const QString &strText);

public:
    bool ShowWarningDialog();
    void MoveToParentCenter();
private slots:
    void SlotBtnClicked();
protected:
//    virtual void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;

private:
    Ui::WarningDialog *m_pUi;
};
