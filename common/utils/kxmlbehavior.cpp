#include "kxmlbehavior.h"

void kXmlBehavior::from(const QDomNode& p_root)
{
	QDomNode n = p_root.firstChild();
	while (!n.isNull()){
		if (n.isElement()){
			QDomElement e = n.toElement();
			if(e.tagName() == XML_FILE)
				readFile(e.text());
			else
				readXml(e.tagName(), e);
		}
		n = n.nextSibling();
	}
}

void kXmlBehavior::to(QDomNode& p_root, const QString& p_name)
{
	QDomDocument doc = p_root.toDocument();
	QDomElement tag = doc.createElement(p_name);

	writeXml(tag);

	p_root.appendChild(tag);
}

void kXmlBehavior::readFile(const QString& p_filename)
{
	QFile file(p_filename);

	if(file.exists() && file.open(QIODevice::ReadOnly)){
		QDomDocument config;
		if(config.setContent(&file, true))
			from(config.firstChild());
		file.close();
	}
}

void kXmlBehavior::addToElement(QDomNode& p_root, const QString& p_tag , const QString& p_value)
{
	QDomDocument doc = p_root.toDocument();
	QDomNode tag = doc.createElement(p_tag);
	QDomText t = doc.createTextNode(p_value);

	tag.appendChild(t);
	p_root.appendChild(tag);
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const double p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value));
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const unsigned int p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value));
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const int p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value));
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const qint64 p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value));
}

void kXmlBehavior::addToElement(QDomNode & p_root, const QString p_tag , const bool p_value)
{
	addToElement(p_root, p_tag, QString().setNum(p_value ? 1 : 0));
}
