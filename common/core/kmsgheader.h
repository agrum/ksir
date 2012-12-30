/*
 * kMsgHeader.h
 *
 *  Created on: 16 déc. 2011
 *      Author: tle-guerroue
 */

#ifndef KMSGHEADER_H_
#define KMSGHEADER_H_

#include <QtCore>
#include <QtXml>
#include <QMutex>

#include "kcore.h"

class kMsgHeader : public kXmlBehavior
{
public :
	enum Type{
		NONE,
		INFO,
		REQ,
		ANS
	};

	kMsgHeader();
	kMsgHeader(const QDomNode&);
	kMsgHeader(Type, const kCore&);
	kMsgHeader(const kMsgHeader&);
	kMsgHeader& operator=(const kMsgHeader&);

	Type type() const { return m_type; }
	const kCore receiver() const { return m_receiver; }
	int id() const { return m_id; }

	//XML
	void readXml(const QString&, const QDomElement&);
	void writeXml(QDomNode&, const QString&);

	QString print(QString);

private :
	static unsigned int m_idCount;
	static QMutex m_mutex;

	unsigned int m_id;
	Type m_type;
	kCore m_receiver;
};

#endif /* KMSGHEADER_H_ */
