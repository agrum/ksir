#include "kcrypt.h"

kCrypt::kCrypt(int p_id, const QByteArray& p_passphrase, const QString& p_kernel):
	m_id(p_id)
{
	for (int i = 0; i < 256; i++){
		m_passphrase.push_back((unsigned char) (p_passphrase.mid(i*2, 2).toInt(NULL, 16)));
		m_kernel.push_back((unsigned char) (p_kernel.mid(i*2, 2).toInt(NULL, 16)));
	}
}

void kCrypt::setBlurKey()
{
	m_blurKey.clear();
	for(int i = 0; i < 256; i++)
		m_blurKey.push_back((unsigned char)  (qrand()%256));
}

void kCrypt::setClearKey(const QByteArray& p_cryptedPassphrase)
{
	m_clearKey.clear();

	for(int i = 0; i < 256; i++)
		m_clearKey.push_back((unsigned char) (p_cryptedPassphrase[m_kernel[i]] - m_passphrase[i]));
}

QByteArray kCrypt::initBlured()
{
	qDebug() << m_passphrase;
	return blur(m_passphrase);
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
		rtn += QString::number(qrand()%220, 16);

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

QByteArray kCrypt::blurBlock(const unsigned char* p_block)
{
	QByteArray rtn(256, (unsigned char) 255);
	int i = 0;

	for (; p_block[i] != 0 && i < 256; i++){
		int tmp = p_block[i];
		tmp = (tmp + m_blurKey[i])%256;
		rtn[m_kernel[i]] = tmp;
	}
	for (; i < 256; i++){
		int tmp = 0;
		tmp = (tmp + m_blurKey[i])%256;
		rtn[m_kernel[i]] = tmp;
	}

	return rtn;
}

QByteArray kCrypt::clearBlock(const unsigned char* p_block)
{
	QByteArray rtn(256, (char) 0);

	for (int i = 0; i < 256; i++){
		int tmp = p_block[m_kernel[i]];
		tmp = (tmp - m_clearKey[i] + 256)%256;

		rtn[i] = tmp;
	}

	return rtn;
}
