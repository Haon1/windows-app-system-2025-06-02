#ifndef CSTYLELOADER_H
#define CSTYLELOADER_H

#include <QObject>

class CStyleLoader : public QObject
{
    Q_OBJECT
public:
    explicit CStyleLoader(QObject *parent = nullptr);

    static void SetStyle(const QString &strQssFile);

};

#endif // CSTYLELOADER_H
