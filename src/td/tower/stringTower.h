//
// Created by dex on 6/19/23.
//

#ifndef SDL_BACHELORDEFENDER_STRINGTOWER_H
#define SDL_BACHELORDEFENDER_STRINGTOWER_H


#include "tower.h"

class StringTower : public Tower {
    public:
        explicit StringTower(Point pos);

        // Draws the tower
        void Render() override;

        // Place Tower on Map
        void Update() override;

        ~StringTower() override;

        int getCosts() override;

        void setCosts(int cp) override;

        // init the Menu
        void showMenu(Gui **focus) override;

        bool upgrade() override;

    private:
        static int _creditPointCosts;
        StringProjectile _stringProjectile;
        Vector<string> strText = {"#Hello_World!#", "###The_Cake###", "###Is_a_Lie###", "###Pa$$W0rd###","Zweiundvierzig"};
    };


#endif //SDL_BACHELORDEFENDER_STRINGTOWER_H
