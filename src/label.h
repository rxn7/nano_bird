#ifndef __LABEL_H__
#define __LABEL_H__

#include "global.h"

class Label {
public:
    Label(const uint8_t y, U8G2 &u8g) : m_U8g(u8g), m_PosY(y) {
    }

    void set_text(const char *text) {
        m_Text = text;
        m_PosX = 64 - m_U8g.getStrWidth(text) / 2;
    }

    inline void render() {
        m_U8g.drawStr(m_PosX, m_PosY, m_Text);
    }

private:
    const char *m_Text;
    uint8_t m_PosX;
    uint8_t m_PosY;
    U8G2 &m_U8g;
};

#endif