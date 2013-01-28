#include "kcrypt.h"

kCrypt::kCrypt(int p_id, const QByteArray& p_passphrase, const QString& p_kernel):
	m_id(p_id),
	m_passphrase(p_passphrase)
{
	for (int i = 0; i < 256; i++)
		m_kernel.push_back(p_kernel[i].toAscii());
}

void kCrypt::setBlurKey()
{
	QList<char> set;
	m_blurKey.clear();

	for (int i = 0; i < 256; i++)
		set.push_back(i);
	for (int i = 0; i < 256; i++)
		m_blurKey.push_back(set.takeAt(qrand()%(256-i)));
}

void kCrypt::setClearKey(const QByteArray& p_cryptedPassphrase)
{
	m_clearKey.clear();

	for(int i = 0; i < 256; i++)
		m_clearKey.push_back((unsigned char) (p_cryptedPassphrase[m_kernel[i]] - m_passphrase[i]));
}

QByteArray kCrypt::blur(const QByteArray&)
{

}

QByteArray kCrypt::clear(const QByteArray&)
{

}

QByteArray kCrypt::blurBlock(char* p_block){
	QByteArray rtn(256, (char) 255);
	int i = 0;

	for (; p_block[i] != 0 && i < 256; i++){
		char tmp = p_block[i];
		if(tmp == 09)
			tmp = (char) 254;
		else if(tmp == 10)
			tmp = (char) 253;
		else if(tmp == 13)
			tmp = (char) 252;
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

QByteArray kCrypt::clearBlock(char* p_block){
	QByteArray rtn(256, (char) 255);

	for (int i = 0; i < 256; i++){
		char tmp = p_block[m_kernel[i]];
		tmp = ((tmp + m_clearKey[i] - 32)%224)+32;
		if(tmp == 255)
			tmp = (char) 00;
		else if(tmp == 254)
			tmp = (char) 09;
		else if(tmp == 253)
			tmp = (char) 10;
		else if(tmp == 252)
			tmp = (char) 13;
		rtn[i] = tmp;
	}

	return rtn;
}
