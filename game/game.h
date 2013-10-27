#ifndef GAME_H
#define GAME_H

#include <QVector>

#include "ksir_common.h"
#include "pomelog.h"

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

	QList<const Region*> worldRegionList();
	QList<const Territory*> worldTerritoryList();

	PRC<CardTerritory> pickTerritoryCard();
	PRC<CardTerritory> pickEventCard();
	PRC<CardTerritory> pickMissionCard();

	void discardTerritoryCard(const PRC<CardTerritory>& p_card);
	void discardEventCard(const PRC<CardTerritory>& p_card);

private:
	WorldMap* m_worldMap;
	Deck<PRC<CardTerritory> > m_territoryDeck;
	Deck<PRC<CardEvent> > m_eventDeck;
	Deck<PRC<CardMission> > m_missionDeck;
};

//INLINES

inline QList<PRC<Territory> >&
Game::worldTerritoryList()
{
	return m_worldMap->territoryList();
}

inline PRC<CardTerritory>
Game::pickTerritoryCard()
{
	return m_territoryDeck.drawCard();
}

inline PRC<CardTerritory>
Game::pickEventCard()
{
	return m_eventDeck.drawCard();
}

inline PRC<CardTerritory>
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
Game::discardEventCard(const PRC<CardTerritory>& p_card)
{
	return m_eventDeck.discardCard(p_card);
}

}

#endif // GAME_H
