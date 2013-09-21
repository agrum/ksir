#ifndef KMSGINNER_H
#define KMSGINNER_H

#include <QMap>

#include "kmsg.h"

class kMsgInner : public kMsg
{
public:
	kMsgInner(const QString& p_name, Type p_type);
	kMsgInner(const kMsgInner& p_msg);
	~kMsgInner();
	kMsgInner& operator=(const kMsgInner& p_msg);

	//Operation
	void add(const QString& p_tag, const kPRC<kXmlBehavior>& p_entity);
	void get(const QString& p_tag, kPRC<kXmlBehavior>& p_entity);
	bool exist(const QString& p_tag);

private:
	//XML
	void writeXml(QDomNode& p_node);

private:
	QMap<QString, kPRC<kXmlBehavior> > m_map;
};

#endif // KMSGINNER_H
