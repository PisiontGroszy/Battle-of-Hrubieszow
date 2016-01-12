#ifndef PREINIT_H_INCLUDED
#define PREINIT_H_INCLUDED

sf::Image tmpScreenshotImage;

int screenCornerX = 0;
int screenCornerY = 0;

sf::Vector2f screenCenter;

float mapCornerX = 0;
float mapCornerY = 0;

float map2CornerX = 0;
float map2CornerY = 0;

float map3CornerX = 0;
float map3CornerY = 0;

float mapControlCornerX = 0;
float mapControlCornerY = 0;

sf::Sprite enemyArrow;
sf::Sprite infoBackground;

sf::Sprite HPbar;
sf::Sprite shieldBar;
sf::Sprite regainingShieldBar;
sf::Sprite ammoBar;
sf::Sprite noAmmoBar;

int screenX = sf::VideoMode::getDesktopMode().width;
int screenY = sf::VideoMode::getDesktopMode().height;

int generatedTiles = 0;
int generatedMinX = -1500;
int generatedMaxX = 3000;

int generatedMinY = -1500;
int generatedMaxY = 3000;

sf::View view;
float viewScale;

sf::RenderWindowStream app;
sf::Event event;

sf::Font roboto;
sf::Font bitFont;

sf::Text FPStext;
sf::Text HPtext;
sf::Text XPtext;
sf::Text shieldText;
sf::Text ammoText;
sf::Text releaseButton;

sf::Vector2f direction;

float counter = 0.f;
int mouseWheelDelta = 0;

bool quit = false;

bool gamePause;
bool newTiles = false;

void unpause()
{
    gamePause = false;
}

long long int Time = 0;

void gameOver()
{
    app.close();
    app.soundsManager.getMusic() -> stop();
    long long int Seconds = (Time % 3600) / 60;
    Time -= Time % 3600;
    cout << "Time: " << Time / 3600 << "m, " << Seconds << 's';
    exit(0);
}

sf::FloatRect screenRect;

void drawer();

sf::Clock controlClock;
float timeModifier;
float currentFrameTime;
float perfectFrameTime = 1.f / 60;
int framerateControl;

sf::textureManager textureManager;

void textureManagerInit()
{
    textureManager.add("assets/graphics/UI/mainMenu/play1.png", false);
    textureManager.add("assets/graphics/UI/mainMenu/play2.png", false);

    textureManager.add("assets/graphics/UI/mainMenu/quit1.png", false);
    textureManager.add("assets/graphics/UI/mainMenu/quit2.png", false);

    textureManager.add("assets/graphics/UI/mainMenu/settings1.png");
    textureManager.add("assets/graphics/UI/mainMenu/settings2.png");

    textureManager.add("assets/graphics/UI/game/pauseCursor.png", true);
    textureManager.add("assets/graphics/UI/game/soul.png", false);

    textureManager.add("assets/graphics/UI/game/settings1.png");
    textureManager.add("assets/graphics/UI/game/settings2.png");

    textureManager.add("assets/graphics/UI/game/continue1.png");
    textureManager.add("assets/graphics/UI/game/continue2.png");

    textureManager.add("assets/graphics/UI/game/back1.png");
    textureManager.add("assets/graphics/UI/game/back2.png");

    textureManager.add("assets/graphics/UI/game/quit1.png");
    textureManager.add("assets/graphics/UI/game/quit2.png");
}
vector <float> frameTimes;

bool shouldRender(sf::Vector2f p)
{
    if(screenRect.contains(p))
        return true;

    return false;
}

char * date()
{
    time_t now = time(0);
    char * d = ctime(&now);

    for(int i = 0; d[i] != '\0'; i++)
    {
        if(d[i] == '\n')
        {
            d[i] = '\0';
            break;
        }
    }

    return d;
}
#endif // PREINIT_H_INCLUDED
