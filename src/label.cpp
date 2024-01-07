#include "label.h"

Label::Label(const uint8_t y, const char *text) : m_PosY(y) {
    if(text != nullptr) {
        set_text(text);
    }
}

void Label::set_text(const char *text) {
    m_Text = text;
    m_PosX = 64 - u8g.getStrWidth(text) / 2;
}

void Label::render() {
    if(m_Text == nullptr)
        return;

    u8g.drawStr(m_PosX, m_PosY, m_Text);
}