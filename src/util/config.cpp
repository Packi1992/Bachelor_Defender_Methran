//
// Created by banoodle on 25.06.23.
//

#include <fstream>
#include "config.h"

Config *Config::configInstance = nullptr;

Config *Config::getConfig() {
    if (configInstance == nullptr) {
        configInstance = new Config();
        configInstance->loadConfig();
    }
    return configInstance;
}

void Config::loadConfig() {
    if (std::filesystem::exists(_configPath)) {
        string line;
        std::ifstream iStream;
        iStream.open(_configPath);
        IfDebug cout << "Load Data: " << _configPath << endl;
        if (iStream.is_open()) {
            while (getline(iStream, line)) {
                if (line.substr(0, 13) == ("totalEnemies:")) {
                    totalEnemiesKilled = (long) strtol(line.substr(13).c_str(), nullptr, 10);
                }
                if (line.substr(0, 12) == ("totalBosses:")) {
                    totalBossesKilled = (long) strtol(line.substr(12).c_str(), nullptr, 10);
                }
                if (line.substr(0, 8) == ("worldNR:")) {
                    worldsFinished = (int) strtol(line.substr(8).c_str(), nullptr, 10);
                }
                if (line.substr(0, 18) == ("totalCreditPoints:")) {
                    totalCreditPointsEarned = (long) strtol(line.substr(18).c_str(), nullptr, 10);
                }
                if (line.substr(0, 18) == ("moorhuhnHighscore:")) {
                    highscoreMoorhuhn = (int) strtol(line.substr(18).c_str(), nullptr, 10);
                }
            }
        }
    }
    else{
        safeConfig();
    }
}

void Config::safeConfig() {
    std::filesystem::create_directory(BasePath"Config/");
    // save Config Data
    std::stringstream s;

    s << "totalEnemies:" << totalEnemiesKilled << "\n";
    s << "totalBosses:" << totalBossesKilled << "\n";
    s << "worldNR:" << worldsFinished << "\n";
    s << "totalCreditPoints:" << totalCreditPointsEarned << "\n";
    s << "moorhuhnHighscore:" << highscoreMoorhuhn << "\n";
    std::ofstream oStream;

    oStream.open(_configPath);
    oStream << s.str();

    oStream.close();
    cout << "Config Saved" << endl;
}

    Config::~Config()
    {
        safeConfig();
        delete configInstance;
        configInstance = nullptr;
    }
