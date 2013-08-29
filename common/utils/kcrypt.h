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
    virtual ~kCrypt();
	kCrypt& operator=(const kCrypt&);

	QByteArray blur(const QByteArray&);
	QByteArray clear(const QByteArray&, int);

	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&);

private:
	bool extractClearKey(const unsigned char*, unsigned char*);
	void initBlur();

	QByteArray genPassphrase();
	QByteArray genKernel();

	QByteArray blurBlock(const unsigned char*, int*);
	QByteArray clearBlock(const unsigned char*, unsigned char*);

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

	//dot product of the blur key used, thus not know for the receiver
	//but still reconized even if the key s compents are swapped
	int m_clearSum;

	QByteArray m_passphraseStr;
	QByteArray m_kernelStr;
};

#endif // KCRYPT_H
