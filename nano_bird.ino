#include "src/games/flappy_bird/flappy_bird.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g(U8G2_R0);
bool swapDisplayBuffer = true;
Game *game;

void set_game(Game *newGame) {
    if(game != nullptr) {
        delete game;
    }

    game = newGame;
}

void setup() {
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LED_BUILTIN, OUTPUT);

    u8g.setPowerSave(true);
    u8g.begin();
    u8g.setFont(u8g2_font_profont12_tr);

    set_game(new FlappyBird());
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

    game->loop(deltaTime, isBtnPressed);

    if(swapDisplayBuffer) {
        u8g.sendBuffer();
        u8g.clearBuffer();
    }
}