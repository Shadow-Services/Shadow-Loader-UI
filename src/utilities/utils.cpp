#include <globals.hpp>

std::vector<std::string> utils::string_splice(std::string str, std::string_view delimiter)
{
	std::vector<std::string> tokens;

	size_t pos = 0;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		tokens.push_back(str.substr(0, pos));
		str.erase(0, pos + delimiter.size());
	}
	tokens.push_back(str);

	return tokens;
}