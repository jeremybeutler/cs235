//YOU MAY NOT MODIFY THIS DOCUMENT
#ifndef MAZE_INTERFACE_H
#define MAZE_INTERFACE_H
#include <string>
using std::string;

class MazeInterface
{
public:
	MazeInterface(void) {}
	~MazeInterface(void) {}

	/** Set maze value
	@parm height
	@parm width
	@parm depth
	@parm value
	*/
	virtual void setValue(int height, int width, int depth, int value) = 0;

	/** Solve maze
	@return true if solvable, else false
	*/
	virtual bool find_maze_path(int depth, int height, int width) = 0;

	/** Output maze (same order as input maze)
	@return string of xx layers
	*/
	virtual string toString() const = 0;

};
#endif //MAZE_INTERFACE_H