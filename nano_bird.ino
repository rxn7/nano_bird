#include "U8g2lib.h"
#include "player.h"
#include "pipe.h"

constexpr uint8_t BUTTON_PIN = 2;
const char *SCORE_TEXT_PREFIX = "Score: ";
const char *WAITING_FOR_INPUT_TEXT = "Tap to play";

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g(U8G2_R0);

uint8_t waitingForInputTextPosX = 0;
uint8_t scoreTextPosX = 0;

uint16_t score = 0;
bool startScreenRendered = false;
bool waitingForInput = true;
char scoreTextBuffer[14];

Player player;
Pipe pipe;

void setup() {
    strcpy(scoreTextBuffer, SCORE_TEXT_PREFIX);

    u8g.setPowerSave(true);
    u8g.begin();
    u8g.setFont(u8g2_font_profont12_tr);

    waitingForInputTextPosX = 64 - u8g.getStrWidth(WAITING_FOR_INPUT_TEXT) / 2;

    Serial.begin(9600);

	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LED_BUILTIN, OUTPUT);

    reset();
}

void reset() {
    static size_t prefixSize = strlen(SCORE_TEXT_PREFIX);
    snprintf(scoreTextBuffer + prefixSize, sizeof(scoreTextBuffer) - prefixSize, "%u", score);

    scoreTextPosX = 64 - u8g.getStrWidth(scoreTextBuffer) / 2;

    waitingForInput = true;
    startScreenRendered = false;
	score = 0;

	player = {};
    pipe.reset();

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

            u8g.drawStr(waitingForInputTextPosX, 48, WAITING_FOR_INPUT_TEXT);
            u8g.drawStr(scoreTextPosX, 32, scoreTextBuffer);

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

    pipe.update(deltaTime);
	player.update(deltaTime, pipe);

	if(player.is_dead()) {
		reset();
		goto display_and_ret;
	}

    if(!pipe.m_Scored && pipe.m_PosX + PIPE_WIDTH / 2 <= PLAYER_POS_X) {
        ++score;
        pipe.m_Scored = true;
    }

    pipe.draw(u8g);
    player.draw(u8g);

display_and_ret:
    u8g.sendBuffer();
    u8g.clearBuffer();
}