#ifndef KXMLBEHAVIOR_H
#define KXMLBEHAVIOR_H

///Since the communication inside and outside the project uses the Msg class,
///the instances given to the messages must be able to convert themself to
///and from XML content.
///Any class inheriting from XmlBehavior tells the user this class can convert
///or initiate itself.
///XmlBehavior can t exist by itself, it must be inherited and implement a
///constructor.

#include <QtXml>

#include <pomelog.h>

namespace ksir {

class XmlBehavior : public pLogBehavior
{
public:
	XmlBehavior() {}
	~XmlBehavior() {}
	//Operation
	void from(const QDomNode& p_node);
	void to(QDomNode& p_node, const QString& p_name) const;

protected :
	//Lifetime
	XmlBehavior(const QString& p_sign);

	virtual void readXml(const QDomNode&, const QString&) {}
	virtual void writeXml(QDomNode&) const {}

	//Get
	QString getAttribute(const QDomNode& p_node, const QString& p_name) const;
	QString getText(const QDomNode& p_node) const;

	//Operation
	void addAttribute(QDomNode& p_node, const QString& p_name, const QString& p_value) const;
	void addText(QDomNode& p_node, const QString& p_text) const;

private:
	//Operation
	void readFile(const QString&);

private:
	bool m_initialized;
};

}

#endif // KXMLBEHAVIOR_H
