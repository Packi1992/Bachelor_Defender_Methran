//
// Created by banoodle on 10.05.23.
//

#include "introstate.h"
void IntroState::Init()
{
    if( !image )
    {
        image = t_cache->getTexture(BasePath "asset/graphic/bg-main.png");
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

    SDL_Point size = game.GetWindowSize();
    std::cout << "window size " << size.x << " " << size.y << std::endl;
    int left = size.x / 10;
    int width = left*8;
    int top = size.y / 5;
    int height = top*2;
    btn_start.set("Start",30,{left,top,width,height});
    btn_editor.set("Editor",30,{left, (int)(1.5*top+height),width, height});
    btn_exit.set( "Beenden",30,{left, (int)(2.5*top+2*height),width, height});
}

void IntroState::UnInit()
{
    if( !Mix_PausedMusic() )
        Mix_PauseMusic();
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
                if(btn_editor.clicked(event))
                    game.SetNextState(2);
                break;
            case SDL_KEYDOWN:
            {
                const Keysym & what_key = event.key.keysym;

                if( what_key.scancode == SDL_SCANCODE_F9 )
                {
                    // crash/shutdown, since State #99 does not exist
                    game.SetNextState( 99 );
                }
                else if( what_key.scancode == SDL_SCANCODE_ESCAPE )
                    game.SetNextState( 0 );
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
    updateBtnSize(winSize);
    {
        const Rect dst_rect { 0, 0, winSize.x, winSize.y };
        SDL_RenderCopy( render, image, EntireRect, &dst_rect /* same result as EntireRect */ );
        btn_start.draw();
        btn_editor.draw();
        btn_exit.draw();
    }
}

void IntroState::updateBtnSize(const Point &size) {
    int left = size.x / 10*2;
    int width = left*3;
    int top = size.y / 5*2;
    int height = top/3;
    btn_start.setSize({left,top,width,height});
    btn_editor.setSize({left, (int)(top+height*1.5),width, height});
    btn_exit.setSize({left, (int)(top+height*3),width, height});
}
