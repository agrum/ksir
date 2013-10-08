#include "mailman.h"

#include "../utils/string.h"

using namespace ksir;

MailMan* MailMan::s_singleton = NULL;

/* $Desc Constructor, default for everything and launch
 *	the looping thread.
 * $Parm /.
 * $Rtrn /.
 */
MailMan::MailMan():
	m_comLink(MAILMAN)
{
	start();
}

/* $Desc Creates the MailMan if it wasn t set already.
 * $Parm /.
 * $Rtrn /.
 */
void
MailMan::initialize()
{
	if(s_singleton == NULL)
		s_singleton = new MailMan;
}

/* $Desc Looping function.
 * $Parm /.
 * $Rtrn /.
 */
void
MailMan::run()
{
	PRC<Msg> msg;

	while(true)
	{
		if((msg = m_comLink.read()) != NULL)
		{
			if(msg->name() == MSG_ASK_OWNERSHIP)
				//Update the ownershipping directory (add)
			{
				String owner, shipping;
				msg->get("owner", &owner);
				msg->get("shipping", &shipping);

				m_ownershipDirectory.insert(shipping, owner);
				msg->ack();
			}
			else if(msg->name() == MSG_RMV_OWNERSHIP)
				//Update the ownershipping directory (rmv)
			{
				String owner;
				msg->get("owner", &owner);

				QList<QString> shippings = m_ownershipDirectory.keys(owner);
				while(!shippings.empty())
					m_ownershipDirectory.remove(shippings.takeLast());
				msg->ack();
			}
			else
				//Otherwise, redirect the message to the owner
			{
				String owner;
				if((owner = m_ownershipDirectory.value(msg->name())) != "")
					ComLink::write(msg, owner);
			}
		}
	}
}
