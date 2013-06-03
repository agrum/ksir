#ifndef KUINAVIGATIONTREE_H
#define KUINAVIGATIONTREE_H

#include <QFrame>
#include <QList>
#include <QStandardItemModel>

namespace Ui {
class kUINavigationTree;
}

class kUINavigationTree : public QFrame
{
	Q_OBJECT
	
public:
	explicit kUINavigationTree(QWidget *parent = 0);
	~kUINavigationTree();

	void serverConnect(const QString&);
	void serverDisconnect(const QString&);
	
private:
	Ui::kUINavigationTree *ui;

	QStandardItemModel m_model;
	QList<QStandardItem*> m_serverList;
};

#endif // KUINAVIGATIONTREE_H
