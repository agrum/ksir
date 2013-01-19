#ifndef KCOMMONLOGEXTENSION_H
#define KCOMMONLOGEXTENSION_H

#include "pomelog.h"

class kCommonLogExtension
{
public:
	enum kCommonMsg {
		INFO_K_LOST = 110,
		INFO_K_JOINED = 111,
		INFO_K_NAME = 112
	};

	static void extendPomelog();
};



#endif // KCOMMONLOGEXTENSION_H
