#ifndef KCLIENTUIMNGR_H
#define KCLIENTUIMNGR_H

#include <QMap>
#include <QMainWindow>
#include <QPalette>
#include <QFont>
#include <QThread>
#include <QTimer>
#include "pomelog.h"

#include "ksir_common.h"

namespace Ui {
class kClientUIMngr;
}

class kClientUIMngr : public QMainWindow, public pLogBehavior
{
	Q_OBJECT

public:
	explicit kClientUIMngr(kQueueW&, QWidget *parent = 0);
	~kClientUIMngr();

	inline kQueueW& queue() { return *(kQueueW*) &m_queue; }

public
slots:
	void slotLoop();

private:
	void serverConnect(const QString&);
	void serverDisconnect(const QString&);

private:
	Ui::kClientUIMngr *ui;
	QPalette m_palette;
	QTimer m_timer;

	kQueueR m_queue;
	kQueueW& m_sysQueue;
	QMap<QString, QAction*> m_serverList;
};

#endif // KCLIENTUIMNGR_H
