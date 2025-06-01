#ifndef CDATACOLLECTHANDLER_H
#define CDATACOLLECTHANDLER_H

#include "IThreadHandler.h"
#include <QObject>

class CDataCollectHandler : public IThreadHandler
{
    Q_OBJECT
public:
    CDataCollectHandler();

    void HandleTask() Q_DECL_OVERRIDE;
};

#endif // CDATACOLLECTHANDLER_H
