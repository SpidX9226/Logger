#include <print>
#include <string>
#include <string_view>
#include <fstream>
#include <chrono>
#include <iostream>
#include <format>

class AbstractLogger {
public:
	virtual ~AbstractLogger() = default;
	virtual void log(std::string_view msg) = 0;
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

	void log(std::string_view msg) override {
		auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());

		std::print("[{:%H:%M:%S}] [{}] ({}) {}\n", now, from, name, msg);
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

	return 0;
}