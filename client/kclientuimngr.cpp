#include "kclientuimngr.h"

#include "ui_kclientuimngr.h"

kClientUIMngr::kClientUIMngr(kQueueW& p_sysQueue, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::kClientUIMngr),
	m_sysQueue(p_sysQueue)
{
	ui->setupUi(this);

	/*m_palette.setColorGroup(
				QPalette::Normal,
				QBrush (QColor (20, 20, 30)),
				QBrush (QColor (50, 50, 60)),
				QBrush (QColor (40, 30, 40)),
				QBrush (QColor (20, 20, 20)),
				QBrush (QColor (20, 20, 30)),
				QBrush (QColor (140, 140, 150)),
				QBrush (QColor (170, 170, 190)),
				QBrush (QColor (40, 40, 45)),
				QBrush (QColor (35, 35, 40)) );

	setPalette(m_palette);*/

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
