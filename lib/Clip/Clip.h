#ifndef Clip_h
#define Clip_h

#include <Arduino.h>

enum clip_type{
    clip_text,
    clip_gif,
    clip_image
};

class Clip {
    public:
        Clip(ushort type, uint length, bool active);
        Clip(ushort type, uint length);
        Clip(ushort type);
        Clip();
    private:
        bool _active;
        ushort _type; 
        uint _length; 
};

#endif