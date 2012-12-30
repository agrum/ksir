#include "kxmlbehavior.h"

void kXmlBehavior::addToElement(QDomNode& p_root, const QString& p_tag , const QString& p_value)
{
	QDomDocument doc = p_root.toDocument();
	QDomNode tag = doc.createElement(p_tag);
	QDomText t = doc.createTextNode(p_value);

	tag.appendChild(t);
	p_root.appendChild(tag);
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const double p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value));
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const unsigned int p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value));
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const int p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value));
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const qint64 p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value));
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const bool p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value ? 1 : 0));
}
