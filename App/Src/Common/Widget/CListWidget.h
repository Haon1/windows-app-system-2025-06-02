#pragma once

#include <QListWidget>

class CListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit CListWidget(QWidget *parent = nullptr);
};

