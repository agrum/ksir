#include "string.h"

using namespace ksir;


//Lifetime

String::String() :
	QString(),
	XmlBehavior("String") {}
String::String(const QChar * unicode, int size) :
	QString(unicode, size),
	XmlBehavior("String") {}
String::String(QChar ch) :
	QString(ch),
	XmlBehavior("String") {}
String::String(int size, QChar ch) :
	QString(size, ch),
	XmlBehavior("String") {}
String::String(QLatin1String str) :
	QString(str),
	XmlBehavior("String") {}
String::String(const QString & other) :
	QString(other),
	XmlBehavior("String") {}
String::String(const String & other) :
	QString(other),
	XmlBehavior("String") {}
String::String(const char * str) :
	QString(str),
	XmlBehavior("String") {}
String::String(const QByteArray & ba) :
	QString(ba),
	XmlBehavior("String") {}
String::String(QStringDataPtr dd) :
	QString(dd),
	XmlBehavior("String") {}
String::~String() { /*((QString*) this)->~QString();*/ }

String&
String::operator=(const String& p_str)
{
	*(QString*)this = p_str;

	return *this;
}

//XML

void
String::readXml(const QDomNode& p_node, const QString&)
{
	*(QString*)this = getText(p_node);
}

void
String::writeXml(QDomNode& p_node) const
{
	addText(p_node, *this);
}
