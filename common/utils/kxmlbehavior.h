#ifndef KXMLBEHAVIOR_H
#define KXMLBEHAVIOR_H

#include <QtXml>

#include <pomelog.h>

class kXmlBehavior : public pLogBehavior
{
public:
	virtual void from(const QDomNode& p_node);
	virtual void to(QDomNode& p_node, const QString& p_name);

protected :
	kXmlBehavior(const QString& p_sign) : pLogBehavior(p_sign) {}

	virtual void readXml(const QDomNode& p_node, const QString& p_name) = 0;
	virtual void writeXml(QDomNode& p_node) = 0;

	//----- Gets -----
	const QString getAttribute(const QDomNode& p_node, const QString& p_name) const;
	const QString getText(const QDomNode& p_node) const;

	//----- Sets -----
	void addAttribute(QDomNode& p_node, const QString& p_name, const QString& p_value);
	void addText(QDomNode& p_node, const QString& p_text);

	QDomNode createNode(QDomNode& p_node, const QString& p_name);

private:
	void readFile(const QString&);
};

#endif // KXMLBEHAVIOR_H
