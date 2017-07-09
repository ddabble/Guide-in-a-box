#include "util.h"

#include <algorithm>
#include <fstream>

std::string util::toLowerCase(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

std::string* util::readFile(const std::string& filePath)
{
	std::string* fileContents = new std::string;
	std::ifstream fileStream(filePath);

	std::string line;
	while (std::getline(fileStream, line))
		*fileContents += line + "\n";

	return fileContents;
}

std::string util::getLinkToLineInFile(const std::string& filePath, size_t lineNumber)
{
	return filePath + "(" + std::to_string(lineNumber) + ")";
}

std::string util::getLinkToCharInFile(const std::string& filePath, const std::string& fileContents, size_t charIndex)
{
	std::string contentSoFar = fileContents.substr(0, charIndex);
	int lineNumber = 1 + (int)std::count(contentSoFar.begin(), contentSoFar.end(), '\n');
	return getLinkToLineInFile(filePath, lineNumber);
}
