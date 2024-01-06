#include "U8glib.h"
#include "player.h"

constexpr int BUTTON_PIN = 2;
constexpr uint32_t GAME_OVER_SCREEN_DURATION = 2000;
const char *GAME_OVER_TEXT = "GAME OVER!";

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST | U8G_I2C_OPT_NO_ACK);
Player player;
uint32_t gameOverScreenTimer = 0;

void setup() {
	Serial.begin(9600);
	u8g.setFont(u8g_font_6x10);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LED_BUILTIN, OUTPUT);
}

void game_over() {
	gameOverScreenTimer = 1;
	player = {};
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

	if(gameOverScreenTimer != 0) {
		const uint8_t offset = u8g.getStrWidth(GAME_OVER_TEXT);
		u8g.firstPage();
		do {
			u8g.drawStr(64 - offset / 2, 22, GAME_OVER_TEXT);
		} while(u8g.nextPage());

		gameOverScreenTimer += deltaTime;

		if(gameOverScreenTimer < GAME_OVER_SCREEN_DURATION) {
			return;
		}

		gameOverScreenTimer = 0;
	}

	if (isBtnPressed) {
		player.jump();
	}

	player.update(deltaTime);
	if(player.is_dead()) {
		game_over();
		return;
	}

	u8g.firstPage();
	do {
		player.draw(u8g);
	} while (u8g.nextPage());
}