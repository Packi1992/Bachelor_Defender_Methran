//
// Created by banoodle on 07.06.23.
//

#include "player.h"

bool Player::load(const Vector<string> &data) {
    bool SanityLoaded = false;
    // now we need to load lines out of Map string
    for(const string& line: data) {
        if (line.substr(0, 7) == ("SANITY :")) {
            _sanity = _maxSanity = (int) strtol(line.substr(7).c_str(), nullptr, 10);
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
