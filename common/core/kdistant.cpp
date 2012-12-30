#include "kdistant.h"

kDistant::kDistant(QTcpSocket* p_socket):
	m_responsible(false),
	m_socket(p_socket)
{

}

kDistant::kDistant(const QDomNode& p_root):
	kCore(p_root),
	m_responsible(true)
{

}

kDistant::~kDistant()
{
	if(m_responsible)
		delete m_socket;
}

void kDistant::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if( p_tag == XML_ID )
		m_id = p_node.text();
	else if( p_tag == XML_TYPE )
		m_type = p_node.text();
	else if( p_tag == XML_ADDR )
		m_addr = p_node.text();
}

void kDistant::writeXml(QDomNode& p_tag)
{
	addToElement(p_tag, XML_ID, m_id);
	addToElement(p_tag, XML_TYPE, m_type);
	addToElement(p_tag, XML_ADDR, m_addr);
}
