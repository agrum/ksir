#include "kserver.h"

kServer::kServer(QFile& p_confFile)
{
	QDomDocument doc;

	doc.setContent(&p_confFile);
}

void kServer::run()
{

}

//XML
void kServer::readXml(const QDomNode&)
{

}

void kServer::writeXml(QDomNode&, QString)
{

}
