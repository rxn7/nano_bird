#include "../../global.h"
#include "pipe.h"

void Pipe::reset() {
    m_PosX = 128;
    m_GapOrigin = rand() % (64 - PIPE_GAP_SIZE- PIPE_GAP_MARGIN) + PIPE_GAP_MARGIN;
    m_Scored = false;
}

void Pipe::update(const uint16_t deltaTime, const float scrollSpeed) {
    m_PosX -= scrollSpeed * deltaTime;
    if(m_PosX <= -PIPE_WIDTH) {
        reset();
    }
}

void Pipe::draw() const {
    // Render top pipe
    u8g.drawBox(m_PosX, 0, PIPE_WIDTH, m_GapOrigin);

    // Render bottom pipe
    const uint8_t gapEnd = m_GapOrigin + PIPE_GAP_SIZE;
    u8g.drawBox(m_PosX, gapEnd, PIPE_WIDTH, 64 - gapEnd);
}