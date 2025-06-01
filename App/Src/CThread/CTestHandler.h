#ifndef CTESTHANDLER_H
#define CTESTHANDLER_H

#include "IThreadHandler.h"
#include <QObject>

class CTestHandler : public IThreadHandler
{
    Q_OBJECT
public:
    CTestHandler();
    ~CTestHandler();
    void HandleTask() Q_DECL_OVERRIDE;
};

#endif // CTESTHANDLER_H
