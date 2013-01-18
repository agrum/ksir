#include "kclient.h"

kClient::kClient(const QDomNode& p_root):
	kCore(p_root),
	pLogBehavior("kClient"),
	m_currentServer(NULL)
{
	from(p_root);
	if(m_serverList.empty())
		abort();
	m_currentServer = m_serverList.first();
	m_currentServer->start();

	kMsgHeader::setSender(*(kCore*) this);

	start();
}

kClient::~kClient()
{

}

void kClient::run()
{
	int err = 0;

	while(!err){
		QList<kMsg> msgList = m_currentServer->getMsg();
		while(!msgList.empty()){
			kMsg tmp = msgList.takeFirst();
			if(tmp.is("gotYourName", kMsgHeader::INFO)){ //Name client
				m_id = tmp.header().receiver().id();
				logI(pLog::INFO_NONE, "name set : " + m_id);
			}
		}

		msleep(100);
	}
}

//XML
void kClient::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if(p_tag == XML_SERVER){
		kDistant* tmp = new kDistant(p_node);
		m_serverList.push_back(tmp);
	}
}
