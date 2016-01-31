#include "sonarsroutine.h"

#include <iostream>
#include <list>
using namespace std;

SonarsRoutine::SonarsRoutine(Sonars & iface) :
		_iface(iface), _simple(0)
{
	iface.dataResived = std::bind(&SonarsRoutine::dataResived, this,
			std::placeholders::_1);
}

void SonarsRoutine::dataResived(const SonarData & data)
{
	//emit incomingDataRsv(data);
	// _w->showSonarsData(data);

	// std::cout << "hell" << std::endl;

	stdOut(data);

}

void SonarsRoutine::stdOut(const SonarData & data)
{
	static std::list<SonarData> dataList;

	if (_simple)
		std::cout << "Name is: " << data.getName() << "\tNum is: "
				<< data.getNum() << "\tDist: " << data.getDistance()
				<< std::endl;
	else if (data.getName() == "SB")
	{
		printf("\033[2J");
		for (uint8_t i = 0; i < 18; i++)
		{
			std::cout << (uint32_t) i << ": ";
			std::string temp = string("SR") + std::to_string(i);
			auto it = dataList.begin();
			for (; it != dataList.end(); it++)
				if (it->getNameNum() == temp)
				{
					std::cout << "Name is: " << it->getName() << "\tNum is: "
							<< it->getNum() << "\tDist: " << it->getDistance();
					break;
				}
			if (it == dataList.end())
				std::cout << "---";
			cout << std::endl;
		}
		dataList.clear();
	}
	else
		dataList.push_back(data);

}

void SonarsRoutine::setMode(bool simple)
{
	_simple = simple;
}
