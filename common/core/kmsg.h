/*!
 * \file Commandes/CCommand.h
 *
 */
#ifndef KMSG_H
#define KMSG_H

#include <QtCore>
#include <QtXml>
#include <QTime>

#include "kmsgheader.h"

class kMsg
{
public :
	kMsg();
	kMsg(const QString&, kMsgHeader::Type);
	kMsg(const QString&, kMsgHeader::Type, const kCore&);
	kMsg(const kMsg&);
	kMsg(const QByteArray&);
	kMsg& operator=(const kMsg&);

	bool outdated();

	const QString name() const { return m_info.localName(); }
	kMsgHeader& header() { return m_header; }
	QDomNode& dom() { return m_info; }
	QDomNode node(const QString& p_node) { return m_info.firstChildElement(p_node); }
	QString text(const QString& p_node) { return m_info.firstChildElement(p_node).text(); }
	void add(const QString&, const QString&);

	bool operator==(const kMsg&);
	bool is(const QString&, const kMsgHeader::Type);
	bool exist(const QString&);
	bool find(const QString&, QDomNode&);
	QByteArray toMsg();
	QString print(QString);

protected :
	QTime m_time;
	QDomDocument m_info;
	kMsgHeader m_header;

	QByteArray m_content;
};


#endif // ____KMSG_H____
