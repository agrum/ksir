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
	m_type = p_link.m_type;

	return *this;
}

Territory*
TerritoryLink::opposite(const Territory* p_c)
{
	return (p_c == m_a) ? m_b : m_a;
}

const Territory*
TerritoryLink::opposite(const Territory* p_c) const
{
	return (p_c == m_a) ? m_b : m_a;
}

TerritoryLink::LinkType
TerritoryLink::type()
{
	return m_type;
}
