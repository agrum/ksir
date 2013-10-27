#ifndef DECK_H
#define DECK_H

#include <QList>

namespace ksir {

template<class T> class Deck
{
public:
	Deck();

	T drawCard();
	void discardCard(T);

private:
	QList<T> m_stack;
	QList<T> m_discard;
};

////////

template<class T> inline
Deck<T>::Deck()
{
}

template<class T> inline
T
Deck<T>::drawCard()
{
	if(m_stack.empty())
	{
		m_stack = m_discard;
		m_discard.clear();
	}

	return m_stack.takeFirst();
}

template<class T> inline
void
Deck<T>::discardCard(T p_card)
{
	m_discard.insert(m_discard.begin() + (qrand()%m_discard.size()), p_card);
}

}

#endif // DECK_H
