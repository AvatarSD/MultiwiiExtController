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

void SonarsRoutine::dataResived(const DistSensorData & data)
{
	//emit incomingDataRsv(data);
	// _w->showSonarsData(data);

	// std::cout << "hell" << std::endl;

	stdOut(data);

}

void SonarsRoutine::stdOut(const DistSensorData & data)
{
	static std::list<DistSensorData> sonarDataList, opticalDataList;

	if (_simple)
		std::cout << "Name is: " << data.getName() << "\tNum is: "
				<< data.getNum() << "\tDist: " << data.getDistance()
				<< std::endl;
	else if (data.getName() == "SB")
	{
		//sonarDataList.clear();
		//opticalDataList.clear();
	}
	else if (data.getName() == "IT")
	{
		printf("\033[2J");
		std::cout << "Sonars:" << std::endl;
		for (uint8_t i = 0; i < 16; i++)
		{
			std::cout << (uint32_t) i << ": ";
			std::string temp = string("SR") + std::to_string(i);
			auto it = sonarDataList.begin();
			for (; it != sonarDataList.end(); it++)
				if (it->getNameNum() == temp)
				{
					std::cout << "Name is: " << it->getName() << "\tNum is: "
							<< it->getNum() << "\tDist: " << it->getDistance();
					break;
				}
			if (it == sonarDataList.end())
				std::cout << "---";
			cout << std::endl;
		}
		std::cout << std::endl << "Optical:" << std::endl;
		for (uint8_t i = 0; i < 16; i++)
		{
			std::cout << (uint32_t) i << ": ";
			std::string temp = string("OP") + std::to_string(i);
			auto it = opticalDataList.begin();
			for (; it != opticalDataList.end(); it++)
				if (it->getNameNum() == temp)
				{
					std::cout << "Name is: " << it->getName() << "\tNum is: "
							<< it->getNum() << "\tDist: " << it->getDistance();
					break;
				}
			if (it == opticalDataList.end())
				std::cout << "---";
			cout << std::endl;
		}
	}
	else if (data.getName() == "SR")
	{
		sonarDataList.remove(data);
		sonarDataList.push_back(data);
	}
	else if (data.getName() == "OP")
	{
		opticalDataList.remove(data);
		opticalDataList.push_back(data);
	}
}

void SonarsRoutine::setMode(bool simple)
{
	_simple = simple;
}
