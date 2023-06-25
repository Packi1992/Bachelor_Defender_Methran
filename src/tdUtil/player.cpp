//
// Created by banoodle on 07.06.23.
//

#include "player.h"

bool Player::load(const Vector<string> &data) {
    bool SanityLoaded = false;
    bool creditPointsLoaded = false;
    bool towerLoaded = false;
    // now we need to load lines out of Map string
    for(const string& line: data) {
        if (line.substr(0, 8) == ("SANITY :")) {
            _maxSanity = (int) strtol(line.substr(8).c_str(), nullptr, 10);
            _sanity = _maxSanity;
            SanityLoaded = true;
        }
        if (line.substr(0, 15) == ("CREDIT-POINTS :")) {
            _creditPoints = (int) strtol(line.substr(15).c_str(), nullptr, 10);
            creditPointsLoaded = true;
        }
        if(line.substr(0, 13) == ("TOWER-ENTRY :")){
            _usableTowers.insert((MenuEntries) strtol(line.substr(13).c_str(), nullptr, 10));
            towerLoaded = true;
        }
    }
    return SanityLoaded&&creditPointsLoaded&&towerLoaded;
}

std::string Player::save() const {
    // save PlayerData
    std::stringstream s;
    //checkPlayerStartSpot();
    s << "SANITY :" << _maxSanity << "\n";
    s << "CREDIT-POINTS :" << _creditPoints << "\n";
    for( auto &entry : _usableTowers){
        s << "TOWER-ENTRY :" << (int)entry << "\n";
    }
    return s.str();
}
