#include "kcrypt.h"

kCrypt::kCrypt(int p_id, const QByteArray& p_passphrase, const QString& p_kernel):
	m_id(p_id),
	m_passphrase(p_passphrase)
{
	for (int i = 0; i < 256; i++)
        m_kernel.push_back(p_kernel[i].toLatin1());
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
