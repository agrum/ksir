#include "crypt.h"

#include <assert.h>

#include <QDebug>

using namespace ksir;

/////KCRYPT

//_-_-_PUBLIC

//---LIFETIME

/* $Desc Constructor. Generates its own passphrase and kernel.
 * $Parm /
 * $Rtrn /
 */
Crypt::Crypt() :
	XmlBehavior("Crypt")
{
	m_kernelStr = genKernel();

	initKernel();
}

/* $Desc Constructor. Generates its passphrase and kernel out of an XML node.
 * $Parm p_node QDomNode as the one filled by writeXML().
 * $Rtrn /
 */
Crypt::Crypt(const QDomNode& p_node) :
	XmlBehavior("Crypt")
{
	m_kernelStr = getAttribute(p_node, "kernel").toLatin1();

	initKernel();
}

/* $Desc Constructor. Generates its passphrase and kernel out of the provided kernel.
 * $Parm p_kernel Kernel in hex.
 * $Rtrn /
 */
Crypt::Crypt(const QByteArray& p_kernel) :
	XmlBehavior("Crypt"),
	m_kernelStr(p_kernel)
{
	initKernel();
}

/* $Desc Constructor. Copy an existing Crypt.
 * $Parm p_crypt reference.
 * $Rtrn /
 */
Crypt::Crypt(const Crypt& p_crypt) :
	XmlBehavior("Crypt"),
	m_kernelStr(p_crypt.m_kernelStr)
{
	memcpy(m_kernel, p_crypt.m_kernel, 256);
}

/* $Desc Desctructor.
 * $Parm /
 * $Rtrn /
 */
Crypt::~Crypt()
{

}

/* $Desc Copy operator.
 * $Parm p_crypt reference.
 * $Rtrn /
 */
Crypt&
Crypt::operator=(const Crypt& p_crypt)
{
	m_kernelStr = p_crypt.m_kernelStr;

	memcpy(m_kernel, p_crypt.m_kernel, 256);

	return *this;
}

//_-_-_PRIVATE

//---XMLBEHAVIOUR

/* $Desc XML interface inherited. Fill an XML.
 * $Parm p_tag Tag of the current node.
 * $Parm p_tag Current node.
 * $Rtrn /.
 */
void
Crypt::writeXml(QDomNode& p_node) const
{
	addAttribute(p_node, "kernel", QString(m_kernelStr));
}

//---FUNDAMENTAL

/* $Desc Generate randomly a kernel for a brand new Crypt.
 * $Parm /
 * $Rtrn 512 char long string in hexadecimal.
 */
QByteArray
Crypt::genKernel()
{
	QString rtn;
	QList<int> set;

	//The kernel is a set of entries from 0 to 255
	//The order is shuffled, but there is no doubles
	for (int i = 0; i < 256; i++)
		set.push_back(i);
	for (int i = 0; i < 256; i++){
		int pick = set.takeAt(qrand()%(256-i));
		if(pick < 16)
			rtn += QString::number(0, 16);
		rtn += QString::number(pick, 16);
	}

    return rtn.toLatin1();
}

/////KBLURER

//_-_-_PUBLIC

//---LIFETIME

/* $Desc Constructor. Generates its own passphrase and kernel.
 * $Parm /
 * $Rtrn /
 */
kBlurer::kBlurer(const Crypt& p_crypt) :
m_crypt(p_crypt)
{
	//The mixer modify frequently the bluring key.
	//It s asimple 256 char entry which sum is a multiple of 256.
	unsigned char moduler = 0;
	for (int i = 0; i < 255; i++)
		moduler += m_mixer[i] = (unsigned char) (qrand()%256);
	m_mixer[255] = 0 - moduler;

	//The bluring key is combined with the kernel to encrypt a message.
	//While both parties knows the kernel, they receiver doesn t know
	// the bluring key until the header is decrypted.
	for(int i = 0; i < 256; i++)
		m_blurKey[i] = (unsigned char) (qrand()%256);
}

