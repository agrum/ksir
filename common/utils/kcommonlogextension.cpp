#include "kcommonlogextension.h"

void kCommonLogExtension::extendPomelog()
{
	QMap<int, QString> msgMap;

	msgMap.insert(110, "System lost");
	msgMap.insert(111, "System joined");
	msgMap.insert(112, "System named");
	msgMap.insert(310, "Outdated");

	pLog::extendMap(msgMap);
}
