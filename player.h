#pragma once

#include "pipe.h"
#include "U8g2lib.h"

constexpr uint8_t PLAYER_POS_X = 20;
constexpr uint8_t PLAYER_WIDTH = 6;
constexpr uint8_t PLAYER_HEIGHT = 6;
constexpr uint8_t FLOOR_POS_Y = 64 - PLAYER_HEIGHT;

constexpr float GRAVITY = 0.4f * 0.001f;
constexpr float JUMP_FORCE = -GRAVITY * 200.0f;

class Player {
public:
	void update(const uint16_t deltaTime, const Pipe &pipe) {
		m_Velocity += deltaTime * GRAVITY;
		m_PosY += m_Velocity * deltaTime;

		if (m_PosY <= 0 || m_PosY >= FLOOR_POS_Y) {
			m_Dead = true;
			return;
		}

		// TODO: Check for collision
	}

	void draw(U8G2 &u8g) const {
		u8g.drawBox(PLAYER_POS_X, m_PosY, PLAYER_WIDTH, PLAYER_HEIGHT);
	}

	void jump() {
		m_Velocity = JUMP_FORCE;
	}

	inline bool is_dead() const {
		return m_Dead;
	}


private:
	bool m_Dead = false;
	float m_Velocity = 0;
	float m_PosY = 10;
};
