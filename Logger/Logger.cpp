#include <print>
#include <string>
#include <string_view>
#include <fstream>
#include <chrono>
#include <iostream>
#include <format>

enum LogLevel {
	INFO,
	DEBUG,
	WARNING,
	ERROR,
	CRIT
};

class AbstractLogger {
public:
	virtual ~AbstractLogger() = default;
	virtual void log(std::string_view msg) = 0;
	virtual void log(std::string_view msg, LogLevel level) {
		switch (level) {
		case INFO:
			std::print("[INFO] {}", msg);
			break;
		case DEBUG:
			std::print("[DEBUG] {}", msg);
			break;
		case WARNING:
			std::print("[WARN] {}", msg);
			break;
		case ERROR:
			std::print("[ERROR] {}", msg);
			break;
		case CRIT:
			std::print("[CRIT] {}", msg);
			break;
		}
	};
};

class SimpleLogger : public AbstractLogger {
private:
	std::string name;
public:
	explicit SimpleLogger(std::string_view name = "") : name(name) {}
	~SimpleLogger() = default;

	void log(std::string_view msg) override {
		if (!name.empty()) {
			std::print("[{}] {}\n", name, msg);
		}
		else {
			std::print("{}\n", msg);
		}
	}
};


class Logger : public AbstractLogger {
private:
	std::string from;
	std::string name;
public:
	Logger(std::string_view name = "", std::string_view from = "") : name(name), from(from) {}

	std::string get_timestamp() {
		auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
		return std::format("{:%Y-%m-%d %H:%M:%S}", now);
	}

	std::string get_level(LogLevel level) {
		switch (level) {
		case INFO:
			return "[INFO]";
		case DEBUG:
			return "DEBUG";
		case WARNING:
			return "WARNING";
		case ERROR:
			return "ERROR";
		case CRIT:
			return "CRIT";
		}
	}

	void log(std::string_view msg) override {
		auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());

		std::print("[{:%H:%M:%S}] [{}] ({}) {}\n", now, from, name, msg);
	}

	void log(std::string_view msg, LogLevel level) override {
		auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());

		std::string prefix = get_level(level);

		if (level == ERROR || level == CRIT) {
			std::print("[{:%H:%M:%S}] [{}/{}] ({}) {}\n", now, from, prefix, name, msg);
			return;
		}

		std::print("[{:%H:%M:%S}] [{}/{}] ({}) {}\n", now, from, prefix, name, msg);
	}

	void info(std::string_view msg) {
		log(msg, LogLevel::INFO);
	}
	void debug(std::string_view msg) {
		log(msg, LogLevel::DEBUG);
	}
	void warn(std::string_view msg) {
		log(msg, LogLevel::WARNING);
	}

	void error(std::string_view msg) {
		log(msg, LogLevel::ERROR);
	}

	void critical(std::string_view msg) {
		log(msg, LogLevel::CRIT);
	}
};

/*
class CLogger : public AbstractLogger {
private:
	std::string name;
	bool is_err;
public:
};
*/

int main() {
	SimpleLogger simple_logger = SimpleLogger("well");
	simple_logger.log("hello ");

	Logger* logger = new Logger("Main", "Initialization");

	logger->log("Hello world!");

	logger->log("Hello level ", LogLevel::WARNING);

	return 0;
}