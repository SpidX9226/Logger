#include <print>
#include <string>
#include <string_view>

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
			std::print("[{}] {}", name, msg);
		}
		else {
			std::print("{}", msg);
		}
	}
};

int main() {
	SimpleLogger logger = SimpleLogger("well");

	logger.log("hello");

	return 0;
}