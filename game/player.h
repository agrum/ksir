#ifndef PLAYER_H
#define PLAYER_H

#include "actionlist.h"
#include "cardterritory.h"
#include "cardevent.h"
#include "cardmission.h"
#include "territory.h"

namespace ksir {

class Player
{
public:
	Player();

private:
	PRC<CardMission> m_mission;
	QList<PRC<CardTerritory> > m_cardTerritoryList;
	QList<PRC<CardTerritory> > m_cardEventList;
};

}

#endif // PLAYER_H
