#ifndef CARDMISSION_H
#define CARDMISSION_H

namespace ksir {

class CardMission
{
public:
	enum MissionSpec {
		TERRITORY_CAP,
		REGION_GATHERING,
		CIVILIZATION_ANNHILATION
	};

	CardMission();
};

}

#endif // CARDMISSION_H
