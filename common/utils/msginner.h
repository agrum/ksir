#ifndef KMSGINNER_H
#define KMSGINNER_H

#include <QMap>

#include "msg.h"

namespace ksir {

class MsgInner : public Msg
{
public:
	MsgInner(const QString& p_name, Type p_type);
	MsgInner(const MsgInner& p_msg);
	~MsgInner();
	MsgInner& operator=(const MsgInner& p_msg);

	//Operation
	void add(const QString& p_tag, const PRC<XmlBehavior>& p_entity);
	void get(const QString& p_tag, PRC<XmlBehavior>& p_entity);
	bool exist(const QString& p_tag);

private:
	//XML
	void readXml(const QDomNode&, const QString&) {}
	void writeXml(QDomNode& p_node) const;

private:
	QMap<QString, PRC<XmlBehavior> > m_map;
};

}

#endif // KMSGINNER_H
