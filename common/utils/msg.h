#ifndef KMSG_H
#define KMSG_H

#include <QString>

#include "xmlbehavior.h"
#include "prc.h"

namespace ksir {

class Msg : public XmlBehavior
{
public :
	enum Type{
		NONE,
		INFO, //Casual information transition between systems
		RPRT, //Meant to stay in the same system
		RQST, //Meant to ask for something
		ANSW //Meant to answer a request
	};

	Msg(const QString& p_name, Type p_type);
	Msg(const QDomNode& p_node);
	Msg(const Msg& p_msg);
	virtual ~Msg();

	//Get
	int id() const { return m_id; }
	const QString& name() const { return m_name; }
	Type type() const { return m_type; }

	//Operation
	virtual void add(const QString& p_tag, const PRC<XmlBehavior>& p_entity) = 0;
	virtual void get(const QString& p_tag, PRC<XmlBehavior>& p_entity) = 0;
	virtual bool exist(const QString& p_tag) = 0;

protected:
	Msg& operator=(const Msg&) { return *this; }

	//XML (never create content out of a node, except for the attributes)
	void from(const QDomNode&) {}
	void readXml(const QDomNode&, const QString&) {}

protected:
	static unsigned int m_idCount;
	static QMutex m_mutex;

	unsigned int m_id;
	QString m_name;
	Type m_type;

	//QMap<QString, PRC<XmlBehavior> > m_entityMap;
};

}

#endif // ____KMSG_H____
