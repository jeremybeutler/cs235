//YOU MAY NOT MODIFY THIS DOCUMENT
#ifndef MAZE_H
#define MAZE_H
#include "MazeInterface.h"

enum color { OPEN=0, BLOCKED=1, TEMP=2, EXIT=3, PATH=4 };


class Maze : public MazeInterface
{
private:
	int depth;
	int height;
	int width;
	int*** maze;
public:
	Maze(int depth, int height, int width) : depth(depth), height(height), width(width)
	{
		maze = new int**[depth];
		for (int i = 0; i < depth; ++i)
		{
			maze[i] = new int*[height];
			for (int j = 0; j < height; ++j)
			{
				maze[i][j] = new int[width];
			}
		}
		
	}
	~Maze() 
	{ 
		for (int i = 0; i < depth; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				delete[] maze[i][j];
			}
			delete[] maze[i];
		}
		delete[] maze;
	}

	/** Set maze value
	@parm height
	@parm width
	@parm depth
	@parm value
	*/
	virtual void setValue(int depth, int height, int width, int value)
	{
		maze[depth][height][width] = value;
	}

	/** Solve maze
	@return true if solvable, else false
	*/
	virtual bool find_maze_path(int depth, int height, int width)
	{
		// check boundary (base case #1)
		if ((height < 0) || (height >= this->height) ||
			(width < 0) || (width >= this->width) || 
			(depth < 0) || (depth >= this->depth)) return false;

		if (maze[depth][height][width] != OPEN) return false; // blocked (base case #2)

		if ((height == this->height - 1) && (width == this->width - 1) && (depth == this->depth - 1))
		{
			maze[depth][height][width] = EXIT; // Success! (base case #3)
			return true;
		}

		maze[depth][height][width] = PATH; // Recursive case
		if (find_maze_path(depth, height, width - 1) ||
			find_maze_path(depth, height, width + 1) ||
			find_maze_path(depth, height - 1, width) ||
			find_maze_path(depth, height + 1, width) ||
			find_maze_path(depth - 1, height, width) ||
			find_maze_path(depth + 1, height, width)) return true;
		maze[depth][height][width] = TEMP;
		return false;
	}

	/** Output maze (same order as input maze)
	@return string of xx layers
	*/
	virtual string toString() const 
	{
		std::stringstream ss;
		for (size_t i = 0; i < depth; i++)
		{
			ss << "Layer " << i + 1 << std::endl;
			for (size_t j = 0; j < height; j++)
			{
				for (size_t k = 0; k < width; k++)
				{
					if (maze[i][j][k] == OPEN || maze[i][j][k] == TEMP)
					{
						ss << "_ ";
					}
					else if (maze[i][j][k] == BLOCKED)
					{
						ss << "X ";
					}
					else if (maze[i][j][k] == EXIT)
					{
						ss << "3 ";
					}
					else if (maze[i][j][k] == PATH)
					{
						ss << "2 ";
					}
				}
				ss << std::endl;
			}
		}
		return ss.str();
	}

};
#endif //MAZE_H