#ifndef KMSG_H
#define KMSG_H

///Key class of the project. The message supposedly can hold anything
///Consider the Msg class paired with the ComLinks as an elaborate
///event system.
///The message is the event while the ComLink is the mean used to
///transfer the event.

#include <QString>
#include <QMutex>
#include <QWaitCondition>

#include "xmlbehavior.h"
#include "prc.h"

namespace ksir {

class Msg : public XmlBehavior
{
public :
	enum Type{
		NONE,
		INFO, //Casual information transition between systems
		RPRT //Meant to stay in the same system, can block a thrad by calling waitForAck()
	};

	//Lifetime
	Msg(const QString& p_name, Type p_type);
	Msg(const QDomNode& p_node);
	Msg(const Msg& p_msg);
	~Msg();
	Msg& operator=(const Msg&);

	//Get
	int id() const { return m_id; }
	const QString& name() const { return m_name; }
	Type type() const { return m_type; }

	//Operation
	virtual void add(const QString& p_tag, const PRC<XmlBehavior> p_entity);
	virtual void get(const QString& p_tag, XmlBehavior* p_entity);
	virtual bool exist(const QString& p_tag);

	void waitForAck();
	void ack();

private:
	//XML
	void writeXml(QDomNode& p_node) const;

protected:
	static unsigned int s_idCount;
	static QMutex s_mutex;

	unsigned int m_id;
	QString m_name;
	Type m_type;
	QDomDocument m_doc;

	QMutex m_mutex;
	QWaitCondition m_reportWaitCondition;
};

}

#endif // ____KMSG_H____
