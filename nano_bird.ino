#include "src/games/flappy_bird/flappy_bird.h"
#include "src/push_button.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g(U8G2_R0);
Game *game;
PushButton mainButton(2);
bool swapDisplayBuffer = true;

void set_game(Game *newGame) {
    if(game != nullptr)
        delete game;

    game = newGame;
}

void setup() {
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

    game->loop(deltaTime, mainButton.is_pressed());

    if(swapDisplayBuffer) {
        u8g.sendBuffer();
        u8g.clearBuffer();
    }
}