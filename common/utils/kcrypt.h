#ifndef KCRYPT_H
#define KCRYPT_H

#include <QMap>
#include <QList>
#include <QPair>
#include <QString>
#include <QDebug>
#include <QByteArray>

#include "kxmlbehavior.h"

class kCrypt : public kXmlBehavior
{
public:
	kCrypt();
	kCrypt(const QByteArray&, const QByteArray&);
	kCrypt(const QDomNode&);
	kCrypt(const kCrypt&);
	~kCrypt();
	kCrypt& operator=(const kCrypt&);

	void initClear(const QByteArray&);
	QByteArray initBlur();

	QByteArray blur(const QByteArray&);
	QByteArray clear(const QByteArray&);

	const QByteArray& passphrase();
	const QByteArray& kernel();

	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&);

private:
	QByteArray genPassphrase();
	QByteArray genKernel();

	QByteArray blurBlock(const unsigned char*);
	QByteArray clearBlock(const unsigned char*);

private:
    //256 bytes word delivered by the server only once
    //Never shared uncrypted afterwards
    //Used as step stone to determine the blurKey used by the other party
	QByteArray m_passphrase;

    //256 bytes combination delivered by the server only once
    //Never sent uncrypted, nor crypted
    //Used as combination key
	QList<unsigned char> m_kernel;

    //256 bytes key initilized by the system
    //Never shared uncrypted, nor crypted
    //Used as additional key to crypt outgoing messages
	QList<unsigned char> m_blurKey;

    //256 bytes key determined through setClearkey()
    //Never shared uncrypted, nor crypted
    //Used as additional key to crypt incoming messages
	QList<unsigned char> m_clearKey;

	QByteArray m_passphraseStr;
	QByteArray m_kernelStr;
};

#endif // KCRYPT_H