/* $Desc Constructor. Generates its passphrase and kernel out of an XML node.
 * $Parm p_node QDomNode as the one filled by writeXML().
 * $Rtrn /
 */
kBlurer::kBlurer(const kBlurer& p_blurer) :
m_crypt(p_blurer.m_crypt)
{
	memcpy(m_mixer,	p_blurer.m_mixer, 256);
	memcpy(m_blurKey, p_blurer.m_blurKey, 256);
}

/* $Desc Desctructor.
 * $Parm /
 * $Rtrn /
 */
kBlurer::~kBlurer()
{

}

/* $Desc Copy operator.
 * $Parm p_crypt reference.
 * $Rtrn /
 */
kBlurer&
kBlurer::operator=(const kBlurer& p_blurer)
{
	m_crypt = p_blurer.m_crypt;

	memcpy(m_mixer,	p_blurer.m_mixer, 256);
	memcpy(m_blurKey, p_blurer.m_blurKey, 256);

	return *this;
}

//---OPERATION

/* $Desc Crypt a string. The output size is a multiple of 256.
 *	Only Crypts with the same kernel can decypher the encrypted data.
 * $Parm p_msg string to encrypt.
 * $Rtrn Encrypted input.
 */
QByteArray
kBlurer::blur(const QByteArray& p_msg)
{
	QByteArray rtn;
	int blocks = p_msg.length()/256 + p_msg.length()/1; //Message splitted every 256 chars
	const unsigned char* data = (const unsigned char*) p_msg.data();

	//Mix the bluring key
	//To avoid using the same mixer each time,
	//	the starting point used in the mixer changes
	//	randomly at each call
	//The bluring key is permanently changed
	//But its checksum stays the same
	unsigned int push = qrand()%256;
	for (int i = 0; i < 256; i++)
		m_blurKey[i] += m_mixer[(i+push)%256];

	//Encrypt the message 256bytes block by 256bytes block
	for(int i = 0; i < blocks; i++)
		rtn.append(blurBlock(data + (256*i)));

	//Set the header of the message with is the encrypted kernel
	//	with the newly mixed bluring key
	rtn = blurBlock((const unsigned char*) m_crypt.kernel()) + rtn + '\0';

	return rtn;
}

//---INNERPROCESS

/* $Desc Encrypt a 256bytes block of data.
 * $Parm p_block data to crypt
 * $Rtrn The encrypted block in a 256bytes QByteArray.
 */
QByteArray
kBlurer::blurBlock(const unsigned char* p_block)
{
	QByteArray rtn(256, (unsigned char) 255);
	int i = 0;

	//The block is supposed to be a string,
	//	\0 is a stop
	for (; p_block[i] != 0 && i < 256; i++){
		//Encryption easy as fuck, simply adding the block to the bluring key
		//It s just the way the bluring key is frequently modified that
		//	makes the encryption strong
		//Splitted in two lines for obvious uchar usage
		unsigned char tmp = p_block[i] + m_blurKey[i];
		rtn[m_crypt.kernel()[i]] = tmp;
	}
	//The output must be a 256bytes long array
	//If the string stops before, fill up with the bluring key
	for (; i < 256; i++)
		rtn[m_crypt.kernel()[i]] = m_blurKey[i];

	return rtn;
}

/////KCLEARER

//_-_-_PUBLIC

//---LIFETIME

/* $Desc Constructor. Generates its own passphrase and kernel.
 * $Parm /
 * $Rtrn /
 */
kClearer::kClearer(const Crypt& p_clearer) :
m_crypt(p_clearer),
m_checksumInitialized(false)
{

}

/* $Desc Constructor. Generates its passphrase and kernel out of an XML node.
 * $Parm p_node QDomNode as the one filled by writeXML().
 * $Rtrn /
 */
kClearer::kClearer(const kClearer& p_clearer) :
m_crypt(p_clearer.m_crypt),
m_checksum(p_clearer.m_checksum),
m_checksumInitialized(p_clearer.m_checksumInitialized)
{

}

