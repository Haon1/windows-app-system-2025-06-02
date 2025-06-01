#ifndef IWIDGETCREATOR_H
#define IWIDGETCREATOR_H

#include <QWidget>

class IWidgetCreator
{
public:
    IWidgetCreator();
    virtual QWidget *create(QWidget *parent) = 0;
};

template<class T>
class CWidgetCreator: public IWidgetCreator
{
public:
    CWidgetCreator(){};
    virtual QWidget *create(QWidget *parent)
    {
        return new T(parent);
    }

};
#endif // IWIDGETCREATOR_H
