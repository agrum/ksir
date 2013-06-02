#include "kclientuimngr.h"

kClientUIMngr::kClientUIMngr(kQueueW& p_sysQueue):
	m_sysQueue(p_sysQueue)
{
	m_widget.show();

	start();
}

kClientUIMngr::~kClientUIMngr()
{

}

void kClientUIMngr::run()
{
	kMsg tmp;

	while(true){
		while(m_queue.pop(tmp)){
			if(tmp.is(MSG_DISC_SOCK, kMsgHeader::REP)){
				m_widget.changeText(tmp.text("who"));
			}
			else if(tmp.is(MSG_CONN_SOCK, kMsgHeader::REP)){
				m_widget.changeText(tmp.text("who"));
			}
		}

		msleep(100);
	}
}
