#include "CTestHandler.h"
#include <QDebug>

CTestHandler::CTestHandler()
{

}

CTestHandler::~CTestHandler()
{

}

void CTestHandler::HandleTask()
{
    qDebug() << "TestHandler in progress ...";
}
