#ifndef __LABEL_H__
#define __LABEL_H__

#include "global.h"

class Label {
public:
    Label(const uint8_t y, const char *text = nullptr); 

    void set_text(const char *text);
    void render();

private:
    const char *m_Text;
    uint8_t m_PosX;
    uint8_t m_PosY;
};

#endif