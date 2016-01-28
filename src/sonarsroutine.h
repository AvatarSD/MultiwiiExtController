#ifndef SONARSROUTINE_H
#define SONARSROUTINE_H


#include "sonars.h"
#

class SonarsRoutine : public  public Sonars
{
public:
	SonarsRoutine( bool isSimple);

private:
    void dataResived(const SonarData data);
    //MainWindow * _w;
    void stdOut(const SonarData & data);
    bool _simple;
};

#endif // SONARSROUTINE_H
