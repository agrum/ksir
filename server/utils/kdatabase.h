#ifndef KDATABASE_H
#define KDATABASE_H

#include <QSqlDatabase>
#include "ksir_common.h"

class kDatabase : public QSqlDatabase, public kXmlBehavior
{
public:
    kDatabase();

	//XML
	virtual void readXml(const QString&, const QDomElement&);

private:
	virtual void writeXml(QDomNode&) {}
};

#endif // KDATABASE_H
