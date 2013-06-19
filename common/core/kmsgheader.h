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
#include <QString>
#include <QMutex>

#include "kcore.h"

class kMsgHeader : public kXmlBehavior
{
public :
	enum Type{
		NONE,
		INFO, //Casual information transition between systems
		REP, //Meant to stay in the same system
		REQ, //Meant to ask for something
		ANS //Meant to answer a request
	};

	kMsgHeader();
	kMsgHeader(Type);
	kMsgHeader(const QDomNode&);
	kMsgHeader(Type, const kCore&);
	kMsgHeader(const kMsgHeader&);
	kMsgHeader& operator=(const kMsgHeader&);

	int id() const { return m_id; }
	Type type() const { return m_type; }
	const QString sender() const { return m_sender; }
	const QString receiver() const { return m_receiver; }

	inline void setSender(const QString& p_sender) { m_sender = p_sender; }

	//XML
	void readXml(const QString&, const QDomElement&);
	void writeXml(QDomNode&);

	QString print(QString);

private :
	static kCore m_core;
	static unsigned int m_idCount;
	static QMutex m_mutex;

	unsigned int m_id;
	Type m_type;
	QString m_sender;
	QString m_receiver;
};

#endif /* KMSGHEADER_H_ */
