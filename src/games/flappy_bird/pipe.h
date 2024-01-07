#ifndef __PIPE_H__
#define __PIPE_H__

#include "../../global.h"

constexpr uint8_t PIPE_GAP_SIZE = 28;
constexpr uint8_t PIPE_WIDTH = 15;
constexpr uint8_t PIPE_GAP_MARGIN = 5;
constexpr float PIPE_SCROLL_SPEED = 0.05f;
constexpr float PIPE_SCROLL_SPEED_INCREMENT = 0.01f;

class Pipe {
public:
    Pipe() {
        reset();
    }

    void reset();
    void update(const uint16_t deltaTime, const float scrollSpeed);

    void draw() const;

public:
    bool m_Scored = false;
    float m_PosX = 128;
    uint8_t m_GapOrigin = 0;
};

#endif