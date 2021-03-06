#ifndef STRING_H
#define STRING_H

///This string class is a simple extension of QString.
///It only adds the XmlBehaviour, enabling it to be pushed inside messages

#include <QString>

#include "xmlbehavior.h"

namespace ksir {

class String : public QString, public XmlBehavior
{
public:
	//Lifetime
	String();
	String(const QChar * unicode, int size = -1);
	String(QChar ch);
	String(int size, QChar ch);
	String(QLatin1String str);
	String(const QString& other);
	String(const String& other);
	String(const char * str);
	String(const QByteArray & ba);
	String(QStringDataPtr dd);
	~String();
	String& operator=(const String&);

	//XML
	void readXml(const QDomNode& p_node, const QString&);
	void writeXml(QDomNode& p_node) const;
};

}

#endif // STRING_H
