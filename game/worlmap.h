#ifndef WORLMAP_H
#define WORLMAP_H

#include "ksir_common.h"

#include "territory.h"

namespace ksir {

class WorlMap
{
public:
	WorlMap();

private:
	QList<Territory*> m_pTerritoryList;
};

}

#endif // WORLMAP_H
