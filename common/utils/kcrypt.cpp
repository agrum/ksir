#include "kcrypt.h"

kCrypt::kCrypt(int p_id, const QByteArray& p_passphrase, const QString& p_kernel):
	m_id(p_id),
	m_passphrase(p_passphrase)
{
	for (int i = 0; i < 256; i++)
		m_kernel.push_back((unsigned char) (p_kernel.mid(i*2, 2).toInt(NULL, 16)));
}

void kCrypt::setBlurKey()
{
	m_blurKey.clear();
	for(int i = 0; i < 256; i++)
		m_blurKey.push_back((unsigned char)  (qrand()%226));
}

void kCrypt::setClearKey(const QByteArray& p_cryptedPassphrase)
{
	m_clearKey.clear();

	for(int i = 0; i < 256; i++)
		m_clearKey.push_back((unsigned char) (p_cryptedPassphrase[m_kernel[i]] - m_passphrase[i]));
}

QByteArray kCrypt::blur(const QByteArray& p_msg)
{
	QByteArray rtn;
	int blocks = p_msg.length()%256 + 1;
	const unsigned char* data = (const unsigned char*) p_msg.data();

	for(int i = 0; i < blocks; i++)
		rtn.append(blurBlock(data + (256*i)));

	return rtn;
}

QByteArray kCrypt::clear(const QByteArray& p_msg)
{
	QByteArray rtn;
	int blocks = p_msg.length()%256 + 1;
	const unsigned char* data = (const unsigned char*) p_msg.data();

	for(int i = 0; i < blocks; i++){
		rtn.append(clearBlock(data + (256*i)));
	}

	return rtn;
}

QByteArray kCrypt::genPassphrase()
{
	QString rtn;

	for (int i = 0; i < 256; i++)
		rtn += QString::number(qrand()%224 + 32, 16);

	return rtn.toAscii();
}

QByteArray kCrypt::genKernel()
{
	QString rtn;
	QList<int> set;

	for (int i = 0; i < 256; i++)
		set.push_back(i);
	for (int i = 0; i < 256; i++)
		rtn += QString::number(set.takeAt(qrand()%(256-i)), 16);

	return rtn.toAscii();
}

QByteArray kCrypt::blurBlock(const unsigned char* p_block)
{
	QByteArray rtn(256, (unsigned char) 255);
	int i = 0;

	for (; p_block[i] != 0 && i < 256; i++){
		char tmp = p_block[i];
		if(tmp == 9)
			tmp = (unsigned char) 254;
		else if(tmp == 10)
			tmp = (unsigned char) 253;
		else if(tmp == 13)
			tmp = (unsigned char) 252;
		tmp = ((tmp + m_blurKey[i] - 32)%224)+32;
		rtn[m_kernel[i]] = tmp;
	}
	for (; i < 256; i++){
		char tmp = 255;
		tmp = ((tmp + m_blurKey[i] - 32)%224)+32;
		rtn[m_kernel[i]] = tmp;
	}

	return rtn;
}

QByteArray kCrypt::clearBlock(const unsigned char* p_block)
{
	QByteArray rtn(256, (unsigned char) 255);

	for (int i = 0; i < 256; i++){
		unsigned char tmp = p_block[m_kernel[i]];
		tmp = ((tmp + m_clearKey[i] - 32)%224)+32;
		if(tmp == 255)
			tmp = (unsigned char) 0;
		else if(tmp == (unsigned char) 254)
			tmp = (unsigned char) 9;
		else if(tmp == (unsigned char) 253)
			tmp = (unsigned char) 10;
		else if(tmp == (unsigned char) 252)
			tmp = (unsigned char) 13;
		rtn[i] = tmp;
	}

	return rtn;
}
