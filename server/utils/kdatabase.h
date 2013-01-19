#ifndef KDATABASE_H
#define KDATABASE_H

#include <QTextStream>
#include <QString>
#include <QSqlDatabase>
#include "ksir_common.h"

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;

class kDatabase : public QSqlDatabase, public kXmlBehavior
{
public:
    kDatabase();

	void login();

	//XML
	virtual void readXml(const QString&, const QDomElement&);

private:
	virtual void writeXml(QDomNode&) {}

	bool m_set;
};

#endif // KDATABASE_H
