#include "Logger.h"

int main()
{
	Logger logger;
	logger.open();
	logger.send("Hello, world");
	logger.close();
	return 0;
}

