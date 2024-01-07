#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "pipe.h"

constexpr uint8_t PLAYER_POS_X = 20;
constexpr uint8_t PLAYER_WIDTH = 6;
constexpr uint8_t PLAYER_HEIGHT = 6;
constexpr uint8_t PLAYER_FLOOR_POS_Y = 64 - PLAYER_HEIGHT;

constexpr float GRAVITY = 0.4f * 0.001f;
constexpr float JUMP_FORCE = -GRAVITY * 200.0f;

class Player {
public:
	void update(const uint16_t deltaTime, const Pipe &pipe);
	void draw() const;
	void jump();

	inline bool is_dead() const {
		return m_Dead;
	}

private:
    void collision_check(const Pipe &pipe);

private:
	bool m_Dead = false;
	float m_Velocity = 0;
	uint8_t m_PosY = 10;
};

#endif