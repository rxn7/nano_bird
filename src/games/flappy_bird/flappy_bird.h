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
    Label m_ScoreLabel;

    uint16_t m_Score = 0;
    float m_ScrollSpeed = PIPE_SCROLL_SPEED;
    bool m_StartScreenRendered = false;
    bool m_WaitingForInput = true;

    Player m_Player;
    Pipe m_Pipe;
};

#endif