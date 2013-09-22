#ifndef KCRYPT_H
#define KCRYPT_H

///This class is used to encrypt any kind of content.
///The encrypted output message s size is the input one plus 256 bytes.
///This is a personnal project with a big flaw, the kernel must be shared
///among parties the first time the key has been created.
///The way it should be is, the server generates a kernel and sends it to
///the client, only once. The way the kernel must be send is still unclear,
///but the flaw in security will surely happens here.
///Once the server and the client knows about the kernel, everything goes fine
///and the security of the encryption seems bulletproof enough to me.
///Since I don t know shit about security, I may be damn wrong. Anyway, the
///fact that the kernel must be shared once is a deadly falw by itself.
///Still, had fun writing this shit.

#include <QByteArray>

#include "xmlbehavior.h"

namespace ksir {

class Crypt : public XmlBehavior
{
public:
	//Lifetime
	Crypt();
	Crypt(const QByteArray&);
	Crypt(const QDomNode&);
	Crypt(const Crypt&);
	virtual ~Crypt();
	Crypt& operator=(const Crypt&);

	const unsigned char* kernel() const { return m_kernel; }

private:
	//XML
	void writeXml(QDomNode& p_node) const;

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
	kBlurer(const Crypt&);
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
	Crypt m_crypt;

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
	kClearer(const Crypt&);
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
	Crypt m_crypt;

	//dot product of the blur key used, thus not know for the receiver
	//but still reconized even if the key s compents are swapped
	unsigned char m_checksum;
	bool m_checksumInitialized;
};

}

#endif // KCRYPT_H
