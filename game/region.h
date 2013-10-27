#ifndef REGION_H
#define REGION_H

#include <QString>
#include <QList>

namespace ksir {

class Territory;

class Region
{
public:
	Region(const QString& p_name);

	const QList<const Territory*>& territoryList();

	bool addTerritory(const Territory* p_territory);

	unsigned int reinforcement();

private:
	QString m_name;
	unsigned int m_reinforcement;
	bool m_reinforcementComputed;

	QList<const Territory*> m_territoryList;
};

}

#endif // REGION_H
