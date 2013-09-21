#ifndef KMSGOUTTER_H
#define KMSGOUTTER_H

#include "kmsg.h"

class kMsgOutter : public kMsg
{
public:
	kMsgOutter(const QString& p_name, Type p_type);
	kMsgOutter(const QDomNode& p_node);
	kMsgOutter(const kMsgOutter& p_msg);
	~kMsgOutter();
	kMsgOutter& operator=(const kMsgOutter& p_msg);

	//Operation
	void add(const QString& p_tag, const kPRC<kXmlBehavior>& p_entity);
	void get(const QString& p_tag, kPRC<kXmlBehavior>& p_entity);
	bool exist(const QString& p_tag);

private:
	//XML
	void writeXml(QDomNode& p_node);

private:
	QDomDocument m_doc;
};

#endif // KMSGOUTTER_H
