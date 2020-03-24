#ifndef UPDATER_H
#define UPDATER_H
#include <QObject>
#include <windows.h>

class Updater : public QObject {
    Q_OBJECT
public:
    Updater();
    ~Updater() {}
    void sendSignal();
public slots:
    void process();
    void finished();
signals:
    void update();
    void end_process();
private:
    bool run;
};

#endif // UPDATER_H
