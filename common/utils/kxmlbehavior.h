#ifndef KXMLBEHAVIOR_H
#define KXMLBEHAVIOR_H

#endif // KXMLBEHAVIOR_H

#include <QtXml>

#define XML_NONE "none"
#define XML_ID "id"
#define XML_TYPE "type"
#define XML_ALICE "A"
#define XML_BOB "B"
#define XML_FILE "file"
#define XML_ADDR "address"
#define XML_SERVER "server"
#define XML_CLIENT "client"

class kXmlBehavior
{
public:
	void setFrom(const QDomNode&);

protected :
	kXmlBehavior() {}
	kXmlBehavior(const QDomNode& p) { setFrom(p); }

	virtual void readXml(const QString&, const QDomElement&) = 0;
	virtual void writeXml(QDomNode&, const QString&) = 0;

	void addToElement(QDomNode&, const QString&, const QString&);
	void addToElement(QDomNode&, const QString, const double);
	void addToElement(QDomNode&, const QString, const unsigned int);
	void addToElement(QDomNode&, const QString, const int);
	void addToElement(QDomNode&, const QString, const qint64);
	void addToElement(QDomNode&, const QString, const bool);

private:
	void readFile(const QString&);
};
