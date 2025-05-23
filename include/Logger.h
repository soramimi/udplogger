#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
	static constexpr int PORT = 1024;
private:
	struct Private;
	Private *m;
public:
	Logger();
	~Logger();
	bool open();
	void close();
	void send(std::string message);
};

#endif // LOGGER_H
