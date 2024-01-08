#include "flappy_bird.h"

static const char *START_SCREEN_TEXT_1 = "Flappy Bird";
static const char *START_SCREEN_TEXT_2 = "Tap to play";

FlappyBird::FlappyBird() : m_ScoreLabel(64) {
    reset();
}

void FlappyBird::loop(const uint16_t deltaTime, const bool isBtnPressed) {
	if(m_WaitingForInput) {
        // Render the start screen only once, it doesn't change
        if(!m_StartScreenRendered) {
            m_StartScreenRendered = true;

            u8g.drawStr(32, 12, START_SCREEN_TEXT_1);
            u8g.drawStr(32, 36, START_SCREEN_TEXT_2);
            m_ScoreLabel.render();

            swapDisplayBuffer = true;
            return;
        }

        swapDisplayBuffer = false;

        if (isBtnPressed) {
            reset();
            m_WaitingForInput = false;
        }

        // Save some power
        delay(50);
        return;
	}

    swapDisplayBuffer = true;

	if (isBtnPressed) {
		m_Player.jump();
	}

    m_Pipe.update(deltaTime, m_ScrollSpeed);
	m_Player.update(deltaTime, m_Pipe);

	if(m_Player.is_dead()) {
		reset();
        return;
	}

    if(!m_Pipe.m_Scored && m_Pipe.m_PosX + PIPE_WIDTH / 2 <= PLAYER_POS_X) {
        set_score(m_Score + 1);
        m_Pipe.m_Scored = true;
        m_ScrollSpeed += PIPE_SCROLL_SPEED_INCREMENT;
    }

    m_ScoreLabel.render();

    m_Pipe.draw();
    m_Player.draw();
}

void FlappyBird::reset() {
    m_ScrollSpeed = PIPE_SCROLL_SPEED;

    m_WaitingForInput = true;
    m_StartScreenRendered = false;
    set_score(0);

	m_Player = {};
    m_Pipe.reset();
}

void FlappyBird::set_score(const uint16_t newScore) {
    m_Score = newScore;

    static char scoreTextBuffer[13];
    snprintf_P(scoreTextBuffer, sizeof(scoreTextBuffer), PSTR("Score: %u"), m_Score);
    m_ScoreLabel.set_text(scoreTextBuffer);
}
