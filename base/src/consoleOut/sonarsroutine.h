#ifndef SONARSROUTINE_H
#define SONARSROUTINE_H

#include "../sonars/sonars.h"


class SonarsRoutine
{
public:
	SonarsRoutine(Sonars & iface);

	void setMode(bool simple);

private:
	//MainWindow * _w;
    void dataResived(const SonarData & data);
    void stdOut(const SonarData & data);

    Sonars & _iface;
    bool _simple;
};

#endif // SONARSROUTINE_H
