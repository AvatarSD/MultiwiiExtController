#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <string>

char* getCmdOption(char ** begin, char ** end, const std::string & option);
bool cmdOptionExists(char** begin, char** end, const std::string& option);

#endif // ARGPARSER_H
