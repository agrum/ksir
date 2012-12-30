/*!
 * \file Commandes/kMsg.cpp
 *
 */
#include "kmsg.h"

kMsg::kMsg(const QString& p_name, kMsgHeader::Type p_type, const kCore& p_receiver) :
	m_info(p_name),
	m_header(p_type, p_receiver)
{

}

kMsg::kMsg(const kMsg& p_info) :
	m_info(p_info.m_info),
	m_header(p_info.m_header)
{

}

kMsg::kMsg(const QByteArray& p_buffer){
	m_info.setContent(p_buffer);
	m_header.from(m_info.firstChildElement("Header"));
}

kMsg& kMsg::operator=(const kMsg& p_info){
	m_info = p_info.m_info;
	m_header = p_info.m_header;

	return *this;
}


bool kMsg::exist(const QString& p_tag){
	for (QDomNode n = m_info.firstChild(); !n.isNull(); n = n.nextSibling())
		if (n.localName() == p_tag)
			return true;
	return false;
}

bool kMsg::find(const QString& p_tag, QDomNode& p_node){
	for (QDomNode n = m_info.firstChild(); !n.isNull(); n = n.nextSibling()){
		if (n.localName() == p_tag){
			p_node = n;
			return true;
		}
	}
	return false;
}

QByteArray kMsg::toMsg(){
	QDomDocument rtn(m_info);
	m_header.to(rtn, "Header");
	return rtn.toByteArray();
}

QString kMsg::print(QString p_blank )
{
	QString Result = p_blank + "kMsg\n";
	p_blank += " ";
	Result += p_blank + "name : " + name() + "\n";
	Result += m_header.print(p_blank);

	return Result;
}

void kMsg::add(const QString& p_name, const QString& p_content){
	QDomNode tag = m_info.createElement(p_name);
	QDomText t = m_info.createTextNode(p_content);

	tag.appendChild(t);
	m_info.appendChild(tag);
}
