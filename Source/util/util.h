#pragma once

#include <string>

namespace util
{
	std::string toLowerCase(std::string str);

	std::string* readFile(const std::string& filePath);

	std::string getLinkToLineInFile(const std::string& filePath, size_t lineNumber);

	std::string getLinkToCharInFile(const std::string& filePath, const std::string& fileContents, size_t charIndex);
}
