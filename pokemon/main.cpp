#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream> 
#include <fstream>
#include "HashMap.h"
#include "Set.h"
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
	string line, command, key, val, setVal, poke1, poke2, weapon1, weapon2;
	HashMap<string, string> pokemon;
	HashMap<string, string> moves;
	HashMap<string, Set<string>> effectivities;
	HashMap<string, Set<string>> ineffectivities;
	Set<string> set;
	while (getline(in, line))
	{
		if (line.empty()) continue;
		stringstream iss(line);
		iss >> command;
		//cout << line << endl;

		if (command == "Pokemon:")
		{
			out << line << endl;
			iss >> key >> val;
			pokemon[key] = val;
		}
		else if (command == "Move:")
		{
			out << line << endl;
			iss >> key >> val;
			moves[key] = val;
		}
		else if (command == "Effective:")
		{
			iss >> key;
			if (effectivities.count(key) == 0)
			{
				effectivities[key] = Set<string>();
				out << line << endl;
				while (iss >> setVal)
				{
					effectivities[key].insert(setVal);
				}
			}
			else
			{
				effectivities[key].clear();
				out << line << endl;
				while (iss >> setVal)
				{
					effectivities[key].insert(setVal);
				}
			}
			//set.clear();
		}
		else if (command == "Ineffective:")
		{
			iss >> key;
			if (ineffectivities.count(key) == 0)
			{
				ineffectivities[key] = Set<string>();
				out << line << endl;
				while (iss >> setVal)
				{
					ineffectivities[key].insert(setVal);
				}
			}
			else
			{
				ineffectivities[key].clear();
				out << line << endl;
				while (iss >> setVal)
				{
					ineffectivities[key].insert(setVal);
				}

			}
			
			//set.clear();
		}
		else if (command == "Pokemon")
		{
			out << "Pokemon: " << pokemon.toString() << endl;
		}
		else if (command == "Moves")
		{
			out << "Moves: " << moves.toString() << endl;
		}
		else if (command == "Effectivities")
		{
			out << "Effectivities: " << effectivities.toString() << endl;
		}
		else if (command == "Ineffectivities")
		{
			out << "Ineffectivities: " << ineffectivities.toString() << endl;
		}
		else if (command == "Battle:")
		{
			iss >> poke1 >> weapon1 >> poke2 >> weapon2;
			string typePoke1 = pokemon[poke1];
			string typePoke2 = pokemon[poke2];
			string typeWeapon1 = moves[weapon1];
			string typeWeapon2 = moves[weapon2];
			out << line << endl << poke1 << " (" << weapon1 << ") vs " << poke2 << " (" << weapon2 << ")" << endl;
			cout << ineffectivities[moves[weapon1]].count(typePoke2);
			int damage1To2 = effectivities[moves[weapon1]].count(pokemon[poke2]) - ineffectivities[moves[weapon1]].count(pokemon[poke2]);
			int damage2To1 = effectivities[moves[weapon2]].count(pokemon[poke1]) - ineffectivities[moves[weapon2]].count(pokemon[poke1]);
			out << poke1 << "'s " << weapon1 << " is ";
			if (damage1To2 > 0)
			{
				out << "super ";
			}
			else if (damage1To2 < 0)
			{
				out << "in";
			}
			out << "effective against " << poke2 << endl
				<< weapon2 << " is super effective against [" << effectivities[typeWeapon2] << "] type Pokemon." << endl
				<< weapon2 << " is ineffective against [" << ineffectivities[typeWeapon2] << "] type Pokemon." << endl
				<< poke2 << "'s " << weapon2 << " is ";
			if (damage2To1 > 0)
			{
				out << "super ";
			}
			else if (damage2To1 < 0)
			{
				out << "in";
			}
			out << "effective against " << poke1 << endl;

			if ((damage1To2 - damage2To1) > 0) out << "In the battle between " << poke1 << " and " << poke2 << ", " <<  poke1 << " wins!" << endl << endl;
			else if ((damage1To2 - damage2To1) < 0) out << "In the battle between " << poke1 << " and " << poke2 << ", " << poke2 << " wins!" << endl << endl;
			else out << "The battle between " << poke1 << " and " << poke2 << " is a tie." << endl << endl;

		}
		else if (command == "Set:")
		{
			Set<string> set;
			out << line << endl;
			while (iss >> setVal)
			{
				set.insert(setVal);
			}
			out << "  [" << set.toString() << "]" << endl << endl;
			set.clear();
		}

	}
	pokemon.clear();
	moves.clear();
	effectivities.clear();
	ineffectivities.clear();


	system("PAUSE");
	return 0;

}