#include <QtCore/QCoreApplication>
#include "pomelog.h"
#include "kserver.h"
#include "ksir_common.h"

int main(int argc, char *argv[])
{
	/*QByteArray passph = kCrypt::genPassphrase();
	QByteArray kernel = kCrypt::genKernel();
	QByteArray str;
	kCrypt crypt(0, passph, kernel);

	crypt.setBlurKey();
	str = crypt.initBlured();
	crypt.setClearKey(str);
	qDebug() << crypt.clear(str);
	qDebug() << crypt.clear(crypt.blur("123456789123456789"));*/

	QCoreApplication a(argc, argv);

	pLog::init("ksir.log", pLog::ALL);
	pLog::sign((void*) 1, "main()");
	kCommonLogExtension::extendPomelog();

	QString confFile = QString(argv[1]);
	QFile file(confFile);
	if(file.exists() == false){
		pLog::logE((void*) 1, pLog::ERROR_NONE, "Fichier de configuration inexistant");
		sleep(1);
		return false;
	}

	QDomDocument doc;
	doc.setContent(&file);
	kServer server(doc.firstChild());

	return a.exec();
}
