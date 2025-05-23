#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QDateTime>
#include <QTableView>

struct LogItem {
	pid_t pid = 0;
	QDateTime ts;
	int us = -1;
	QString message;
	LogItem() = default;
	LogItem(QString const &message)
		: message(message)
	{
	}
	static LogItem parse(std::string_view const &sv);
};
Q_DECLARE_METATYPE(LogItem)

class LogView : public QTableView {
	Q_OBJECT
private:
	struct Private;
	Private *m;
public:
	explicit LogView(QWidget *parent = nullptr);
	~LogView();
	void add(std::vector<LogItem> &&item);
	void clear();
};

#endif // LOGVIEW_H
