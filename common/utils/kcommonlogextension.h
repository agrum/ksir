#ifndef KCOMMONLOGEXTENSION_H
#define KCOMMONLOGEXTENSION_H

#include <QMap>
#include <QString>
#include "pomelog.h"

class kCommonLogExtension
{
public:
	enum kCommonMsg {
		INFO_LOST = 110,
		INFO_JOINED = 111,
		INFO_NAME = 112,
		WARNING_OUTDATED = 310
	};

	static void extendPomelog();

private:
	kCommonLogExtension() {}
};

#endif // KCOMMONLOGEXTENSION_H
