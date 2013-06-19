#include "kcrypt.h"

//_-_-_PUBLIC

//---LIFETIME

kCrypt::kCrypt() :
m_clearSum(-1)
{
	m_passphraseStr = genPassphrase();
	m_kernelStr = genKernel();

	for (int i = 0; i < 256; i++){
		m_passphrase.push_back((unsigned char) (m_passphraseStr.mid(i*2, 2).toInt(NULL, 16)));
		m_kernel.push_back((unsigned char) (m_kernelStr.mid(i*2, 2).toInt(NULL, 16)));
	}

	initBlur();
}

kCrypt::kCrypt(const QDomNode& p_node) :
m_clearSum(-1)
{
	from(p_node);

	for (int i = 0; i < 256; i++){
		m_passphrase.push_back((unsigned char) (m_passphraseStr.mid(i*2, 2).toInt(NULL, 16)));
		m_kernel.push_back((unsigned char) (m_kernelStr.mid(i*2, 2).toInt(NULL, 16)));
	}
	initBlur();
}

kCrypt::kCrypt(const QByteArray& p_passphrase, const QByteArray& p_kernel):

	m_clearSum(-1),
	m_passphraseStr(p_passphrase),
	m_kernelStr(p_kernel)
{
	for (int i = 0; i < 256; i++){
		m_passphrase.push_back((unsigned char) (m_passphraseStr.mid(i*2, 2).toInt(NULL, 16)));
		m_kernel.push_back((unsigned char) (m_kernelStr.mid(i*2, 2).toInt(NULL, 16)));
	}
	initBlur();
}

kCrypt::kCrypt(const kCrypt& p_crypt):
	m_passphrase(p_crypt.m_passphrase),
	m_kernel(p_crypt.m_kernel),
	m_blurKey(p_crypt.m_blurKey),
	m_clearSum(p_crypt.m_clearSum),
	m_passphraseStr(p_crypt.m_passphraseStr),
	m_kernelStr(p_crypt.m_kernelStr)
{

}

kCrypt::~kCrypt()
{

}

kCrypt& kCrypt::operator=(const kCrypt& p_crypt)
{
	m_passphrase = p_crypt.m_passphrase;
	m_kernel = p_crypt.m_kernel;
	m_blurKey = p_crypt.m_blurKey;
	m_clearSum = p_crypt.m_clearSum;
	m_passphraseStr = p_crypt.m_passphraseStr;
	m_kernelStr = p_crypt.m_kernelStr;

	return *this;
}

//---OPERATION

QByteArray kCrypt::blur(const QByteArray& p_msg)
{
	QByteArray rtn;
	int blocks = p_msg.length()%256 + 1;
	const unsigned char* data = (const unsigned char*) p_msg.data();
	int setSorted[256];
	int setUnsorted[256];

	for (int i = 0; i < 256; i++)
		setSorted[i] = i;
	for (int i = 0; i < 256; i++)
		setUnsorted[i] = setSorted[qrand()%(256-i)];

	if(p_msg.size() > 0)
		for(int i = 0; i < blocks; i++)
			rtn.append(blurBlock(data + (256*i), setUnsorted));

	return blurBlock((const unsigned char*) m_passphrase.data(), setUnsorted) + rtn + '\0';
}

QByteArray kCrypt::clear(const QByteArray& p_msg, int size)
{
	QByteArray rtn;
	QByteArray cryptedPassphrase = p_msg.left(256);
	QByteArray cryptedMsg = p_msg.mid(256);
	int blocks = (size-256)/256 + 1;
	const unsigned char* data = (const unsigned char*) cryptedMsg.data();
	unsigned char clearKey[256];

	if(!extractClearKey((const unsigned char*) cryptedPassphrase.data(), clearKey))
		return rtn;

	for(int i = 0; i < blocks; i++){
		rtn.append(clearBlock(data + (256*i), clearKey));
	}

	return rtn;
}

//---XMLBEHAVIOUR

void kCrypt::readXml(const QString& p_tag, const QDomElement& p_node)
{
	if( p_tag == XML_CRYPT_PASSPH )
		m_passphraseStr = p_node.text().toAscii();
	else if( p_tag == XML_CRYPT_KERNEL )
		m_kernelStr = p_node.text().toAscii();
}

void kCrypt::writeXml(QDomNode& p_tag)
{
	addToElement(p_tag, XML_CRYPT_PASSPH, QString(m_passphraseStr));
	addToElement(p_tag, XML_CRYPT_KERNEL, QString(m_kernelStr));
}

//_-_-_PRIVATE

//---KEYGEN

void kCrypt::initBlur()
{
	m_blurKey.clear();
	for(int i = 0; i < 256; i++)
		m_blurKey.push_back((unsigned char)  (qrand()%256));
}

bool kCrypt::extractClearKey(const unsigned char* p_cryptedPassphrase, unsigned char* p_clearKey)
{
	union {
		int sum;
		unsigned char c[4];
	};
	int checkSum = 0;

	for(int i = 0; i < 256; i++){
		p_clearKey[i] = (unsigned char) (p_cryptedPassphrase[m_kernel[i]] - m_passphrase[i]);

		sum = 0;
		c[3] = p_clearKey[i];
		checkSum += sum * sum;
	}

	if(m_clearSum == -1){
		m_clearSum = checkSum;
		return true;
	}
	else
		return m_clearSum == checkSum;
}

QByteArray kCrypt::genPassphrase()
{
	QString rtn;

	for (int i = 0; i < 256; i++){
		int c = qrand()%256;
		if(c < 16)
			rtn += QString::number(0, 16);
		rtn += QString::number(c, 16);
	}

	return rtn.toAscii();
}

QByteArray kCrypt::genKernel()
{
	QString rtn;
	QList<int> set;

	for (int i = 0; i < 256; i++)
		set.push_back(i);
	for (int i = 0; i < 256; i++){
		int pick = set.takeAt(qrand()%(256-i));
		if(pick < 16)
			rtn += QString::number(0, 16);
		rtn += QString::number(pick, 16);
	}

	return rtn.toAscii();
}

//---INNERPROCESS

QByteArray kCrypt::blurBlock(const unsigned char* p_block, int* p_set)
{
	QByteArray rtn(256, (unsigned char) 255);
	int i = 0;

	for (; p_block[i] != 0 && i < 256; i++){
		int tmp = p_block[i];
		tmp = (tmp + m_blurKey[p_set[i]])%256;
		rtn[m_kernel[i]] = tmp;
	}
	for (; i < 256; i++){
		int tmp = 0;
		tmp = (tmp + m_blurKey[p_set[i]])%256;
		rtn[m_kernel[i]] = tmp;
	}

	return rtn;
}

QByteArray kCrypt::clearBlock(const unsigned char* p_block, unsigned char* p_key)
{
	QByteArray rtn(256, (char) 0);

	for (int i = 0; i < 256; i++){
		int tmp = p_block[m_kernel[i]];
		tmp = (tmp - p_key[i] + 256)%256;

		rtn[i] = tmp;
	}

	return rtn;
}
