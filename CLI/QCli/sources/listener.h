#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>

class Listener : public QObject
{
    Q_OBJECT
public:
    Listener();

public slots:
    void        process();

signals:
    void        idleSig();
};

#endif // LISTENER_H
