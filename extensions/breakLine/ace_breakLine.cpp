/*
 * ace_breakLine.cpp
 *
 * Takes a string and insert as many line breaks as needed so it fits a given width
 *
 * Takes:
 * Localized string as string
 * Example: "Check weapon temperature"
 *
 * Returns:
 * String with line breaks
 */

#include "ace_common.h"

#include <sstream>
#include <vector>
#include <string>

#define MAXCHARACTERS 14

static char VERSION[] = "1.0";

extern "C" {
    __declspec (dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
};

std::vector<std::string> splitString(const std::string & input) {
    std::istringstream ss(input);
    std::string token;

    std::vector<std::string> output;
    while (std::getline(ss, token, ' ')) {
        output.push_back(token);
    }

    return output;
}

std::string addLineBreaks(const std::vector<std::string> &words) {
    std::stringstream sstream;
    int numChar = 0;
    int i = 0;

    while (i < words.size()) {
        if (numChar == 0) {
            sstream << words[i];
            numChar += words[i].size();
            i++;
        } else {
            if (numChar + 1 + words[i].size() > MAXCHARACTERS) {
                sstream << "<br/>";
                numChar = 0;
            } else {
                sstream << " " << words[i];
                numChar += 1 + words[i].size();
                i++;
            }
        }
    }
    
    return sstream.str();
}

// i like to live dangerously. jk, fix strncpy sometime pls.
#pragma warning( push )
#pragma warning( disable : 4996 )

void __stdcall RVExtension(char *output, int outputSize, const char *function) {
    if (!strcmp(function, "version")) {
        strncpy(output, VERSION, outputSize);
    } else {
        strncpy(output, addLineBreaks(splitString(function)).c_str(), outputSize);
        output[outputSize - 1] = '\0';
    }
}

#pragma warning( pop )
