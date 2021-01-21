
#include "utils/ConfigParser.h"

#include <fstream>

Utils::Config::Config() {
    std::ifstream configReader("../config.cfg");
    std::string eachLine;
    while (configReader >> eachLine) {
        auto configInfo = splitConfig(eachLine);
        try {
            auto intValue = std::stoi(configInfo.second);
            this->configMap[configInfo.first] = intValue;
        } catch (std::invalid_argument &ia) {
            this->configMap[configInfo.first] = configInfo.second.substr(1, configInfo.second.length() - 2);
        }
    }
    configReader.close();
}

std::pair<std::string, std::string> Utils::Config::splitConfig(const std::string &inputStr) {
    auto equationQuotePos = inputStr.find('=');
    auto n = inputStr.length();
    return std::make_pair(inputStr.substr(0, equationQuotePos),
                          inputStr.substr(equationQuotePos + 1, n - equationQuotePos - 1));
}
