#include "kxmlbehavior.h"

#include <assert.h>

void kXmlBehavior::from(const QDomNode& p_root)
{
	if(m_initialized == true)
		logE("Already initialized from XML content");

	QDomNode n = p_root.firstChild();
	while (!n.isNull()){
		if (n.isElement()){
			QDomElement e = n.toElement();
			if(e.tagName() == XML_FILE)
				readFile(e.text());
			else
				readXml(n, e.tagName());
		}
		n = n.nextSibling();
	}

	m_initialized = true;
}

void kXmlBehavior::to(QDomNode& p_node, const QString& p_name)
{
	if(p_node.firstChild().nodeType() == QDomNode::TextNode)
	   logE("Can't create a child to a node with text");

	QDomElement child = p_node.ownerDocument().createElement(p_name);

	p_node.appendChild(child);

	writeXml(child);
}

void kXmlBehavior::readFile(const QString& p_filename)
{
	QFile file(p_filename);

	if(file.exists() && file.open(QIODevice::ReadOnly)){
		QDomDocument config;
		if(config.setContent(&file, true))
			from(config.firstChild());
		else
			logE("kXmlBehavior::readFile() : parsing error " + p_filename);
		file.close();
	}
	else
		logE("kXmlBehavior::readFile() : can't open " + p_filename);
}

const QString
kXmlBehavior::getAttribute(const QDomNode& p_node, const QString& p_attribute) const
{
	return p_node.toElement().attribute(p_attribute);
}

const QString
kXmlBehavior::getText(const QDomNode& p_node) const
{
	return p_node.toElement().text();
}

void
kXmlBehavior::addAttribute(QDomNode& p_node, const QString& p_attribute, const QString& p_value)
{
	p_node.toElement().setAttribute(
		QString::fromStdString(p_attribute),
		QString::fromStdString(p_value));
}

void
kXmlBehavior::addText(QDomNode& p_node, const QString& p_value)
{
	if(m_cursor.hasChildNodes())
		logE("Try to add text to a node with children");

	p_node.appendChild(p_node.ownerDocument().createTextNode(p_value));
}
