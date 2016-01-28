#ifndef SONARSROUTINE_H
#define SONARSROUTINE_H

#include <QObject>
#include "sonars.h"
#include "mainwindow.h"

class SonarsRoutine : public QObject, public Sonars
{
    Q_OBJECT
public:
    explicit SonarsRoutine( bool isSimple, /*MainWindow * w,*/ QObject *parent = 0);

private:
    void dataResived(const SonarData data);
    //MainWindow * _w;
    void stdOut(const SonarData & data);
    bool _simple;
};

#endif // SONARSROUTINE_H
