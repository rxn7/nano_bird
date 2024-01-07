#ifndef __GAME_H__
#define __GAME_H__

#include "global.h"

class Game {
public:
    virtual void loop(const uint16_t deltaTime, const bool isBtnPressed) = 0;
};

#endif