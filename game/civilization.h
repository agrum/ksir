#ifndef CIVILIZATION_H
#define CIVILIZATION_H

#include "cardterritory.h"
#include "cardevent.h"
#include "cardmission.h"
#include "territory.h"
#include "game.h"

namespace ksir {

class Civilization
{
public:
	Civilization();

	//-/
	virtual void turnInit();

	//-/
	virtual void reinforcementAvailable(
			QList<const PRC<CardTerritory> >& p_territoryHand,
			unsigned int& p_unitsAvailableFromTerritories,
			unsigned int& p_unitsAvailableFromRegions);
	virtual void reinforcementUseCombo(
			const PRC<CardTerritory>& m_first,
			const PRC<CardTerritory>& p_second,
			const PRC<CardTerritory>& p_third,
			unsigned int& p_unitsAvailableFromCombo);
	virtual void reinforcementTrigger(
			const QList<const PRC<CardTerritory> >& p_dstList,
			const QList<unsigned int>& p_reinforcementList);

	//-/
	virtual void attackAvailable(
			QList<const Territory*>& o_boundaryTerritories,
			QList<const PRC<CardEvent> >& o_attackEventHand,
			unsigned int& o_attacksAvailable);
	virtual void attackTargetsFrom(
			const Territory*& p_src,
			QList<const Territory*>& o_dstList);
	virtual void attackGetAttackPanel(
			const Territory*& p_src,
			const Territory*& p_dst,
			QDomDocument& o_panel);
	virtual void attackUseEvent(
			const PRC<CardEvent>& p_eventCard,
			const Territory*& p_src,
			const Territory*& p_dst);
	virtual void attackGetBattleInitialIssue(
			const Territory*& p_src,
			const Territory*& p_dst,
			QList<unsigned int>& o_diceSrc,
			QList<unsigned int>& o_diceDst);
	virtual void attackCallBattleFinalIssue(
			const Territory*& p_src,
			const Territory*& p_dst,
			const QList<unsigned int>& p_diceSrc,
			const QList<unsigned int>& p_diceDst);

	//-/
	virtual void movementAvailable(
			QList<const Territory*>& o_populatedTerritories,
			unsigned int& o_movementsAvailable);
	virtual void movementChoicesFrom(
			const Territory*& p_src,
			QList<const Territory*>& o_dstList);
	virtual void movementTrigger(
			const QList<const Territory*>& p_srcList,
			const QList<const Territory*>& p_dstList,
			const QList<unsigned int>& p_reinforcementList);

	//-/
	virtual void turnEnd();

protected:
	//-/
	QList<const Territory*> territoriesOwned() const;
	QList<const Territory*> territoriesOwnedIn(const QList<const Territory*>&) const;
	QList<const Territory*> territoriesNotOwnedIn(const QList<const Territory*>&) const;
	QList<const Territory*> territoriesInSameRegionAs(const Territory*&) const;
	QList<const Territory*> territoriesLinkedWith(const Territory*&) const;

private:
	//Game
	PRC<Game> m_game;
	QList<Territory*> m_territoryList;

	//Hand
	PRC<CardMission> m_mission;
	QList<PRC<CardTerritory> > m_territoryHand;
	QList<PRC<CardEvent> > m_eventHand;
};

}

#endif // CIVILIZATION_H
