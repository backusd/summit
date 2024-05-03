#include "pch.h"
#include "Logger.h"



int main(int argc, char** argv)
{
	std::cout << "Hello\n";

	LOG_TRACE("World");
	LOG_TRACE("Eat some {0}", 69);
	LOG_INFO("Info {0} {1}", 69, "no thanks");
	LOG_WARN("Warn {0}", true);
	LOG_ERROR("Error - you suck");

	LOG_TRACE("Eat some {0}", 69);
	LOG_INFO("Info {0} {1}", 69, "no thanks");
	LOG_WARN("Warn {0}", true);
	LOG_ERROR("Error - you suck");

	return 0;
}