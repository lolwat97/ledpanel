#ifndef Clip_h
#define Clip_h

#include <Arduino.h>

// Clip types: text, gif (animated image), static image
// TODO: think of other types
enum clip_type{
    clip_text,
    clip_gif,
    clip_image
};

// Clip class, use this as a parent class?
class Clip {
    public:
        Clip(ushort type, uint length, bool active);
        Clip(ushort type, uint length);
        Clip(ushort type);
        Clip();

        bool is_active;

        void show();
    private:
        ushort _type; 
        uint _length; 

        void show_text();
        void show_gif();
        void show_image();
};

#endif