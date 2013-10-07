#include "kclient.h"

using namespace ksir;

kClient::kClient(const QDomNode& p_root):
	XmlBehavior("kClient"),
	m_currentServer(NULL)
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

}

//XML
void kClient::readXml(const QDomNode& p_node, const QString& p_tag)
{
	if(p_tag == "XML_SERVER"){
		Distant* tmp = new Distant(p_node);
		m_serverList.push_back(tmp);
	}
}
