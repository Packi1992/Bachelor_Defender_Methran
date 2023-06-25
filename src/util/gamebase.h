
#ifndef SDL_GAMEBASE_H
#define SDL_GAMEBASE_H

#include "global.h"

// globals - introoduced at everything global
extern Renderer *render;

// TextureCache
class AudioHandler;

extern AudioHandler *audioHandler;

class TextureCache;

extern TextureCache *t_cache;

class RenderHelper;

extern RenderHelper *rh;

class Game;

extern Game *pGame;

class Map;

extern Map *pMap;

class Config;
extern Config *config;

extern Point offset;
extern Point windowSize;
extern int scale;

// Timer
extern float deltaTF;
extern Duration deltaT;
extern u32 totalMSec;
extern u32 frame;

class GameState;

class Game {
protected:
    Window *window;

    bool isRunning = true;

    GameStates currentStateIdx = GS_MainMenu;
    GameStates nextStateIdx = GS_MainMenu;

    GameState *currentState = nullptr;
    Vector<GameState *> allStates;


public:
    bool isGameover();
    static void zoomScreen(SDL_Event event);

    static void scrollScreen(SDL_Event event);

    static Point getMousePos();

    static bool onScreen(Rect dstRect);

    [[nodiscard]]       bool IsRunning() const { return isRunning; }

    explicit Game(
            const char *windowTitle = "SDL Game",
            const Point windowSize = Point{1024, 720},
            const bool vSync = true);

    Game(const Game &) = delete;

    Game(Game &&) = delete;

    Game &operator=(const Game &) = delete;

    Game &&operator=(Game &&) = delete;

    virtual ~Game();

    virtual bool HandleEvent(Event event);

    virtual int Run();

    virtual void SetNextState(GameStates gs) { nextStateIdx = gs; }


protected:
    virtual void ActivateNextState();


    /// Performance
public:
    // All output msec per frame, see: http://renderingpipeline.com/2013/02/fps-vs-msecframe/
    enum class PerformanceDrawMode {
        None,
        Title,      // averaged and only updated every 250ms
        OStream,    // averaged and only updated every 1000ms
        //Overlay,    // Maybe Overlay mode?!
    };

    void SetPerfDrawMode(PerformanceDrawMode mode) noexcept { perfDrawMode = mode; }

protected:
    PerformanceDrawMode perfDrawMode = PerformanceDrawMode::Title;
    u32 lastPerfInfoFrame = 0;
    TimePoint lastPerfInfoTime = Clock::now();
    Duration accumulatedNeeded = Duration::zero();

    [[nodiscard]]
    float AverageMSecPerFrame() const;

    void ResetPerformanceInfo(const TimePoint current);

    void OutputPerformanceInfo(const TimePoint current, const Duration needed);
};

class GameState {
protected:
    Game &game;

public:
    [[nodiscard]] GameStates getType() const;
    GameStates _type = GS_Close;
    bool _gameover = false;
    [[nodiscard]] virtual bool IsFPSLimited() const { return true; }

    [[nodiscard]] virtual Color GetClearColor() const { return Color{0, 0, 0, SDL_ALPHA_OPAQUE}; }

    explicit GameState(Game &&game) = delete; // prevent taking an rvalue
    explicit GameState(Game &game, GameStates gs)
            : game(game) {
        _type = gs;
    }

    GameState(const GameState &) = delete;

    GameState(GameState &&) = delete;

    GameState &operator=(const GameState &) = delete;

    GameState &&operator=(GameState &&) = delete;

    virtual ~GameState() = default;

    virtual void Init() {}

    virtual void UnInit() {}

    virtual void Events() = 0;

    virtual void Update() = 0;

    virtual void Render() = 0;
};
#endif
