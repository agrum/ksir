#include <QtCore/QCoreApplication>
#include "pomelog.h"
#include "kserver.h"
#include "ksir_common.h"

int main(int argc, char** argv)
{
	/*kCrypt A;
	kCrypt B(A);

	QString fullMsg("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.");
	QByteArray msgA(A.blur(fullMsg.toAscii()));

	qDebug() << B.clear(msgA, fullMsg.size()+256);*/

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
