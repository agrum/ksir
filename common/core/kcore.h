#ifndef KCORE_H
#define KCORE_H

#include "../utils/kxmlbehavior.h"
#include <QString>

class kCore : public kXmlBehavior
{
public:
	//Lifetime
	kCore();
	kCore(const QDomNode&);
	kCore(const kCore&);
    virtual ~kCore() {}
	kCore& operator=(const kCore&);

	//Integrity helper
	bool operator==(const kCore&) const;
	bool isNull() const;

	//Get
	const QString& id() const { return m_id; }
	const QString& type() const { return m_type; }

	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&);

protected:
	QString m_id;
	QString m_type;
};

#endif // KCORE_H
