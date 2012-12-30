#include "kxmlbehavior.h"

void kXmlBehavior::setFrom(const QDomNode& p_root)
{
	QDomNode n = p_root.firstChild();
	while (!n.isNull()){
		if (n.isElement()){
			QDomElement e = n.toElement();
			readXml(e.tagName(), e);
			if(e.tagName() == XML_FILE)
				readFile(e.text());
			else
				readXml(e.tagName(), e);
		}
		n = n.nextSibling();
	}
}

void kXmlBehavior::readFile(const QString& p_filename)
{
	QFile lFile(p_filename);

	if(lFile.exists() && lFile.open(QIODevice::ReadOnly)){
		QDomDocument lConfig;
		if(lConfig.setContent(&lFile, true, NULL, NULL, NULL))
			setFrom(lConfig.documentElement());
		lFile.close();
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
