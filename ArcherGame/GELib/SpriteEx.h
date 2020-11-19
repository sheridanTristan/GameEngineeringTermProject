#pragma once
#include "SDL.h"
#include <iostream>
#include <map>
#include <functional>
#define FLIPPED_HORIZONTAL(flipped) flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
#define FLIPPED_VERTICAL(flipped) flipped ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE
//this base class will render just one static sprite

class SpriteEx
{
protected:
    SDL_Rect spriteSrcRect; //which part of the spritesheet we would like to render
    SDL_Rect spriteDestRect; //the position on the screen we would like to render this sprite at
    SDL_Texture* texture;
    //first for horizontal second for vertical
    std::pair<bool, bool> flippedDimensions;
    bool animationReset;
    bool isFlipped;
    double angle;//the angle to display sprite (in degrees)
    double m_X, //x coord
        m_Y, //Y coord
        m_DX, //the change in x coord
        m_DY, //the change in Y coordinate
        m_dSpeed; //speed in pixels to move per change
    double m_dRadius; //radius of the sprite's circle bounds
    std::pair<int, int> CalculateNormal(int x, int y);
    std::pair<int, int> MoveTowards(int x, int y, float speed);

public:
    SpriteEx() {}
    SpriteEx(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect dstRect)
    {
        isFlipped = false;
        texture = tex;
        spriteSrcRect = srcRect;
        spriteDestRect = dstRect;
    }
    void Render();
    void UpdateDestRect();
    double GetRadius() { return m_dRadius; }
    double GetX() { return m_X; }
    double GetY() { return m_Y; }
};

struct AnimStateDefinition
{
    short rowIndex;
    short frames;
    short time;
    bool isLoopable = false;
    bool isInterrupt = true;

    std::function<void()> callbackOnComplete;
    std::function<void()> callbackOnStart;
    void AddCallbackOnComplete(std::function<void()> cb) {
        callbackOnComplete = cb;
    }
    void AddCallbackOnStart(std::function<void()> cb) {
        callbackOnStart = cb;
    }

    AnimStateDefinition() {}
    AnimStateDefinition(short ri, short f, short t, bool loop = false,
        bool interrupt = true)
        : rowIndex(ri), frames(f), time(t), isLoopable(loop),
        isInterrupt(interrupt)
    {}

};
//this is the animated version of the Sprite class
class SpriteExAnimated : public SpriteEx
{
private:
    void AnimateRange(AnimStateDefinition asd);
    void Animate();
protected:
    int
        // m_iSprite = 0, //which sprite to display for animation
        // m_iSpriteMax, //how many sprites in total for this animation
        m_iFrame = 0, //which frame we are at now
        m_iFrameMax; //number of frames for this sprite
    Uint32 lastUpdate;
    std::string currentState;
    //Stores various animation states for this spritesheet
    std::map<std::string, AnimStateDefinition> animStates;
    bool isAnimFinished;
public:
    void AddAnimState(std::string stateName, AnimStateDefinition asd);
    void PlayState(std::string stateName);
    SpriteExAnimated(SDL_Texture* tex, double x, double y,
        double a);
    std::string GetCurrentState() { return currentState; }
    int GetCurrentAnimFrame() { return m_iFrame; }
    std::map<std::string, AnimStateDefinition> getAnimStates() { return animStates; };
    bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
    {
        return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));

    }

};