/* $Desc Desctructor.
 * $Parm /
 * $Rtrn /
 */
kClearer::~kClearer()
{

}

/* $Desc Copy operator.
 * $Parm p_crypt reference.
 * $Rtrn /
 */
kClearer&
kClearer::operator=(const kClearer& p_clearer)
{
	m_crypt = p_clearer.m_crypt;

	m_checksum = p_clearer.m_checksum;
	m_checksumInitialized = p_clearer.m_checksumInitialized;

	return *this;
}

//---OPERATION

/* $Desc Uncrypt a string. The input size must be a multiple of 256.
 *	Only Crypts with the same kernel can decypher the encrypted data.
 * $Parm p_msg string to encrypt.
 * $Rtrn Encrypted input.
 */
QByteArray
kClearer::clear(const QByteArray& p_msg, int size)
{
	assert(size%256 == 0);

	QByteArray rtn;
	QByteArray cryptedKernel = p_msg.left(256);
	QByteArray cryptedMsg = p_msg.mid(256);
	int blocks = (size-256)/256 + size/1;
	const unsigned char* data = (const unsigned char*) cryptedMsg.data();
	unsigned char blurKeyUsed[256];

	//Assumes the clearing key from the header of the message
	//This header id the encrypted kernel
	//If the clearing key found doesn t match the checksum computed
	//	previously, the function fails
	if(!extractClearKey((const unsigned char*) cryptedKernel.data(), blurKeyUsed))
		return rtn;

	//Uncrypt every 256bytes block of data
	for(int i = 0; i < blocks; i++)
		rtn.append(clearBlock(data + (256*i), blurKeyUsed));

	return rtn;
}

//_-_-_PRIVATE

/* $Desc Retrieve the bluring key used to generate the received message.
 * $Parm p_cryptedKernel 256bytes char array corresponding to the encrypted kernel
 * $Parm p_blurKey Output parameter which is the inverse of the bluring key.
 * $Rtrn True if the checksum is consistant, else otherwise.
 */
bool
kClearer::extractClearKey(const unsigned char* p_cryptedKernel, unsigned char* p_blurKey)
{
	unsigned char checkSum = 0;

	//The kernel is crypted by itself plus the bluring key.
	//Since the intial kernel and the crypted one are known,
	//	the bluring key can be easily found
	for(int i = 0; i < 256; i++){
		//The encryption is as follow
		//The value at i is added with the bluring key and moved to kernel[i]
		//The inverse operation is then to move back the blured value to its original position
		//	and substract it by its original value
		//Since the header is the kernel, the original value is known.
		p_blurKey[i] = (unsigned char) (p_cryptedKernel[m_crypt.kernel()[i]] - m_crypt.kernel()[i]);

		//The checksum is the sum of bluring key's values % 256
		checkSum += p_blurKey[i];
	}

	//For the first call, the checksum is unknown since its the sender who decides of it
	//Thus the first call is always true
	if(!m_checksumInitialized)
	{
		m_checksum = checkSum;
		m_checksumInitialized = true;
	}

	return m_checksum == checkSum;
}

//---INNERPROCESS

/* $Desc Uncrypt a 256bytes block of data.
 * $Parm p_block data to uncrypt
 * $Rtrn The uncrypted block in a up to 256bytes QByteArray.
 */
QByteArray
kClearer::clearBlock(const unsigned char* p_block, unsigned char* p_blurKey)
{
	QByteArray rtn(256, (char) 0);

	for (int i = 0; i < 256; i++){
		//Uncryption easy as fuck, simply subtracting the block by the bluring key
		//It s just the way the bluring key is frequently modified that
		//	makes the encryption strong
		//Splitted in two lines for obvious uchar usage
		unsigned char tmp = p_block[m_crypt.kernel()[i]] - p_blurKey[i];
		rtn[i] = tmp;
	}

	return rtn;
}
