//
// Created by banoodle on 10.05.23.
//
#include "introstate.h"
void IntroState::Init()
{
    if( !font )
    {
        font = TTF_OpenFont( BasePath "asset/font/RobotoSlab-Bold.ttf", 24 );
        TTF_SetFontHinting( font, TTF_HINTING_LIGHT );
        if( !font )
            cerr << "TTF_OpenFont failed: " << TTF_GetError() << endl;
    }

    if( !image )
    {
        image = IMG_LoadTexture( render, BasePath "asset/graphic/background.png" );
        if( !image )
            cerr << "IMG_LoadTexture failed: " << IMG_GetError() << endl;
    }

    if( !music )
    {
        music = Mix_LoadMUS( BasePath "asset/music/severance.ogg" );
        if( !music )
            cerr << "Mix_LoadMUS failed: " << Mix_GetError() << endl;
        else
            Mix_PlayMusic( music, -1 );
    }
    else if( Mix_PausedMusic() )
    {
        Mix_ResumeMusic();
    }
    tcache = TextureCache::getCache(render);
    SDL_Point size = game.GetWindowSize();
    int left = size.x / 10;
    int width = left*8;
    int top = size.y / 5;
    int height = top*2;
    btn_start.set(render,"Start",30,{left,top,width,height});
    btn_exit.set(render, "Beenden",30,{left, (int)(1.5*top+height),height});
}

void IntroState::UnInit()
{
    if( !Mix_PausedMusic() )
        Mix_PauseMusic();

    // Keep everything loaded/allocated is also an option
    /*
    TTF_CloseFont( font );
    SDL_DestroyTexture( image );
    SDL_DestroyTexture( blendedText );
    font = nullptr;
    image = nullptr;
    blendedText = nullptr;
    */
}

void IntroState::Events( const u32 frame, const u32 totalMSec, const float deltaT )
{
    SDL_PumpEvents();

    Event event;
    while( SDL_PollEvent( &event ) )
    {
        if( game.HandleEvent( event ) )
            continue;

        switch( event.type )
        {
            case SDL_MOUSEMOTION:
                btn_exit.entered(event);
                btn_start.entered(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(btn_exit.clicked(event))
                    game.SetNextState(99);
                if(btn_start.clicked(event))
                    game.SetNextState(1);
                break;
            case SDL_KEYDOWN:
            {
                const Keysym & what_key = event.key.keysym;

                if( what_key.scancode == SDL_SCANCODE_F9 )
                {
                    // crash/shutdown, since State #6 does not exist
                    game.SetNextState( 99 );
                }
                else if( what_key.scancode == SDL_SCANCODE_ESCAPE )
                {
                    game.SetNextState( 0 );
                }

                break;
            }
            default:
                break;
        }
    }
}

void IntroState::Update( const u32 frame, const u32 totalMSec, const float deltaT )
{
}

void IntroState::Render( const u32 frame, const u32 totalMSec, const float deltaT )
{
    const Point & winSize = game.GetWindowSize();

    {
        const Rect dst_rect { 0, 0, winSize.x, winSize.y };
        SDL_RenderCopy( render, image, EntireRect, &dst_rect /* same result as EntireRect */ );
        btn_start.draw();
        btn_exit.draw();
    }
}