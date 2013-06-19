#include "kclientuimngr.h"

#include "ui_kclientuimngr.h"

kClientUIMngr::kClientUIMngr(kQueueW& p_sysQueue, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::kClientUIMngr),
	m_sysQueue(p_sysQueue)
{
	ui->setupUi(this);

	connect(&m_timer, SIGNAL(timeout()),
			this, SLOT(slotLoop()));

	m_timer.setInterval(40);
	m_timer.start();

	show();
}

kClientUIMngr::~kClientUIMngr()
{
	delete ui;
}

//---SLOTS

void kClientUIMngr::slotLoop()
{
	kMsg tmp;

	while(m_queue.pop(tmp)){
		if(tmp.is(MSG_CONN_SOCK, kMsgHeader::REP)){
			serverConnect(tmp.text("who"));
		}
		else if(tmp.is(MSG_DISC_SOCK, kMsgHeader::REP)){
			serverDisconnect(tmp.text("who"));
		}
	}
}

//---PRIVATE

void kClientUIMngr::serverConnect(const QString& p_id)
{
	ui->navigationTree->serverConnect(p_id);
}

void kClientUIMngr::serverDisconnect(const QString& p_id)
{
	ui->navigationTree->serverDisconnect(p_id);
}
