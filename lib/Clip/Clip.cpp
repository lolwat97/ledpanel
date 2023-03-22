#include <Arduino.h>

#include <Clip.h>

// Default length of a clip in ms
#define DEFAULT_LENGTH 1000

Clip::Clip(ushort type, uint length, bool active) {
    is_active = active;
    _type = type;
    _length = length;
};

Clip::Clip(ushort type, uint length) : Clip(type, length, false) {}

Clip::Clip(ushort type) : Clip(type, DEFAULT_LENGTH, false) {}

Clip::Clip() : Clip(clip_text, DEFAULT_LENGTH, false) {}

void Clip::show(void* screenptr) {
    Serial.printf("I'm a type %d clip, ", _type);
    Serial.print(is_active?"I'm active, ":"I'm inactive, ");
    Serial.printf("I have a length of %d ms\n", _length);
    switch (_type)
    {
    case clip_text:
        show_text(screenptr);
        break;
    case clip_image:
        show_image(screenptr);
        break;
    case clip_gif:
        show_gif(screenptr);
        break;
    default:
        Serial.println("ERROR: Empty or unrecognized clip type! This should not happen!");
        break;
    }
};

void Clip::show_text(void* screenptr) {
    Serial.println("INFO: Showing some text");
    delay(_length);
};

void Clip::show_image(void* screenptr) {
    Serial.println("INFO: Showing an image");
    delay(_length);
};

void Clip::show_gif(void* screenptr) {
    ushort frames = 8;
    ushort repeat = 3;
    uint frame_length = _length/(frames*repeat);
    for (ushort i = 0; i < repeat; i++)
    {
        for (ushort j = 0; j < frames; j++)
        {
            Serial.printf("INFO: Showing gif frame %d\n", j);
            delay(frame_length);
        }
    }
}