#include <QtCore/QCoreApplication>
#include "pomelog.h"
#include "kclient.h"

int main(int argc, char *argv[])
{
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
	kClient client(doc.firstChild());

    return a.exec();
}
