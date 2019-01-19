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
#include "Maze.h"
using namespace std;

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

	int depth, height, width, value;
	in >> height >> width >> depth;
	Maze *m = new Maze(depth, height, width);

	for (size_t i = 0; i < depth; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			for (size_t k = 0; k < width; k++)
			{
				in >> value;
				m->setValue(i, j, k, value);
			}
		}
	}

	out << "Solve Maze:" << endl << m->toString() << endl;
	if (m->find_maze_path(0, 0, 0))
	{
		out << "Solution:" << endl << m->toString();
	}
	else
	{
		out << "No Solution Exists!" << endl;
	}

	delete m;
	system("PAUSE");
	return 0;
}