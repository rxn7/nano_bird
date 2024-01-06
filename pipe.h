#pragma once

#include "U8g2lib.h"

constexpr uint8_t PIPE_GAP_SIZE = 32;
constexpr uint8_t PIPE_WIDTH = 15;
constexpr uint8_t PIPE_GAP_MARGIN = 5;
constexpr float PIPE_SCROLL_SPEED = 0.05f;

class Pipe {
public:
    Pipe() {
        reset();
    }

    void reset() {
        m_PosX = 128;
        m_GapOrigin = rand() % (64 - PIPE_GAP_SIZE- PIPE_GAP_MARGIN) + PIPE_GAP_MARGIN;
        m_Scored = false;
    }

    void update(const uint16_t deltaTime) {
        m_PosX -= PIPE_SCROLL_SPEED * deltaTime;
        if(m_PosX <= -PIPE_WIDTH) {
            reset();
        }
    }

    void draw(U8G2 &u8g) const {
        // Render top pipe
        u8g.drawBox(m_PosX, 0, PIPE_WIDTH, m_GapOrigin);

        const uint8_t gapEnd = m_GapOrigin + PIPE_GAP_SIZE;

        // Render bottom pipe
        u8g.drawBox(m_PosX, gapEnd, PIPE_WIDTH, 64 - gapEnd);
    }

public:
    bool m_Scored = false;
    float m_PosX = 128;

private:
    uint8_t m_GapOrigin = 0;
};