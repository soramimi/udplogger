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
	bool open(const char *remote = nullptr, int port = 1024);
	void close();
	void send(std::string message);
	static void initialize();
	static void cleanup();
};

#endif // LOGGER_H
