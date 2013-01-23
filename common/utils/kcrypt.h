#ifndef KCRYPT_H
#define KCRYPT_H

#include <QMap>
#include <QList>
#include <QPair>
#include <QString>
#include <QByteArray>

/*
  init_phrase : 256 char passphrase to determine the key
  id : never crypted, fast access database
  kernel : 256bytes combination
  key : ~256bytes key generated by the client at each connexion
  */

class kCrypt
{
public:
	kCrypt(int, const QByteArray&, const QString&);

	void setBlurKey();
	void setClearKey(const QByteArray&);

	QByteArray blur(const QByteArray&);
	QByteArray clear(const QByteArray&);

private:
	QByteArray blurBlock(char*);
	QByteArray clearBlock(char*);

private:
	int m_id;
	QByteArray m_passphrase;
	QList<char> m_kernel;
	QList<char> m_blurKey;
	QList<char> m_clearKey;
};

#endif // KCRYPT_H
