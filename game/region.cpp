#include "region.h"

#include "territory.h"
#include "territorylink.h"

using namespace ksir;

Region::Region(const QString& p_name):
	m_name(p_name),
	m_reinforcementComputed(false)
{

}

const QList<const Territory*>&
Region::territoryList()
{
	return m_territoryList;
}

bool
Region::addTerritory(const Territory* p_territory)
{
	if(m_territoryList.contains(p_territory))
		return true;
	if(p_territory->m_region != NULL)
		return false;

	m_territoryList.push_back(p_territory);
	m_reinforcementComputed = false;
	return true;
}

unsigned int
Region::reinforcement()
{
	if(m_reinforcementComputed)
		return m_reinforcement;

	//QVector<QPair<const PRC<Territory>, BoudaryType> > m_territoryLinkList;
	float reinforcementF = 0;
	QList<const Territory*>::Iterator terriIte;
	QList<TerritoryLink>::ConstIterator linkIte;

	//Group reinforcement
	reinforcementF += 0.35 * m_territoryList.size();

	//Gate reinforcement
	for(terriIte = m_territoryList.begin();
		terriIte != m_territoryList.end();
		terriIte++)
	{
		for(linkIte = (*terriIte)->m_territoryLinkList.begin();
			linkIte != (*terriIte)->m_territoryLinkList.end();
			linkIte++)
		{
			if(!m_territoryList.contains((*linkIte).opposite(*terriIte)))
				reinforcementF += 0.9;
		}
	}

	m_reinforcement = (unsigned int) reinforcementF;
	m_reinforcementComputed = true;

	return m_reinforcement;
}
