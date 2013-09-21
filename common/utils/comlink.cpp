#include "comlink.h"

#include <assert.h>

#define COMLINK_MAX_BUF 250

using namespace ksir;

QMap<QString, ComLink*> ComLink::s_comLinkDirectory;
QMutex ComLink::s_comLinkDirectoryLock;
QWaitCondition ComLink::s_waitConditionNewLink;
int ComLink::s_uniqueId = 0;

//Lifetime

/* $Desc Constructor taking an id. If the directory holds the same id, it tries to connect
 *		the comLinks together. Otherwise it creates an entry for it.
 * $Parm p_id name shared with an other comLink.
 * $Rtrn /.
 */
ComLink::ComLink(const QString& p_id)
{
	QString uniqueId = p_id;

	//Tries to connect with an other comLink if any with the same id
	s_comLinkDirectoryLock.lock();
		if(uniqueId == "")
			uniqueId = (s_uniqueId++);
		if((s_comLinkDirectory.value(uniqueId, NULL)) != NULL)
			return; //TODO error

		m_id = uniqueId;
		s_comLinkDirectory.insert(uniqueId, this);
		s_waitConditionNewLink.wakeAll(); //Wakes writing waiting processes
	s_comLinkDirectoryLock.unlock();
}

/* $Desc Push a pointer to a message in the calling ComLink queue.
 * $Parm p_msg pointer to an existing message.
 * $Rtrn /.
 */
void
ComLink::write(PRC<Msg>& p_msg)
{
	assert(p_msg != NULL);

	//push the message into the the dest queue
	m_comLinkLock.lock();
		m_queue.enqueue(p_msg);
		if(m_queue.length() > COMLINK_MAX_BUF)
			return; //TODO error
		m_waitConditionNewMsg.wakeAll();
	m_comLinkLock.unlock();
}

/* $Desc Push a pointer to a message in the desired ComLink queue.
 * $Parm p_msg pointer to an existing message.
 * $Parm p_dst destination comLink's id.
 * $Rtrn /.
 */
void
ComLink::write(PRC<Msg>& p_msg, const QString& p_dst)
{
	assert(p_msg != NULL);

	ComLink* dstComLink;

	//Getthe com linkd esired, or wait for its creation
	s_comLinkDirectoryLock.lock();
		while((dstComLink = s_comLinkDirectory.value(p_dst, NULL)) == NULL)
			s_waitConditionNewLink.wait(&s_comLinkDirectoryLock);
	s_comLinkDirectoryLock.unlock();

	//push the message into the the dest queue
	dstComLink->m_comLinkLock.lock();
		dstComLink->m_queue.enqueue(p_msg);
		if(dstComLink->m_queue.length() > COMLINK_MAX_BUF)
			return; //TODO error
		dstComLink->m_waitConditionNewMsg.wakeAll();
	dstComLink->m_comLinkLock.unlock();
}

/* $Desc Return the oldest entry in the queue or wait for an entry to come.
 * $Parm .
 * $Rtrn p_msg pointer to the oldest message in the queue.
 */
PRC<Msg>
ComLink::read()
{
	PRC<Msg> rtn;

	m_comLinkLock.lock();
		if(m_queue.empty())
			m_waitConditionNewMsg.wait(&m_comLinkLock);
		rtn = m_queue.dequeue();
	m_comLinkLock.unlock();

	return rtn;
}
