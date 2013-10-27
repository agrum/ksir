#ifndef CARDEVENT_H
#define CARDEVENT_H

namespace ksir {

class CardEvent
{
public:
	enum EventEffect {
		MOVEMENT_LIMIT,
		HERO_ADDITION,
		TERRITORY_REINFORCEMENT,
		TERRITORY_LOCKING,
		QUEST_REINFORCEMENT,
		ATTACK_BALANCE,
		DEFENSE_BALANCE
	};

	CardEvent();
};

}

#endif // CARDEVENT_H
