#include <QApplication>
#include "pomelog.h"
#include "kclient.h"
#include "ksir_common.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

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
