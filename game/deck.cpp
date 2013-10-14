#include "deck.h"

#include <QtGlobal>

Deck::Deck(const QList<PRC<Card> >& p_set):
	m_stack(p_set)
{

}

PRC<Card>
Deck::drawCard()
{
	if(m_stack.empty())
	{
		m_stack = m_discard;
		m_discard.clear();
	}

	return m_stack.takeFirst();
}

void
Deck::discardCard(PRC<Card> p_card)
{
	m_discard.insert(m_discard.begin() + (qrand()%m_discard.size()), p_card);
}
