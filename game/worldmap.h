#ifndef WORLDMAP_H
#define WORLDMAP_H

#include "ksir_common.h"

#include "territory.h"

namespace ksir {

class WorldMap
{
public:
	WorldMap();

	QList<Region*>& regionList(){ return m_regionList; }
	QList<Territory*>& territoryList(){ return m_territoryList; }

private:
	QList<Region*> m_regionList; //Originals
	QList<Territory*> m_territoryList; //Originals
};

}

#endif // WORLDMAP_H
