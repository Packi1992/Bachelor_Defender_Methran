//
// Created by banoodle on 07.06.23.
//

#include "player.h"

bool Player::load(const Vector<string> &data) {
    bool SanityLoaded = false;
    // now we need to load lines out of Map string
    for(const string& line: data) {
        if (line.substr(0, 8) == ("SANITY :")) {
            _maxSanity = (int) strtol(line.substr(8).c_str(), nullptr, 10);
            _sanity = _maxSanity;
            SanityLoaded = true;
        }
    }
    return SanityLoaded;
}

std::string Player::save() {
    // save PlayerData
    std::stringstream s;
    //checkPlayerStartSpot();
    s << "SANITY :" << _maxSanity << "\n";

    return s.str();
}
