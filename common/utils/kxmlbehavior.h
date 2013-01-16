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
#define XML_PORT "port"
#define XML_SERVER "server"
#define XML_CLIENT "client"
#define XML_DATABASE "database"

class kXmlBehavior
{
public:
	void from(const QDomNode&);
	void to(QDomNode&, const QString&);

protected :
	kXmlBehavior() {}

	virtual void readXml(const QString&, const QDomElement&) = 0;
	virtual void writeXml(QDomNode&) = 0;

	void addToElement(QDomNode&, const QString&, const QString&);
	void addToElement(QDomNode&, const QString, const double);
	void addToElement(QDomNode&, const QString, const unsigned int);
	void addToElement(QDomNode&, const QString, const int);
	void addToElement(QDomNode&, const QString, const qint64);
	void addToElement(QDomNode&, const QString, const bool);

private:
	void readFile(const QString&);
};
