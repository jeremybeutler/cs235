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
#include "ExpressionManager.h"
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

	// process input strings
	string line, command, input;
	string expression;
	ExpressionManager expMan;
	while (getline(in, line))
	{
		try
		{
			if (line.size() == 0) continue;
			istringstream iss(line);
			iss >> command;
			if (command == "Expression:") out << endl << line;
			else out << line;

			//tmp << iss.rdbuf();
			if (command == "Expression:")
			{
				expression = iss.str().substr(iss.tellg());		
				out << endl;
				expMan.setExpression(expression);
				// procession expression ...
				continue;
			}

			else if (command == "Infix:")
			{
				if (!expMan.isBalanced())
				{
					out << " Unbalanced";
				}
				else if (expMan.checkCleanInput() == 1) out << " Illegal Operator";
				else if (expMan.checkCleanInput() == 2) out << " Missing Operand";
				else if (expMan.checkCleanInput() == 3) out << " Missing Operator";
				else
				{
					out << " " << expMan.infix();
				}
				out << endl;
				continue;
			}

			else if (command == "Postfix:")
			{
				if (!expMan.isBalanced())
				{
					out << " Unbalanced";
				}
				else if (expMan.checkCleanInput() == 1) out << " Illegal Operator";
				else if (expMan.checkCleanInput() == 2) out << " Missing Operand";
				else if (expMan.checkCleanInput() == 3) out << " Missing Operator";
				else
				{
					out << " " << expMan.postfix();
				}
				out << endl;
				continue;
			}

			else if (command == "Prefix:")
			{
				if (!expMan.isBalanced())
				{
					out << " Unbalanced";
				}
				else if (expMan.checkCleanInput() == 1) out << " Illegal Operator";
				else if (expMan.checkCleanInput() == 2) out << " Missing Operand";
				else if (expMan.checkCleanInput() == 3) out << " Missing Operator";
				else
				{
					out << " " << expMan.prefix();
				}
				out << endl;
				continue;
			}

			else if (command == "Value:")
			{
				if (!expMan.isBalanced())
				{
					out << " Unbalanced";
				}
				else if (expMan.checkCleanInput() == 1) out << " Illegal Operator";
				else if (expMan.checkCleanInput() == 2) out << " Missing Operand";
				else if (expMan.checkCleanInput() == 3) out << " Missing Operator";
				else
				{
					out << " " << expMan.value();
				}
				out << endl;
				continue;
			}
		}
		catch (std::exception& e)
		{
			out << e.what() << endl;
		}
		out << endl;
	}

	system("PAUSE");

	return 0;
}