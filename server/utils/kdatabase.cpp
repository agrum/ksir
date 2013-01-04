#include "kdatabase.h"

kDatabase::kDatabase()
{
	*(QSqlDatabase*) this = QSqlDatabase::addDatabase("QMYSQL");
}

void kDatabase::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if( p_tag == "host" )
		setHostName(p_node.text());
	else if( p_tag == "dbname" )
		setDatabaseName(p_node.text());
	else if( p_tag == "user" )
		setUserName(p_node.text());
	else if( p_tag == "password" )
		setPassword(p_node.text());
}
