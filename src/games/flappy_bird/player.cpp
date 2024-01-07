#include "player.h"
#include "../../global.h"

void Player::draw() const {
    u8g.drawBox(PLAYER_POS_X, m_PosY, PLAYER_WIDTH, PLAYER_HEIGHT);
}

void Player::update(const uint16_t deltaTime, const Pipe &pipe) {
    m_Velocity += deltaTime * GRAVITY;
    m_PosY += m_Velocity * deltaTime;

    if (m_PosY <= 0 || m_PosY >= PLAYER_FLOOR_POS_Y) {
        m_Dead = true;
        return;
    }

    collision_check(pipe);
}

void Player::jump() {
    m_Velocity = JUMP_FORCE;
}

void Player::collision_check(const Pipe &pipe) {
    if(pipe.m_PosX > PLAYER_POS_X + PLAYER_WIDTH)
        return;

    if(pipe.m_PosX + PIPE_WIDTH < PLAYER_POS_X)
        return;

    m_Dead = m_PosY + PLAYER_HEIGHT > pipe.m_GapOrigin + PIPE_GAP_SIZE || m_PosY < pipe.m_GapOrigin;
}