/*
 * kMsgHeader.cpp
 *
 *  Created on: 16 déc. 2011
 *      Author: tle-guerroue
 */

#include "kmsgheader.h"

unsigned int kMsgHeader::m_idCount = 0;
QMutex kMsgHeader::m_mutex;

kMsgHeader::kMsgHeader()
{

}

kMsgHeader::kMsgHeader(Type p_type) :
	m_type(p_type)
{

}

kMsgHeader::kMsgHeader(const QDomNode& p_root)
{
	from(p_root);
}

kMsgHeader::kMsgHeader(Type p_type, const kCore& p_receiver) :
	m_type(p_type),
	m_receiver(p_receiver)
{
	m_mutex.lock();
	m_id = m_idCount++;
	m_mutex.unlock();
}

kMsgHeader::kMsgHeader(const kMsgHeader& p_header) :
	kXmlBehavior(),
	m_id(p_header.m_id),
	m_type(p_header.m_type),
	m_receiver(p_header.m_receiver)
{

}

kMsgHeader& kMsgHeader::operator=(const kMsgHeader& p_header){
	m_id = p_header.m_id;
	m_type = p_header.m_type;
	m_receiver = p_header.m_receiver;

	return *this;
}

void kMsgHeader::readXml(const QString& p_tag, const QDomElement& p_node){
	if(p_tag == XML_ID)
		m_id = p_node.text().toInt();
	else if(p_tag == XML_TYPE)
		m_type = (kMsgHeader::Type) p_node.text().toInt();
	else if(p_tag == XML_BOB)
		m_receiver.from(p_node);
}

void kMsgHeader::writeXml(QDomNode& p_tag){
	addToElement(p_tag, XML_ID, m_id);
	addToElement(p_tag, XML_TYPE, m_type);
	m_receiver.to(p_tag, XML_BOB);
}

QString kMsgHeader::print(QString p_blank){
	QString Result = p_blank + "kMsgHeader\n";

	p_blank += " ";
	Result += p_blank + "type : " + m_type + "\n";
	Result += p_blank + "msgId : " + QString("%1").arg(m_id) + "\n";
	Result += p_blank + "receiver : " + m_receiver.type() + "\n";
	Result += p_blank + "receiverId : " + m_receiver.id() + "\n";

	return Result;
}
