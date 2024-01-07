#include "push_button.h"

PushButton::PushButton(uint8_t pin) : m_Pin(pin) {
    pinMode(pin, INPUT_PULLUP);
    m_State = digitalRead(pin);
}

bool PushButton::is_pressed() {
    bool value = digitalRead(m_Pin);
    bool result = value == LOW && m_State == HIGH;
    m_State = value;
    return result;
}