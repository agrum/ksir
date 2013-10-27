#ifndef CARDTERRITORY_H
#define CARDTERRITORY_H

namespace ksir {

class CardTerritory
{
public:
	enum ComboElement {
		LIGHT = 1,
		MEDIUM = 2,
		HEAVY = 4,
		JOKER = 7
	};

	CardTerritory();
};

}

#endif // CARDTERRITORY_H
