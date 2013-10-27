#ifndef TERRITORY_H
#define TERRITORY_H

#include <QString>
#include <QList>

namespace ksir {

class Region;
class TerritoryLink;

class Territory
{
public:
	Territory();

	friend class Region;

private:
	QList<TerritoryLink> m_territoryLinkList;
	Region* m_region;
};

}

#endif // TERRITORY_H
