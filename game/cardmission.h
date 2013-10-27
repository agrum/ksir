#ifndef CARDMISSION_H
#define CARDMISSION_H

#include "ksir_common.h"
#include "pomelog.h"

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
