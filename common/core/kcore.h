#ifndef KCORE_H
#define KCORE_H

#include "../utils/kxmlbehavior.h"
#include <QString>

class kCore : public kXmlBehavior
{
public:
	kCore();
	kCore(const QString&, const QString&);
	kCore(const kCore&);
	kCore& operator=(const kCore&);

	bool operator==(const kCore&) const;

	QString id() const { return m_id; }
	QString type() const { return m_type; }

	//XML
	virtual void readXml(const QDomNode&);
	virtual void writeXml(QDomNode&, const QString&);

protected:
	QString m_id;
	QString m_type;
};

#endif // KCORE_H
