#ifndef __FLAPPY_BIRD_H__
#define __FLAPPY_BIRD_H__

#include "player.h"
#include "../../label.h"
#include "../../game.h"

class FlappyBird : public Game {
public:
    FlappyBird();
    void loop(const uint16_t deltaTime, const bool isBtnPressed) override;

private:
    void reset();
    void set_score(const uint16_t newScore);

private:
    Label scoreStartScreenLabel;
    Label waitingForInputLabel;
    Label scoreLabel;

    uint16_t score = 0;
    float scrollSpeed = PIPE_SCROLL_SPEED;
    bool startScreenRendered = false;
    bool waitingForInput = true;

    Player player;
    Pipe pipe;
};

#endif