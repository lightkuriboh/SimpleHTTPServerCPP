
#ifndef SIMPLECPPSERVER_CONFIGPARSER_H
#define SIMPLECPPSERVER_CONFIGPARSER_H

#include <map>
#include <fstream>
#include <string>
#include <variant>

namespace Utils {
    class Config {
    private:
        std::map<std::string, std::variant<int, std::string>> configMap;

        static std::pair<std::string, std::string> splitConfig(const std::string& inputStr) {
            auto equationQuotePos = inputStr.find('=');
            auto n = inputStr.length();
            return std::make_pair(inputStr.substr(0, equationQuotePos),
                                  inputStr.substr(equationQuotePos + 1, n - equationQuotePos - 1));
        }

        [[nodiscard]] std::variant<int, std::string> getMapValue(const std::string& key) const {
            return (*this->configMap.find(key)).second;
        }
    public:
        Config() {
            std::ifstream configReader("config.cfg");
            std::string eachLine;
            while (configReader && configReader >> eachLine) {
                auto configInfo = splitConfig(eachLine);
                try {
                    auto intValue = std::stoi(configInfo.second);
                    this->configMap[configInfo.first] = intValue;
                } catch (std::invalid_argument &ia) {
                    this->configMap[configInfo.first] = configInfo.second.substr(1, configInfo.second.length() - 2);
                }
            }
            if (configReader) {
                configReader.close();
            }
        }
        [[nodiscard]] int getPort() const {
            return std::get<int>(this->getMapValue("PORT"));
        }
        [[nodiscard]] int getMaximumConnections() const {
            return std::get<int>(this->getMapValue("MAXIMUM_CONNECTIONS"));
        }
        [[nodiscard]] int getMaximumPendingConnections() const {
            return std::get<int>(this->getMapValue("MAXIMUM_PENDING_CONNECTIONS"));
        }
        [[nodiscard]] std::string getResourceFolder() const {
            return std::get<std::string>(this->getMapValue("RESOURCE_FOLDER"));
        }
    };
}

#endif //SIMPLECPPSERVER_CONFIGPARSER_H
