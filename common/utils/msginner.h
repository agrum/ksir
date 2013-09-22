#ifndef KMSGINNER_H
#define KMSGINNER_H

///Inherits from the abstract Msg class. This kind of message is
///dedicated for communication inside the program.
///This class actually holds ina  map the PRC provided.
///The PRC provided as input and output are not copied.
///It s the user concern to know whether the entity should be copied
///before transfer or if the correspondant should share the same instance.

#include <QMap>

#include "msg.h"

namespace ksir {

class MsgInner : public Msg
{
public:
	//Lifetime
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
	void writeXml(QDomNode& p_node) const;

private:
	QMap<QString, PRC<XmlBehavior> > m_map;
};

}

#endif // KMSGINNER_H
