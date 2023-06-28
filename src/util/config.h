//
// Created by banoodle on 25.06.23.
//

#ifndef SDL_BACHELORDEFENDER_CONFIG_H
#define SDL_BACHELORDEFENDER_CONFIG_H

#include "global.h"

class Config {
private:
    explicit Config() = default ;

    static Config *configInstance;
    std::string _configPath = BasePath"Config/config.txt";

    void loadConfig();

    ~Config();

public:
    static Config *getConfig();
    long totalEnemiesKilled = 0;
    long totalBossesKilled = 0;
    int worldsFinished = 0;
    long totalCreditPointsEarned = 0;
    int highscoreMoorhuhn = 0;

    Config(Config &other) = delete;

    void operator=(const Config &) = delete;

    void safeConfig();
};


#endif //SDL_BACHELORDEFENDER_CONFIG_H
