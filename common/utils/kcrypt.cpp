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

/*
  00 -> 255
  09 -> 254
  10 -> 253
  13 -> 252
  */

QByteArray kCrypt::blurBlock(char* p_block){
	QByteArray rtn(256, (char) 255);

	for (int i = 0; p_block[i] != 0; i++){
		char tmp = p_block[i];
		if(tmp == 09)
			tmp = (char) 254;
		else if(tmp == 10)
			tmp = (char) 253;
		else if(tmp == 13)
			tmp = (char) 252;
		tmp += m_blurKey[i];
		rtn[m_kernel[i]] = tmp;
	}

	return rtn;
}

QByteArray kCrypt::clearBlock(char*){

}
