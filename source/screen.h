#ifndef _SCREEN_H
#define _SCREEN_H

/**
 * Abstract base class for screen objects.
 */
class Screen {
public:
    Screen() {}
    virtual ~Screen() {}
    
    virtual void tick() = 0;
    virtual void render() = 0;
};

#endif