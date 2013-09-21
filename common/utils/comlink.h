#ifndef KCOMLINK_H
#define KCOMLINK_H

#include <QMutex>
#include <QQueue>
#include <QMap>
#include <QString>
#include <QWaitCondition>

#include "prc.h"
#include "msg.h"

namespace ksir {

class ComLink
{
public:
	//Lifetime
	ComLink(const QString& p_id = "");

	//Get
	const QString& id() { return m_id; }

	//Operation
	void write(PRC<Msg>& p_msg);
	static void write(PRC<Msg>& p_msg, const QString& p_dst);
	PRC<Msg> read();

private:
	//Static directory used to conenct comLinks with the same id
	static QMap<QString, ComLink*> s_comLinkDirectory;
	static QMutex s_comLinkDirectoryLock;
	static QWaitCondition s_waitConditionNewLink;
	static int s_uniqueId;

	QString m_id;

	//Queue of message left for the reader
	//The instance write its message in its own queue to avoid
	//	throwing away messages if the other party isn t there yet
	QQueue<PRC<Msg> > m_queue;

	QMutex m_comLinkLock;
	QWaitCondition m_waitConditionNewMsg;
};

}

#endif // KCOMLINK_H
