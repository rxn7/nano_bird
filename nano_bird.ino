#include <U8g2lib.h>

#include "player.h"
#include "pipe.h"
#include "label.h"

constexpr uint8_t BUTTON_PIN = 2;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g(U8G2_R0);

Label scoreStartScreenLabel(32, u8g);
Label waitingForInputLabel(48, u8g);
Label scoreLabel(64, u8g);

uint16_t score = 0;
float scrollSpeed = PIPE_SCROLL_SPEED;
bool startScreenRendered = false;
bool waitingForInput = true;

Player player;
Pipe pipe;

void setup() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LED_BUILTIN, OUTPUT);

    u8g.setPowerSave(true);
    u8g.begin();
    u8g.setFont(u8g2_font_profont12_tr);

    waitingForInputLabel.set_text("Tap to play");

    reset();
}

void reset() {
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

void set_score(const uint8_t newScore) {
    score = newScore;
    static char scoreTextBuffer[6] = "\0";
    snprintf(scoreTextBuffer, sizeof(scoreTextBuffer), "%u", score);
    scoreLabel.set_text(scoreTextBuffer);
}

void loop() {
	static uint32_t lastFrameTime = millis();
	const uint32_t now = millis();
	const uint16_t deltaTime = now - lastFrameTime;
	lastFrameTime = now;

	const bool btnValue = digitalRead(BUTTON_PIN);
	static bool lastBtnValue = HIGH;
	const bool isBtnPressed = !btnValue && lastBtnValue;
	lastBtnValue = btnValue;

	if(waitingForInput) {
        // Render the start screen only once, it doesn't change
        if(!startScreenRendered) {
            startScreenRendered = true;

            waitingForInputLabel.render();
            scoreStartScreenLabel.render();

            goto display_and_ret;
        }

        if (isBtnPressed) {
            reset();
            waitingForInput = false;
        }

        // Save some power
        delay(50);

        return;
	}

	if (isBtnPressed) {
		player.jump();
	}

    pipe.update(deltaTime, scrollSpeed);
	player.update(deltaTime, pipe);

	if(player.is_dead()) {
		reset();
		goto display_and_ret;
	}


    if(!pipe.m_Scored && pipe.m_PosX + PIPE_WIDTH / 2 <= PLAYER_POS_X) {
        set_score(score + 1);
        pipe.m_Scored = true;
        scrollSpeed += PIPE_SCROLL_SPEED_INCREMENT;
    }

    scoreLabel.render();

    pipe.draw(u8g);
    player.draw(u8g);

display_and_ret:
    u8g.sendBuffer();
    u8g.clearBuffer();
}