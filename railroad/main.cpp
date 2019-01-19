#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream> 
#include <fstream>
#include "Deque.h"
#include "Vector.h"
#include "Queue.h"
#include "Stack.h"
#include "Station.h"
using namespace std;

std::string process(std::string const& s)
{
	std::string::size_type pos = s.find(':');
	if (pos != std::string::npos)
	{
		return s.substr(0, pos);
	}
	else
	{
		return s;
	}
}

int main(int argc, char *argv[])
{
	VS_MEM_CHECK
		//	Create input stream from argv[1] and output stream to argv[2]

		if (argc < 3)
		{
			cerr << "Please provide name of input and output files";
			system("PAUSE");
			return 1;
		}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		system("PAUSE");
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);

	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		system("PAUSE");
		return 3;
	}

	// process input strings
	Station<int> myStation;
	string line, command, type, str_car, temp;
	int car = 0;
	while (getline(in, line))
	{
		out << line;
		command = "";
		type = "";
		str_car = "";
		if (line.empty()) continue;
		stringstream iss(line);
		//iss >> command >> type >> str_car;
		for (int i = 0; iss >> temp; i++)
		{
			if (i == 0)
			{
				command = process(temp);
				type = temp.substr(temp.find(":") + 1);
			}
			else if (i == 1)
			{
				str_car = temp;
				car = stoi(str_car);
			}

		}
		if (command == "Add")
		{
			if (type == "station")
			{
				out << myStation.addCar(car);
			}
			else if (type == "stack")
			{
				out << myStation.addStack();
			}
			else if (type == "queue")
			{
				out << myStation.addQueue();
			}
		}
		else if (command == "Remove")
		{
			if (type == "station")
			{
				out << myStation.removeCar();
			}
			else if (type == "stack")
			{
				out << myStation.removeStack();
			}
			else if (type == "queue")
			{
				out << myStation.removeQueue();
			}
		}
		else if (command == "Top")
		{
			if (type == "queue")
			{
				out << myStation.topQueue();
			}
			else if (type == "stack")
			{
				out << myStation.topStack();
			}
		}
		else if (command == "Size")
		{
			if (type == "queue")
			{
				out << myStation.sizeQueue();
			}
			else if (type == "stack")
			{
				out << myStation.sizeStack();
			}
		}
		else if (command == "Train")
		{
			out << myStation.toString();
		}
		
		out << endl;
	}

	system("PAUSE");
	return 0;
}