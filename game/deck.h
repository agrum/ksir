#ifndef DECK_H
#define DECK_H

#include <QList>

#include "ksir_common.h"

#include "card.h"

namespace ksir {

class Deck
{
public:
	Deck(const QList<PRC<Card> >&);

	PRC<Card> drawCard();
	void discardCard(PRC<Card>);

private:
	QList<PRC<Card> > m_stack;
	QList<PRC<Card> > m_discard;
};

}

#endif // DECK_H
