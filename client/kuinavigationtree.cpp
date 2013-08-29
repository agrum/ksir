#include "kuinavigationtree.h"
#include "ui_kuinavigationtree.h"

kUINavigationTree::kUINavigationTree(QWidget *parent) :
	QFrame(parent),
	ui(new Ui::kUINavigationTree)
{
	ui->setupUi(this);
	ui->treeView->setModel(&m_model);
}

kUINavigationTree::~kUINavigationTree()
{
	delete ui;
}

void kUINavigationTree::serverConnect(const QString& p_id)
{
	QStandardItem* parentItem = m_model.invisibleRootItem();
	QStandardItem* item;
	bool contains = false;
	QList<QStandardItem*>::iterator it;

	for(it = m_serverList.begin(); it != m_serverList.end(); it++)
		if((*it)->text() == p_id)
			contains = true;
	if(!contains){
		item = new QStandardItem(p_id);
		m_serverList << item;
		parentItem->appendRow(item);
	}
}

void kUINavigationTree::serverDisconnect(const QString& p_id)
{
	int i;
	QList<QStandardItem*>::iterator it;

	for(it = m_serverList.begin(), i = 0; it != m_serverList.end(); it++, i++)
		if((*it)->text() == p_id){
			m_serverList.erase(it);
			delete (m_model.invisibleRootItem()->takeRow(i)[0]);
			return;
		}
}
