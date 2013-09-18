#ifndef KCRYPT_H
#define KCRYPT_H

#include <QByteArray>

#include "kxmlbehavior.h"

class kCrypt : public kXmlBehavior
{
public:
	//Lifetime
	kCrypt();
	kCrypt(const QByteArray&);
	kCrypt(const QDomNode&);
	kCrypt(const kCrypt&);
    virtual ~kCrypt();
	kCrypt& operator=(const kCrypt&);

	const unsigned char* kernel() const;

private:
	//XML
	virtual void readXml(const QString&, const QDomElement&);
	virtual void writeXml(QDomNode&);

	//Fundamental operations
	QByteArray genKernel();
	void initKernel();

private:
    //256 bytes combination delivered by the server only once
	//Never sent uncrypted
	//Used as combination key and header
	unsigned char m_kernel[256];
	QByteArray m_kernelStr;
};

class kBlurer
{
public:
	//Lifetime
	kBlurer(const kCrypt&);
	kBlurer(const kBlurer&);
	virtual ~kBlurer();
	kBlurer& operator=(const kBlurer&);

	//Usage interface
	QByteArray blur(const QByteArray&);

private:
	//Redundant operations
	QByteArray blurBlock(const unsigned char*);

private:
	//Instance holding crypting kernel
	kCrypt m_crypt;

	//Init boolean, enable the use of empty blurer
	bool m_initialized;

	//256 bytes combination which sum is a multiple of 256
	//Every time a message needs to be crypted, the blurkey is mixed
	//But because of its sum property, the checksum is constant
	unsigned char m_mixer[256];

	//256 bytes key initilized by the system
	//Never shared uncrypted, nor crypted
	//Used as additional key to crypt outgoing messages
	unsigned char m_blurKey[256];
};

class kClearer
{
public:
	//Lifetime
	kClearer(const kCrypt&);
	kClearer(const kClearer&);
	virtual ~kClearer();
	kClearer& operator=(const kClearer&);

	//Usage interface
	QByteArray clear(const QByteArray&, int);

private:
	//Fundamental operations
	bool extractClearKey(const unsigned char*, unsigned char*);

	//Redundant operations
	QByteArray clearBlock(const unsigned char*, unsigned char*);

private:
	//Instance holding crypting kernel
	kCrypt m_crypt;

	//dot product of the blur key used, thus not know for the receiver
	//but still reconized even if the key s compents are swapped
	unsigned char m_checksum;
	bool m_checksumInitialized;
};

#endif // KCRYPT_H
