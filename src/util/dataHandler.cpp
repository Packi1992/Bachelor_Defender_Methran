//
// Created by banoodle on 07.06.23.
//
#include "dataHandler.h"

void DataHandler::load(Player &player, WaveHandler &waves, Map &map, const string &path) {
    //there should be a marker for every part
    // something like MAP-START -> MAP-END
    // then we will cut the map part and load the map
    string line;
    std::ifstream iStream;
    cout << "Load Data: " << path << endl;
    char mnName[50];
    strncpy(mnName, path.c_str(),50);
    iStream.open(mnName);

    bool Waves = false;
    bool Player = false;
    bool Map = false;

    bool data = false;
    DataType dataType = COUNT;
    Vector<std::string> dataBuff;
    if (iStream.is_open()) {
        while (getline(iStream, line)) {
            if (!data) {
                for (int i = 0; i < DataType::COUNT; i++) {
                    if (line == getTypeName(static_cast<DataType>(i)) + "-START") {
                        dataType = static_cast<DataType>(i);
                        data = true;
                        dataBuff.clear();
                    }
                }
            } else {
                for (int i = 0; i < DataType::COUNT; i++) {
                    if (line == getTypeName(static_cast<DataType>(i)) + "-END") {
                        data = false;
                        switch (dataType) {
                            case PLAYER:
                                Player = player.load(dataBuff);
                                break;
                            case MAP:
                                Map = map.load(dataBuff);
                                break;
                            case WAVES:
                                Waves = waves.load(dataBuff);
                                break;
                            case COUNT:
                                cerr << "DATA LOADER: this should not happen at all";
                                break;
                        }
                        break;
                    }
                }
                if (data) {
                    dataBuff.push_back(line);
                }
            }
        }
    }
    else{
        cerr << "cannot load data";
    }
    if(!(Waves&&Player&&Map))
        cerr << "something went wrong while loading";
}

void DataHandler::save(Player &player, WaveHandler &waves, Map &map, const string &path) {
    char name[100];
    strncpy(name, BasePath"Maps/",100);
    strncat(name, path.c_str(),100);
    strncat(name, ".map",100);
    // save pMap!
    std::ofstream oStream;

    oStream.open((name));
    for (int i = 0; i < DataType::COUNT; i++) {
        oStream << (getTypeName(static_cast<DataType>(i)) + "-START\n");
        switch (static_cast<DataType>(i)) {
            case PLAYER:
                oStream << player.save();
                break;
            case MAP:
                oStream << map.save();
                break;
            case WAVES:
                oStream << waves.save();
                break;
            case COUNT:
                cerr << "DATA LOADER: this should not happen at all";
                break;
        }
        oStream << (getTypeName(static_cast<DataType>(i)) + "-END\n");
    }
    oStream.close();
    cout << "Map Saved" << endl;
}

string DataHandler::getTypeName(DataHandler::DataType type) {
    switch(type){
        case PLAYER:
            return "PLAYER";
        case MAP:
            return "MAP";
        case WAVES:
            return "WAVES";
        case COUNT:
            return "just the count";
    }
    return "ERROR";
}
