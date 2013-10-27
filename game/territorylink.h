#ifndef TERRITORYLINK_H
#define TERRITORYLINK_H

namespace ksir {

class Territory;

class TerritoryLink
{
public:
	enum LinkType {
		Normal,
		Sea,
		Mountain
	};

	TerritoryLink(Territory*, Territory*, LinkType);
	TerritoryLink(const TerritoryLink&);
	~TerritoryLink();
	TerritoryLink& operator=(const TerritoryLink&);

	Territory* opposite(const Territory*);
	const Territory* opposite(const Territory*) const;
	LinkType type();

private:
	Territory* m_a;
	Territory* m_b;
	LinkType m_type;
};

}

#endif // TERRITORYLINK_H
