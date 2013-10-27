#ifndef GAME_H
#define GAME_H

#include <QVector>

#include <utils/prc.h>
#include <pomelog.h>

#include "worldmap.h"
#include "deck.h"
#include "cardterritory.h"
#include "cardevent.h"
#include "cardmission.h"

namespace ksir {

class Game
{
	
public:
	Game();

	const QList<Region*>& worldRegionList();
	const QList<Territory*>& worldTerritoryList();

	PRC<CardTerritory> pickTerritoryCard();
	PRC<CardEvent> pickEventCard();
	PRC<CardMission> pickMissionCard();

	void discardTerritoryCard(const PRC<CardTerritory>& p_card);
	void discardEventCard(const PRC<CardEvent>& p_card);

private:
	WorldMap* m_worldMap;
	Deck<PRC<CardTerritory> > m_territoryDeck;
	Deck<PRC<CardEvent> > m_eventDeck;
	Deck<PRC<CardMission> > m_missionDeck;
};

//INLINES

inline const QList<Region*>&
Game::worldRegionList()
{
	return m_worldMap->regionList();
}

inline const QList<Territory*>&
Game::worldTerritoryList()
{
	return m_worldMap->territoryList();
}

inline PRC<CardTerritory>
Game::pickTerritoryCard()
{
	return m_territoryDeck.drawCard();
}

inline PRC<CardEvent>
Game::pickEventCard()
{
	return m_eventDeck.drawCard();
}

inline PRC<CardMission>
Game::pickMissionCard()
{
	return m_missionDeck.drawCard();
}

inline void
Game::discardTerritoryCard(const PRC<CardTerritory>& p_card)
{
	return m_territoryDeck.discardCard(p_card);
}

inline void
Game::discardEventCard(const PRC<CardEvent>& p_card)
{
	return m_eventDeck.discardCard(p_card);
}

}

#endif // GAME_H
