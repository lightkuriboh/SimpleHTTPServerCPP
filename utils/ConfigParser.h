
#ifndef SIMPLECPPSERVER_CONFIGPARSER_H
#define SIMPLECPPSERVER_CONFIGPARSER_H

#include <map>
#include <string>
#include <variant>

namespace Utils {
    class Config {
    private:
        static std::pair<std::string, std::string> splitConfig(const std::string& inputStr);

        std::map<std::string, std::variant<int, std::string>> configMap;
        [[nodiscard]] std::variant<int, std::string> getMapValue(const std::string& key) const;
    public:
        Config();
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
