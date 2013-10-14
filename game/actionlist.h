#ifndef ACTIONLIST_H
#define ACTIONLIST_H

#include "cardevent.h"
#include "cardterritory.h"
#include "territory.h"

namespace ksir {

class ActionList{

public:
	ActionList();

	virtual void reinforcementInit();
	virtual void reinforcementAvailable(
			QList<PRC<CardTerritory> > p_playerHand,
			const QList<Territory*>& p_list,
			unsigned int& p_unitsAvailable,
			unsigned int& p_herosAvailable);
	virtual void reinforcementAddUnit(
			Territory* p_territory);
	virtual void reinforcementAddHero(
			Territory* p_territory);
	virtual void reinforcementRmvUnit(
			Territory* p_territory);
	virtual void reinforcementRmvHero(
			Territory* p_territory);

	virtual void attackInit();
	virtual void attackAvailable(
			const unsigned int p_round,
			unsigned int& p_attacksAvailable);
	virtual void attackAddSrc(
			const QList<Territory*>& p_playerTerritoryList,
			Territory* p_selectedTerritory);
	virtual void attackRmvSrc(
			Territory* p_selectedTerritory);
	virtual void attackAddDst(
			const QList<Territory*>& p_playerTerritoryList,
			Territory* p_selectedTerritory);
	virtual void attackRmvDst(
			Territory* p_selectedTerritory);
	virtual void attackLaunch();
	virtual void attackConquer();

	virtual void movementInit();
	virtual void movementAvailable(
			QList<PRC<CardEvent> > p_playerHand,
			unsigned int& p_movementsAvailable);
	virtual void movementAddSrc(
			const QList<Territory*>& p_playerTerritoryList,
			Territory* p_selectedTerritory);
	virtual void movementRmvSrc(
			Territory* p_selectedTerritory);
	virtual void movementAddDst(
			const QList<Territory*>& p_playerTerritoryList,
			Territory* p_selectedTerritory);
	virtual void movementRmvDst(
			Territory* p_selectedTerritory);
	virtual void movementTrigger();
};

}

#endif // ACTIONLIST_H
