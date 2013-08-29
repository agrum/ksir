#include "kclient.h"

kClient::kClient(const QDomNode& p_root):
	kCore(p_root),
	pLogBehavior("kClient"),
	m_currentServer(NULL),
	m_uiMngr(*(kQueueW*) &m_queue)
{
	from(p_root);
	if(m_serverList.empty())
		abort();
	for(int i = 0; i < m_serverList.size(); i++)
		m_serverList.at(i)->start();
	//m_currentServer = m_serverList.first();

	start();
}

kClient::~kClient()
{

}

void kClient::run()
{
	int err = 0;

	while(!err){
		manageQueue();

		if(m_currentServer){
			QList<kMsg> msgList = m_currentServer->getMsg();
			while(!msgList.empty()){
				kMsg tmp = msgList.takeFirst();
				if(tmp.is("gotYourName", kMsgHeader::INFO)){ //Name client
					m_id = tmp.header().receiver();
					logI(pLog::INFO_NONE, "name set : " + m_id);
				}
			}
		}

		msleep(100);
	}
}

//XML
void kClient::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if(p_tag == XML_SERVER){
		kDistant* tmp = new kDistant(p_node, *(kQueueW*) &m_queue);
		m_serverList.push_back(tmp);
	}
}

void kClient::manageQueue()
{
	kMsg tmp;

	while(m_queue.pop(tmp)){
		if(tmp.is(MSG_DISC_SOCK, kMsgHeader::REP)){
			m_uiMngr.queue().push(tmp);
		}
		else if(tmp.is(MSG_CONN_SOCK, kMsgHeader::REP)){
			m_uiMngr.queue().push(tmp);
		}
	}
}
