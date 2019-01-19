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
#include "BST.h"
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

	string cmd;
	string mode;
	BST<int>* bst_int = new BST<int>();
	BST<string>* bst_str = new BST<string>();

	while (in >> cmd)
	{
		out << cmd;
		out << ((cmd == "print") ? ":" : " ");
		if (cmd == "INT")
		{
			bst_str->clearTree();
			mode = "INT";
			out << "true";
		}

		else if (cmd == "STRING")
		{
			bst_int->clearTree();
			mode = "STRING";
			out << "true";
		}

		else if (mode == "INT")
		{
			if (cmd == "add")
			{
				int temp;
				in >> temp;
				out << temp << " " << ((bst_int->addNode(temp)) ? "true" : "false");
			}
			else if (cmd == "remove")
			{
				int temp;
				in >> temp;
				out << temp << " " << ((bst_int->removeNode(temp)) ? "true" : "false");
			}
			else if (cmd == "clear")
			{
				out << ((bst_int->clearTree()) ? "true" : "false");
			}
			else if (cmd == "find")
			{
				int temp;
				in >> temp;
				out << temp << " " << ((bst_int->find(temp)) ? "Found" : "Not Found");
			}
			else if (cmd == "size")
			{
				out << bst_int->size();
			}
			else if (cmd == "print")
			{
				out << bst_int->toString();
			}
		}

		else if (mode == "STRING")
		{
			if (cmd == "add")
			{
				string temp;
				in >> temp;
				out << temp << " " << ((bst_str->addNode(temp)) ? "true" : "false");
			}
			else if (cmd == "remove")
			{
				string temp;
				in >> temp;
				out << temp << " " << ((bst_str->removeNode(temp)) ? "true" : "false");
			}
			else if (cmd == "clear")
			{
				out << ((bst_str->clearTree()) ? "true" : "false");
			}
			else if (cmd == "find")
			{
				string temp;
				in >> temp;
				out << temp << " " << ((bst_str->find(temp)) ? "Found" : "Not Found");
			}
			else if (cmd == "size")
			{
				out << bst_str->size();
			}
			else if (cmd == "print")
			{
				out << bst_str->toString();
			}
		}
		
		out << endl;
		
	}
	
	
	delete bst_int;
	delete bst_str;
	system("PAUSE");
	return 0;
}