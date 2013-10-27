#include "territorylink.h"

#include "territory.h"

using namespace ksir;

TerritoryLink::TerritoryLink(
		Territory* p_a,
		Territory* p_b,
		LinkType p_type):
	m_a(p_a),
	m_b(p_b),
	m_type(p_type)
{

}

TerritoryLink::TerritoryLink(const TerritoryLink& p_link):
	m_a(p_link.m_a),
	m_b(p_link.m_b),
	m_type(p_link.m_type)
{

}

TerritoryLink::~TerritoryLink()
{

}

TerritoryLink&
TerritoryLink::operator=(const TerritoryLink& p_link)
{
	m_a = p_link.m_a;
	m_b = p_link.m_b;
	m_link = p_link.m_link;
}

Territory*
TerritoryLink::opposite(Territory* p_c)
{
	return (p_c == p_a) ? p_b : p_a;
}

LinkType
TerritoryLink::type()
{
	return m_type;
}
