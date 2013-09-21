#include "xmlbehavior.h"

#include <assert.h>

using namespace ksir;

XmlBehavior::XmlBehavior(const QString& p_sign) :
	pLogBehavior(p_sign),
	m_initialized(false)
{

}

void XmlBehavior::from(const QDomNode& p_root)
{
	if(m_initialized == true)
		logE("Already initialized from XML content");

	QDomNode n = p_root.firstChild();
	while (!n.isNull()){
		if (n.isElement()){
			QDomElement e = n.toElement();
			if(e.tagName() == "xmlAddFile")
				readFile(e.text());
			else
				readXml(n, e.tagName());
		}
		n = n.nextSibling();
	}

	m_initialized = true;
}

void XmlBehavior::to(QDomNode& p_node, const QString& p_name) const
{
	if(p_node.firstChild().nodeType() == QDomNode::TextNode)
	   logE("Can't create a child to a node with text");

	QDomElement child = p_node.ownerDocument().createElement(p_name);

	p_node.appendChild(child);

	writeXml(child);
}

void XmlBehavior::readFile(const QString& p_filename)
{
	QFile file(p_filename);

	if(file.exists() && file.open(QIODevice::ReadOnly)){
		QDomDocument config;
		if(config.setContent(&file, true))
			from(config.firstChild());
		else
			logE("XmlBehavior::readFile() : parsing error " + p_filename);
		file.close();
	}
	else
		logE("XmlBehavior::readFile() : can't open " + p_filename);
}

const QString
XmlBehavior::getAttribute(const QDomNode& p_node, const QString& p_attribute) const
{
	return p_node.toElement().attribute(p_attribute);
}

const QString
XmlBehavior::getText(const QDomNode& p_node) const
{
	return p_node.toElement().text();
}

void
XmlBehavior::addAttribute(QDomNode& p_node, const QString& p_attribute, const QString& p_value) const
{
	p_node.toElement().setAttribute(p_attribute, p_value);
}

void
XmlBehavior::addText(QDomNode& p_node, const QString& p_value) const
{
	if(p_node.hasChildNodes())
		logE("Try to add text to a node with children");

	p_node.appendChild(p_node.ownerDocument().createTextNode(p_value));
}
