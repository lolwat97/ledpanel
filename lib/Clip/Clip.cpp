#include <Arduino.h>

#include <Clip.h>

// Default length of a clip in ms
#define DEFAULT_LENGTH 1000

Clip::Clip(ushort type, uint length, bool active) {
    _type = type;
    is_active = active;
    _length = length;
};

Clip::Clip(ushort type, uint length) : Clip(type, length, false) {}

Clip::Clip(ushort type) : Clip(type, DEFAULT_LENGTH, false) {}

Clip::Clip() : Clip(clip_text, DEFAULT_LENGTH, false) {}

void Clip::show() {
    Serial.printf("I'm a type %d clip, ", _type);
    Serial.print(is_active?"I'm active, ":"I'm inactive, ");
    Serial.printf("I have a length of %d ms\n", _length);
    delay(_length);
}