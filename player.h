#pragma once

#include "U8glib.h"

constexpr uint8_t PLAYER_SIZE_X = 6;
constexpr uint8_t PLAYER_SIZE_Y = 6;
constexpr uint8_t FLOOR_POS_Y = 64 - PLAYER_SIZE_Y;

constexpr float GRAVITY = 0.4f * 0.001f;
constexpr float JUMP_FORCE = -GRAVITY * 200.0f;

class Player {
public:
	void update(const uint16_t deltaTime) {
	m_Velocity += deltaTime * GRAVITY;
	float positionChange = m_Velocity * deltaTime;

	if (positionChange > UINT8_MAX - m_PosY || m_PosY + positionChange >= FLOOR_POS_Y) {
		m_Dead = true;
		return;
	}

	m_PosY += positionChange;
	}

	void draw(U8GLIB &u8g) {
		u8g.drawBox(m_PosX, m_PosY, PLAYER_SIZE_X, PLAYER_SIZE_Y);
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
	uint8_t m_PosY = 10;
	uint8_t m_PosX = 20;
};
