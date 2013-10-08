#include "xmlbehavior.h"

#include <assert.h>

using namespace ksir;

/* $Desc Construct itself and sign up with the logger.
 * $Parm p_sign Signature used  for logging.
 * $Rtrn /.
 */
void XmlBehavior::from(const QDomNode& p_root)
{
	if(m_initialized == true)
		logE("Already initialized from XML content");

	readXml(p_root, p_root.toElement().tagName());

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

/* $Desc Convert the object to an XML node. The node provided
 * $Parm p_sign Signature used  for logging.
 * $Rtrn /.
 */
void XmlBehavior::to(QDomNode& p_node, const QString& p_name) const
{
	if(p_node.firstChild().nodeType() == QDomNode::TextNode)
	   logE("Can't create a child to a node with text");

	QDomElement child = p_node.ownerDocument().createElement(p_name);

	p_node.appendChild(child);

	writeXml(child);
}

/* $Desc Construct itself and sign up with the logger.
 * $Parm p_sign Signature used  for logging.
 * $Rtrn /.
 */
XmlBehavior::XmlBehavior(const QString& p_sign) :
	pLogBehavior(p_sign),
	m_initialized(false)
{

}

/* $Desc Return the desired attribute from the node itself.
 *	Nothing if the attribute doesn t exist.
 * $Parm p_node Node holding the attribute desired.
 * $Parm p_attribute Name of the attribute researched.
 * $Rtrn Value of the attribute as a string.
 */
QString
XmlBehavior::getAttribute(const QDomNode& p_node, const QString& p_attribute) const
{
	return p_node.toElement().attribute(p_attribute);
}

/* $Desc Return the content of the node if any.
 * $Parm p_node Node holding the information desired.
 * $Rtrn Content of the node as a string.
 */
QString
XmlBehavior::getText(const QDomNode& p_node) const
{
	return p_node.toElement().text();
}

/* $Desc Add an attribute to the node. If it already exists, it s
 *	over written.
 * $Parm p_node Node on which to write.
 * $Parm p_attribute name of the attribute to write.
 * $Parm p_value Value to give to the attribute.
 * $Rtrn /.
 */
void
XmlBehavior::addAttribute(QDomNode& p_node, const QString& p_attribute, const QString& p_value) const
{
	p_node.toElement().setAttribute(p_attribute, p_value);
}

/* $Desc Add text inside the node s markups. If any already exists, it s
 *	over written.
 * $Parm p_node Node on which to write.
 * $Parm p_value Text to fill in.
 * $Rtrn /.
 */
void
XmlBehavior::addText(QDomNode& p_node, const QString& p_value) const
{
	if(p_node.hasChildNodes())
		logE("Try to add text to a node with children");

	p_node.appendChild(p_node.ownerDocument().createTextNode(p_value));
}

/* $Desc Extend research for configuration file by building
 *	new document from file pathes. Thos edocuments are then
 *	read as the original was.
 * $Parm p_filename path to the file to read.
 * $Rtrn /.
 */
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
