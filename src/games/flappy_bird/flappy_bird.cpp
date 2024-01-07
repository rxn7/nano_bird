#include "flappy_bird.h"

FlappyBird::FlappyBird() : scoreStartScreenLabel(32), waitingForInputLabel(48, "Tap to play"), scoreLabel(64) {
    reset();
}

void FlappyBird::loop(const uint16_t deltaTime, const bool isBtnPressed) {
	if(waitingForInput) {
        // Render the start screen only once, it doesn't change
        if(!startScreenRendered) {
            startScreenRendered = true;

            waitingForInputLabel.render();
            scoreStartScreenLabel.render();

            swapDisplayBuffer = true;
            return;
        }

        swapDisplayBuffer = false;

        if (isBtnPressed) {
            reset();
            waitingForInput = false;
        }

        // Save some power
        delay(50);
        return;
	}

    swapDisplayBuffer = true;

	if (isBtnPressed) {
		player.jump();
	}

    pipe.update(deltaTime, scrollSpeed);
	player.update(deltaTime, pipe);

	if(player.is_dead()) {
		reset();
        return;
	}

    if(!pipe.m_Scored && pipe.m_PosX + PIPE_WIDTH / 2 <= PLAYER_POS_X) {
        set_score(score + 1);
        pipe.m_Scored = true;
        scrollSpeed += PIPE_SCROLL_SPEED_INCREMENT;
    }

    scoreLabel.render();

    pipe.draw();
    player.draw();
}

void FlappyBird::reset() {
    static char scoreStartScreenTextBuffer[14] = "\0";
    snprintf(scoreStartScreenTextBuffer, sizeof(scoreStartScreenTextBuffer), "Score: %u", score);
    scoreStartScreenLabel.set_text(scoreStartScreenTextBuffer);

    scrollSpeed = PIPE_SCROLL_SPEED;

    waitingForInput = true;
    startScreenRendered = false;
    set_score(0);

	player = {};
    pipe.reset();
}

void FlappyBird::set_score(const uint16_t newScore) {
    score = newScore;
    static char scoreTextBuffer[6] = "\0";
    snprintf(scoreTextBuffer, sizeof(scoreTextBuffer), "%u", score);
    scoreLabel.set_text(scoreTextBuffer);
}
