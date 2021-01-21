
#ifndef SIMPLECPPSERVER_CONFIGPARSER_H
#define SIMPLECPPSERVER_CONFIGPARSER_H

#include <map>
#include <string>
#include <variant>

namespace Utils {
    class Config {
    private:
        std::map<std::string, std::variant<int, std::string> > configMap;

        static std::pair<std::string, std::string> splitConfig(const std::string& inputStr);
    public:
        Config();
        [[nodiscard]] int getPort() {
            return std::get<int>(this->configMap["PORT"]);
        }
        [[nodiscard]] int getMaximumConnections() {
            return std::get<int>(this->configMap["MAXIMUM_CONNECTIONS"]);
        }
        [[nodiscard]] int getMaximumPendingConnections() {
            return std::get<int>(this->configMap["MAXIMUM_PENDING_CONNECTIONS"]);
        }
        [[nodiscard]] std::string getResourceFolder() {
            return std::get<std::string>(this->configMap["RESOURCE_FOLDER"]);
        }
    };
}

#endif //SIMPLECPPSERVER_CONFIGPARSER_H
