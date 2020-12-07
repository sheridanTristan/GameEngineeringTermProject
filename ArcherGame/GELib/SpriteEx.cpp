#include "GameEngine.h"
void SpriteEx::Render()
{
    SDL_RendererFlip flip = FLIPPED_HORIZONTAL(flippedDimensions.first) | FLIPPED_VERTICAL(flippedDimensions.second);
    if (SDL_RenderCopyEx(GameEngine::Instance()->GetRenderer(), texture,
        &spriteSrcRect, &spriteDestRect, angle, nullptr, flip) == 0)
    {
        // std::cout << "Success...\n";
    }
    else
    {
        std::cout << "Failed to render..\n";
    }
}
SpriteExAnimated::SpriteExAnimated(SDL_Texture* tex, double x, double y,
    double a)
{
    isAnimFinished = false;
    texture = tex;
    m_X = x;
    m_Y = y;
    angle = a;
}
bool SpriteExAnimated::CheckOutOfBounds()
{
    SDL_Surface* surface = SDL_GetWindowSurface(GameEngine::Instance()->GetWindow());

    return (spriteDestRect.x > surface->w || spriteDestRect.x < 0) || (spriteDestRect.y > surface->h || spriteDestRect.y < 0);
        
    
}
void SpriteExAnimated::Animate()
{
    m_iFrame++;
    if (m_iFrame >= m_iFrameMax)
    {
        if (animStates[currentState].callbackOnComplete != nullptr)
            animStates[currentState].callbackOnComplete();
        isAnimFinished = true;
        m_iFrame = 0;

    }
}

void SpriteExAnimated::AnimateRange(AnimStateDefinition asd)
{
    // change the row here
    spriteSrcRect.y = (spriteSrcRect.h * asd.rowIndex);
    if (SDL_TICKS_PASSED(SDL_GetTicks(), lastUpdate + asd.time))
    {
        lastUpdate = SDL_GetTicks();
        m_iFrameMax = asd.frames;
        Animate();
    }
}
void SpriteExAnimated::PlayState(std::string stateName)
{
    /*If isInterrupt is false for the new animation being called,
    then Keep playing the previous animation as long as that previous animation is still not completed...
    */
    if (animStates[currentState].isInterrupt && !isAnimFinished)
    {
        AnimateRange(animStates[currentState]);
        return;
    }
    else if (isAnimFinished)
    {
        isAnimFinished = false;
    }
    if (currentState != stateName)
        m_iFrame = 0;
    AnimateRange(animStates[stateName]);
    currentState = stateName;
}
void SpriteEx::UpdateDestRect()
{
    spriteDestRect.x = (int)(m_X - spriteDestRect.w * 0.5f);
    spriteDestRect.y = (int)(m_Y - spriteDestRect.h * 0.5f);
}
void SpriteExAnimated::AddAnimState(std::string stateName, AnimStateDefinition asd)
{
    //animStates.insert(std::pair<std::string,AnimStateDefinition>(stateName,asd));
    animStates[stateName] = asd;
}

std::pair<int, int> SpriteEx::CalculateNormal(int x, int y)
{
    std::pair<int, int> target;
    target.first = x - (int)GetX();
    target.second = y - (int)GetY();
    std::pair<int, int> normal = { 0,0 };
    //Get magnitude
    double magnitude = sqrt((target.first * target.first) + (target.second * target.second));
    //Calculate normal
    //If the magnitude is zero then it divides by zero, which is not good
    if (magnitude != 0) {
        normal = { (int)round(target.first / magnitude), (int)round(target.second / magnitude) };

    }
    return normal;



}

std::pair<int, int> SpriteEx::MoveTowards(int x, int y, float speed)
{
    std::pair<int, int> targetNormal = CalculateNormal(x, y);
    m_X += targetNormal.first * speed;
    m_Y += targetNormal.second * speed;
    return targetNormal;
}




