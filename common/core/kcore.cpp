#include "kcore.h"

kCore::kCore()
{

}

kCore::kCore(const QString& p_id, const QString& p_type):
	m_id(p_id),
	m_type(p_type)
{

}

kCore::kCore(const kCore& p_core):
	m_id(p_core.m_id),
	m_type(p_core.m_type)
{

}

kCore& kCore::operator=(const kCore& p_core)
{
	m_id = p_core.m_id;
	m_type = p_core.m_type;

	return *this;
}

bool kCore::operator==(const kCore& p_core) const
{
	return (m_id == p_core.m_id && m_type == p_core.m_type);
}

void kCore::readXml(const QDomNode& p_root)
{
	QDomNode n = p_root.firstChild();
	while (!n.isNull()){
		if (n.isElement()){
			QDomElement e = n.toElement();
			if( e.tagName() == XML_ID )
				m_id = e.text();
			else if( e.tagName() == XML_TYPE )
				m_type = e.text();
		}
		n = n.nextSibling();
	}
}

void kCore::writeXml(QDomNode& p_root, const QString& p_name)
{
	QDomDocument doc = p_root.toDocument();
	QDomElement tag = doc.createElement(p_name);

	addToElement(tag, XML_ID, m_id);
	addToElement(tag, XML_TYPE, m_type);

	p_root.appendChild(tag);
}
