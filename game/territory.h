#ifndef TERRITORY_H
#define TERRITORY_H

#include "ksir_common.h"

#include "region.h"

namespace ksir {

class Territory
{
public:
	Territory();

private:
	PRC<Region> m_pRegion;
};

}

#endif // TERRITORY_H
