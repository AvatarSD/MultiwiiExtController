#include "sonarsroutine.h"

#include <iostream>
#include <list>
using namespace std;


SonarsRoutine::SonarsRoutine(bool isSimple, QObject *parent) : QObject(parent), Sonars(), _simple(isSimple)//, _w(w)
{

}

void SonarsRoutine::dataResived(const SonarData data)
{
    //emit incomingDataRsv(data);
    // _w->showSonarsData(data);

    // std::cout << "hell" << std::endl;

    stdOut(data);

}

void SonarsRoutine::stdOut(const SonarData & data)
{
    static std::list<SonarData> dataList;

if(_simple)
    std::cout << "Name is: " << data.getName()<< "\tNum is: " << data.getNum() << "\tDist: " << data.getDistance() << std::endl;
else
    if( data.getName() == "SB")
    {
        printf( "\033[2J" );
        for (uint8_t i = 0; i<18; i++)
        {
            std::cout << (uint32_t)i << ": ";
            std::string temp = string("SR") + std::to_string(i);
            auto it = dataList.begin();
            for(; it!= dataList.end(); it++)
                if(it->getNameNum() == temp)
                {
                    std::cout << "Name is: " << it->getName()<< "\tNum is: " << it->getNum() << "\tDist: " << it->getDistance();
                    break;
                }
            if(it == dataList.end())
                std::cout << "---";
            cout << std::endl;
        }
        dataList.clear();
    }
    else
        dataList.push_back(data);

}
