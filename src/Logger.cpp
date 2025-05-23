#include "Logger.h"
#include "htmlencode.h"
#include "strformat.h"
#include <arpa/inet.h>
#include <cstring>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

struct Logger::Private {
	int sockfd = -1;
	struct sockaddr_in server_addr;
};

Logger::Logger()
	: m(new Private)
{
}

Logger::~Logger()
{
	close();
	delete m;
}

bool Logger::open()
{
	// ソケットの作成
	if ((m->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket creation failed");
		return false;
	}

	// サーバーアドレスの設定
	memset(&m->server_addr, 0, sizeof(m->server_addr));
	m->server_addr.sin_family = AF_INET;
	m->server_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &m->server_addr.sin_addr);
	return true;
}

void Logger::close()
{
	int fd = -1;
	std::swap(fd, m->sockfd);
	if (fd != -1) {
		::close(fd);
	}
}

void Logger::send(std::string message)
{
	pid_t pid = getpid();

	struct timeval tv;
	gettimeofday(&tv, nullptr);
	time_t now = tv.tv_sec;
	struct tm *lt = localtime(&now);
	int date_year = lt->tm_year + 1900;
	int date_month = lt->tm_mon + 1;
	int date_day = lt->tm_mday;
	int time_hour = lt->tm_hour;
	int time_minute = lt->tm_min;
	int time_second = lt->tm_sec;
	int usec = tv.tv_usec;

	message = strf("<pid>%d<d>%d-%02d-%02d<t>%02d:%02d:%02d<us>%06d<m>%s")
			(pid)
			(date_year)(date_month)(date_day)
			(time_hour)(time_minute)(time_second)
			(usec)(html_encode(message));

	sendto(m->sockfd, message.c_str(), message.size(), 0, (const struct sockaddr *)&m->server_addr, sizeof(m->server_addr));
}
