#ifndef KMAILMAN_H
#define KMAILMAN_H

#include <QThread>
#include <QMap>

#include "comlink.h"

#define MAILMAN "mailman"
#define MSG_ASK_OWNERSHIP "ask_ownership"
#define MSG_RMV_OWNERSHIP "remove_ownership"
#define MSG_DISC_SOCK "socket disconnected"
#define MSG_CONN_SOCK "socket connected"

namespace ksir {

class MailMan : public QThread
{
public:
	static void initialize();

private:
	MailMan();

	void run();

private:
	static MailMan* s_singleton;

	ComLink m_comLink;
	QMap<QString, QString> m_distantDirectory;
	QMap<QString, QString> m_ownershipDirectory;
};

}

#endif // KMAILMAN_H
