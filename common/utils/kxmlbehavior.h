#ifndef KXMLBEHAVIOR_H
#define KXMLBEHAVIOR_H

#endif // KXMLBEHAVIOR_H

#include <QtXml>

#define XML_NONE "none"
#define XML_ID "id"
#define XML_TYPE "type"
#define XML_ALICE "A"
#define XML_BOB "B"

class kXmlBehavior
{
protected :
	kXmlBehavior() {}

	virtual void readXml(const QDomNode&) = 0;
	virtual void writeXml(QDomNode&, const QString&) = 0;

	void addToElement(QDomNode&, const QString&, const QString&);
	void addToElement(QDomNode&, const QString, const double);
	void addToElement(QDomNode&, const QString, const unsigned int);
	void addToElement(QDomNode&, const QString, const int);
	void addToElement(QDomNode&, const QString, const qint64);
	void addToElement(QDomNode&, const QString, const bool);
};
