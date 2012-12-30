#ifndef KCORE_H
#define KCORE_H

#include "../utils/kxmlbehavior.h"
#include <QString>

class kCore : public kXmlBehavior
{
public:
	kCore();
	kCore(const QDomNode&);
	kCore(const kCore&);
	kCore& operator=(const kCore&);

	bool operator==(const kCore&) const;

	QString id() const { return m_id; }
	QString type() const { return m_type; }
	QString ip() const { return m_addr; }

	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&, const QString&);

protected:
	QString m_id;
	QString m_type;
	QString m_addr;
};

#endif // KCORE_H
