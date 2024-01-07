#ifndef __PUSH_BUTTON_H__
#define __PUSH_BUTTON_H__

#include "global.h"

class PushButton {
    public:
        PushButton(uint8_t pin);
        bool is_pressed();

    private:
        bool m_State;
        uint8_t m_Pin;
};

#endif