#include <QApplication>
#include "pomelog.h"
//#include "kclient.h"
#include "ksir_common.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//Setup logger
	pLog::init("ksir.log", pLog::ALL);
	pLog::sign((void*) 1, "main()");

	//Check input parameter existence
	if(argc != 2)
		pLog::logE((void*) 1, "Conf file required as run parameter", true);

	//Load conf file
	QString confFile = QString(argv[1]);
	QFile file(confFile);
	if(file.exists() == false){
		pLog::logE((void*) 1, "Conf file not found", true);
		return false;
	}

	ComLink comLinkA("A");

	comLinkA.askOwnershipOver("MsgForA");

	PRC<Msg> MsgForA = new Msg("MsgForA", Msg::INFO);
	ComLink::write(MsgForA, MAILMAN);

	PRC<Msg> MsgForARead = comLinkA.read();

	//Launch app
	//QDomDocument doc;
	//doc.setContent(&file);
	//kClient client(doc.firstChild());

	return 1;
}
