#ifndef KXMLBEHAVIOR_H
#define KXMLBEHAVIOR_H

#include <QtXml>

#include <pomelog.h>

namespace ksir {

class XmlBehavior : public pLogBehavior
{
public:
	virtual void from(const QDomNode& p_node);
	virtual void to(QDomNode& p_node, const QString& p_name) const;

protected :
	XmlBehavior(const QString& p_sign);

	virtual void readXml(const QDomNode& p_node, const QString& p_name) = 0;
	virtual void writeXml(QDomNode& p_node) const = 0;

	//----- Gets -----
	const QString getAttribute(const QDomNode& p_node, const QString& p_name) const;
	const QString getText(const QDomNode& p_node) const;

	//----- Sets -----
	void addAttribute(QDomNode& p_node, const QString& p_name, const QString& p_value) const;
	void addText(QDomNode& p_node, const QString& p_text) const;

	QDomNode createNode(QDomNode& p_node, const QString& p_name) const;

private:
	void readFile(const QString&);

private:
	bool m_initialized;
};

}

#endif // KXMLBEHAVIOR_H
