#ifndef KMSG_H
#define KMSG_H

#include <QString>
#include <QByteArray>

#include "../utils/kxmlbehavior.h"
#include "../utils/kprc.h"

class kMsg : public kXmlBehavior
{
public :
	enum Type{
		NONE,
		INFO, //Casual information transition between systems
		RPRT, //Meant to stay in the same system
		RQST, //Meant to ask for something
		ANSW //Meant to answer a request
	};

	kMsg(const QString& p_name, Type p_type);
	kMsg(const QDomNode& p_node);
	kMsg(const kMsg& p_msg);
	virtual ~kMsg();

	//Get
	int id() const { return m_id; }
	const QString& name() const { return m_name; }
	Type type() const { return m_type; }

	//Operation
	virtual void add(const QString& p_tag, const kPRC<kXmlBehavior>& p_entity) = 0;
	virtual void get(const QString& p_tag, kPRC<kXmlBehavior>& p_entity) = 0;
	virtual bool exist(const QString& p_tag) = 0;

private:
	kMsg& operator=(const kMsg&) {}

	//XML (never create content out of a node, except for the attributes)
	void from(const QDomNode&) {}
	void readXml(const QDomNode&, const QString&) {}

private:
	static unsigned int m_idCount;
	static QMutex m_mutex;

	unsigned int m_id;
	QString m_name;
	Type m_type;

	//QMap<QString, kPRC<kXmlBehavior> > m_entityMap;
};


#endif // ____KMSG_H____
