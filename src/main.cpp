#include "util/global.h"
#include "bddgame.h"

extern "C"
int main( int argc, char * argv [] )
try
{
	std::ios_base::sync_with_stdio(false);
	BddGame game;
	return game.Run();
}
catch( ... )
{
	std::cout << "Non-SDL Exception has occurred!" << std::endl;

	// put a breakpoint in this line, to prevent the shell from closing
	return 66;
}
