// Don't take credits for this ;) Joplin / Manhhao are the first uploaders ;)

#include "MetaInfo.h"
#include "Utilities.h"

void PrintMetaHeader()
{
	printf("                                  AyyWare\n");
	Utilities::SetConsoleColor(FOREGROUND_INTENSE_GREEN);
	Utilities::SetConsoleColor(FOREGROUND_WHITE);
	Utilities::Log("Build %s", __DATE__);
	Utilities::Log("Setting Up AyyWare for %s", AYYWARE_META_GAME);
}