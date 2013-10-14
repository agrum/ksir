#ifndef GAME_H
#define GAME_H

#include "ksir_common.h"
#include "pomelog.h"

#include "worlmap.h"

namespace ksir {

class Game
{
	
public:
	Game();

private:
	WorldMap* m_worldMap;
};

}

#endif // GAME_H
