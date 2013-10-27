#ifndef KCOMLINK_H
#define KCOMLINK_H

///The ComLink class allows user to send messages to any ComLink as
///soon as its name is known
///The standard usage however is to send all the messages to the MailMan.
///Following the name of the message, the mailman will know to whom it
///should be redirected.
///The writing process is blocking until the dest ComLink is created.
///It is then important to create the MailMan before anyone else.
///If for any reason a message should be send directly to an other ComLink,
///the user must be sure the ComLink exists or will, otherwise the thread
///calling the writing will be blocked.
///The reading process is blocking too. As soon as the function has been
///called, the thread will be blocked until a message arrives in the ComLink.
///The reading function should then be called in looping threads.
///
///The ComLink is thread safe from the inside

#include <QMutex>
#include <QQueue>
#include <QMap>
#include <QString>
#include <QWaitCondition>

#include <pomelog.h>

#include "../utils/prc.h"
#include "../utils/msg.h"

namespace ksir {

class ComLink : public pLogBehavior
{
public:
	//Lifetime
	ComLink(const QString& p_id = "");
	~ComLink();

	//Get
	const QString& id() { return m_id; }

	//Operation
	void write(const PRC<Msg>& p_msg);
	static void write(const PRC<Msg>& p_msg, const QString& p_dst);
	PRC<Msg> read();
	void askOwnershipOver(const QString& p_name);

private:
	//Lifetime excluded
	ComLink(const ComLink&);
	ComLink& operator=(const ComLink&);

private:
	//Static directory used to conenct comLinks with the same id
	static QMap<QString, ComLink*> s_comLinkDirectory;
	static QMutex s_comLinkDirectoryLock;
	static QWaitCondition s_waitConditionNewLink;
	static int s_uniqueId;

	QString m_id;

	//Queue of message left by others. The origin is unknown.
	QQueue<PRC<Msg> > m_queue;

	QMutex m_comLinkLock;
	QWaitCondition m_waitConditionNewMsg;
};

}

#endif // KCOMLINK_H
