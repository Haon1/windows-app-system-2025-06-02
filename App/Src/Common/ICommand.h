#pragma once

#include <QObject>

class ICommand : public QObject
{
    Q_OBJECT
public:
    explicit ICommand(QObject *parent = nullptr);
    ~ICommand();
public:
    virtual bool Execute() = 0;

};
