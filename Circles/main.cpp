#include "GameFramework.h"

int main( int argc, char* argv[] )
{
	GameFramework *g = new GameFramework( argc, argv );
	g->setInstance(g);
	g->startFramework();
	g->run();

    return 0;
}
