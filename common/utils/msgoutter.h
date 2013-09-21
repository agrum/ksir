#ifndef KMSGOUTTER_H
#define KMSGOUTTER_H

#include "msg.h"

namespace ksir {

class MsgOutter : public Msg
{
public:
	MsgOutter(const QString& p_name, Type p_type);
	MsgOutter(const QDomNode& p_node);
	MsgOutter(const MsgOutter& p_msg);
	~MsgOutter();
	MsgOutter& operator=(const MsgOutter& p_msg);

	//Operation
	void add(const QString& p_tag, const PRC<XmlBehavior>& p_entity);
	void get(const QString& p_tag, PRC<XmlBehavior>& p_entity);
	bool exist(const QString& p_tag);

private:
	//XML
	void writeXml(QDomNode& p_node) const;

private:
	QDomDocument m_doc;
};

}

#endif // KMSGOUTTER_H
