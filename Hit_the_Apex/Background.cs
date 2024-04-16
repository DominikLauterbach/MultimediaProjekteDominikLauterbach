using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
namespace GGD_Template;

public class background : GameObject
{
    private const int BACKGROUND_TILING_X = 1;

    private const int BACKGROUND_TILING_Y = 1;

    public List<IntRect> borderlist = new List<IntRect>();
    public List<IntRect> startFinishlist = new List<IntRect>();
    public List<IntRect> checkpointlist = new List<IntRect>();
    public List<IntRect> checkpointlist1 = new List<IntRect>();
    public Sprite backgroundSprite;

    public IntRect CollisionRect { get; private set; }

    public override void Initialize()
    {

        Texture backgroundTexture = new Texture("./Formula 1 car and trackset/Assets/track.png");

        backgroundSprite = new Sprite(backgroundTexture);

        backgroundSprite.Position = new Vector2f(0, 0);




        backgroundSprite.TextureRect = new IntRect
        (
            0, 0,
            (int)(backgroundTexture.Size.X / BACKGROUND_TILING_X),
            (int)(backgroundTexture.Size.Y / BACKGROUND_TILING_Y)
        );

        backgroundSprite.Scale = new Vector2f(4f, 4f);

        backgroundSprite.Position += new Vector2f(0, 0);

        borderlist.Add(new IntRect(1000, 2400, 2000, 100));
        borderlist.Add(new IntRect(1150, 1680, 1500, 510));
        borderlist.Add(new IntRect(2250, 1300, 1100, 650));
        borderlist.Add(new IntRect(2600, 1900, 400, 170));
        borderlist.Add(new IntRect(890, 2350, 100, 100));
        borderlist.Add(new IntRect(830, 2300, 100, 100));
        borderlist.Add(new IntRect(790, 2200, 100, 100));
        borderlist.Add(new IntRect(760, 2100, 100, 100));
        borderlist.Add(new IntRect(745, 2000, 100, 100));
        borderlist.Add(new IntRect(740, 1900, 100, 100));
        borderlist.Add(new IntRect(730, 1800, 100, 100));
        borderlist.Add(new IntRect(715, 1700, 100, 100));
        borderlist.Add(new IntRect(710, 1600, 100, 100));
        borderlist.Add(new IntRect(690, 1500, 100, 100));
        borderlist.Add(new IntRect(680, 1400, 100, 100));
        borderlist.Add(new IntRect(670, 1300, 100, 100));
        borderlist.Add(new IntRect(660, 1200, 100, 100));
        borderlist.Add(new IntRect(650, 1100, 100, 100));
        borderlist.Add(new IntRect(640, 1000, 100, 100));
        borderlist.Add(new IntRect(620, 900, 100, 100));
        borderlist.Add(new IntRect(600, 800, 100, 100));
        borderlist.Add(new IntRect(580, 700, 100, 100));
        borderlist.Add(new IntRect(565, 600, 100, 100));
        borderlist.Add(new IntRect(545, 500, 100, 100));
        borderlist.Add(new IntRect(540, 400, 100, 100));
        borderlist.Add(new IntRect(540, 300, 100, 100));
        borderlist.Add(new IntRect(550, 200, 100, 100));
        borderlist.Add(new IntRect(550, 200, 100, 100));
        borderlist.Add(new IntRect(600, 150, 100, 100));
        borderlist.Add(new IntRect(650, 100, 100, 100));
        borderlist.Add(new IntRect(700, 50, 100, 100));
        borderlist.Add(new IntRect(740, 10, 300, 100));
        borderlist.Add(new IntRect(1050, 8, 100, 100));
        borderlist.Add(new IntRect(1150, 4, 100, 100));
        borderlist.Add(new IntRect(1250, 2, 200, 90));
        borderlist.Add(new IntRect(1450, 2, 200, 80));
        borderlist.Add(new IntRect(1650, 2, 200, 70));
        borderlist.Add(new IntRect(1850, 2, 200, 60));
        borderlist.Add(new IntRect(2050, 2, 200, 50));
        borderlist.Add(new IntRect(2250, 2, 200, 40));
        borderlist.Add(new IntRect(2450, 2, 200, 30));
        borderlist.Add(new IntRect(2650, 2, 200, 20));
        borderlist.Add(new IntRect(2800, 2, 100, 100));
        borderlist.Add(new IntRect(2850, 50, 100, 100));
        borderlist.Add(new IntRect(2900, 100, 100, 100));
        borderlist.Add(new IntRect(2920, 200, 100, 100));
        borderlist.Add(new IntRect(2920, 300, 100, 100));
        borderlist.Add(new IntRect(2900, 400, 100, 100));
        borderlist.Add(new IntRect(2850, 500, 100, 100));
        borderlist.Add(new IntRect(2800, 600, 100, 100));
        borderlist.Add(new IntRect(2750, 700, 100, 100));
        borderlist.Add(new IntRect(2700, 800, 100, 100));
        borderlist.Add(new IntRect(2600, 900, 100, 100));
        borderlist.Add(new IntRect(2700, 920, 100, 100));
        borderlist.Add(new IntRect(2800, 920, 100, 100));
        borderlist.Add(new IntRect(2900, 940, 100, 100));
        borderlist.Add(new IntRect(3000, 960, 100, 100));
        borderlist.Add(new IntRect(3100, 9800, 100, 100));
        borderlist.Add(new IntRect(3200, 1000, 100, 100));
        borderlist.Add(new IntRect(3300, 1010, 100, 100));
        borderlist.Add(new IntRect(3380, 1020, 100, 100));
        borderlist.Add(new IntRect(3480, 1060, 100, 100));
        borderlist.Add(new IntRect(3550, 1120, 100, 100));
        borderlist.Add(new IntRect(3600, 1220, 100, 500));
        borderlist.Add(new IntRect(3610, 1620, 100, 500));
        borderlist.Add(new IntRect(3500, 2100, 100, 100));
        borderlist.Add(new IntRect(3400, 2140, 100, 100));
        borderlist.Add(new IntRect(3300, 2170, 100, 100));
        borderlist.Add(new IntRect(3200, 2210, 100, 100));
        borderlist.Add(new IntRect(3100, 2240, 100, 100));
        borderlist.Add(new IntRect(3000, 2280, 100, 100));
        borderlist.Add(new IntRect(2900, 2320, 100, 100));
        borderlist.Add(new IntRect(2800, 2360, 100, 100));
        borderlist.Add(new IntRect(2700, 2400, 100, 100));
        borderlist.Add(new IntRect(2700, 2020, 100, 100));
        borderlist.Add(new IntRect(2900, 1970, 100, 100));
        borderlist.Add(new IntRect(2800, 2000, 100, 100));
        borderlist.Add(new IntRect(3000, 1940, 100, 100));
        borderlist.Add(new IntRect(3100, 1900, 100, 100));
        borderlist.Add(new IntRect(3200, 1860, 100, 100));
        borderlist.Add(new IntRect(3300, 1830, 100, 100));
        borderlist.Add(new IntRect(3340, 1310, 100, 600));
        borderlist.Add(new IntRect(3240, 1300, 100, 100));
        borderlist.Add(new IntRect(3140, 1280, 100, 100));
        borderlist.Add(new IntRect(3040, 1260, 100, 100));
        borderlist.Add(new IntRect(2940, 1240, 100, 100));
        borderlist.Add(new IntRect(2840, 1220, 100, 100));
        borderlist.Add(new IntRect(2740, 1200, 100, 100));
        borderlist.Add(new IntRect(2640, 1180, 100, 100));
        borderlist.Add(new IntRect(2540, 1200, 100, 100));
        borderlist.Add(new IntRect(2440, 1220, 100, 100));
        borderlist.Add(new IntRect(2340, 1200, 100, 100));
        borderlist.Add(new IntRect(2240, 1280, 100, 100));
        borderlist.Add(new IntRect(2190, 1340, 100, 100));
        borderlist.Add(new IntRect(2170, 1440, 100, 100));
        borderlist.Add(new IntRect(2120, 1540, 100, 100));
        borderlist.Add(new IntRect(2020, 1590, 100, 100));
        borderlist.Add(new IntRect(1920, 1630, 100, 100));
        borderlist.Add(new IntRect(1820, 1650, 100, 100));
        borderlist.Add(new IntRect(1720, 1670, 100, 100));
        borderlist.Add(new IntRect(1620, 1670, 100, 100));
        borderlist.Add(new IntRect(1500, 1600, 100, 100));
        borderlist.Add(new IntRect(1440, 1500, 100, 100));
        borderlist.Add(new IntRect(1400, 1410, 100, 100));
        borderlist.Add(new IntRect(1380, 1320, 100, 100));
        borderlist.Add(new IntRect(1360, 1220, 100, 100));
        borderlist.Add(new IntRect(1330, 1120, 100, 100));
        borderlist.Add(new IntRect(1300, 1020, 100, 100));
        borderlist.Add(new IntRect(1320, 920, 100, 100));
        borderlist.Add(new IntRect(1350, 820, 100, 100));
        borderlist.Add(new IntRect(1450, 770, 100, 100));
        borderlist.Add(new IntRect(1550, 740, 100, 100));
        borderlist.Add(new IntRect(1650, 710, 100, 100));
        borderlist.Add(new IntRect(1750, 680, 100, 100));
        borderlist.Add(new IntRect(1850, 650, 100, 100));
        borderlist.Add(new IntRect(1950, 610, 100, 100));
        borderlist.Add(new IntRect(2050, 590, 100, 100));
        borderlist.Add(new IntRect(2150, 570, 100, 100));
        borderlist.Add(new IntRect(2250, 550, 100, 100));
        borderlist.Add(new IntRect(2350, 530, 100, 100));
        borderlist.Add(new IntRect(2430, 510, 100, 100));
        borderlist.Add(new IntRect(2450, 460, 100, 100));
        borderlist.Add(new IntRect(2470, 410, 100, 100));
        borderlist.Add(new IntRect(2490, 360, 100, 100));
        borderlist.Add(new IntRect(2510, 310, 100, 100));
        borderlist.Add(new IntRect(2410, 310, 100, 200));
        borderlist.Add(new IntRect(2310, 310, 200, 300));
        borderlist.Add(new IntRect(2210, 310, 200, 300));
        borderlist.Add(new IntRect(2110, 310, 200, 300));
        borderlist.Add(new IntRect(2010, 315, 200, 330));
        borderlist.Add(new IntRect(1910, 321, 200, 360));
        borderlist.Add(new IntRect(1810, 326, 200, 390));
        borderlist.Add(new IntRect(1710, 329, 200, 400));
        borderlist.Add(new IntRect(1610, 338, 200, 440));
        borderlist.Add(new IntRect(1510, 346, 200, 450));
        borderlist.Add(new IntRect(1410, 353, 200, 480));
        borderlist.Add(new IntRect(1310, 359, 200, 490));
        borderlist.Add(new IntRect(1210, 363, 200, 1800));
        borderlist.Add(new IntRect(1140, 363, 200, 1750));
        borderlist.Add(new IntRect(1040, 369, 200, 990));
        borderlist.Add(new IntRect(940, 374, 200, 300));
        borderlist.Add(new IntRect(970, 374, 200, 370));
        borderlist.Add(new IntRect(1000, 374, 200, 550));
        borderlist.Add(new IntRect(1030, 374, 200, 750));
        borderlist.Add(new IntRect(1090, 369, 200, 1300));
        borderlist.Add(new IntRect(1120, 369, 200, 1500));
        borderlist.Add(new IntRect(2650, 2080, 100, 100));
        borderlist.Add(new IntRect(2500, 900, 100, 100));
        borderlist.Add(new IntRect(2450, 900, 80, 130));
        borderlist.Add(new IntRect(2350, 920, 100, 100));
        borderlist.Add(new IntRect(2250, 950, 100, 80));
        borderlist.Add(new IntRect(2150, 960, 100, 80));
        borderlist.Add(new IntRect(2150, 990, 100, 80));
        borderlist.Add(new IntRect(2100, 1040, 100, 80));
        borderlist.Add(new IntRect(2050, 980, 100, 180));
        borderlist.Add(new IntRect(1950, 1000, 100, 220));
        borderlist.Add(new IntRect(1850, 1020, 100, 360));
        borderlist.Add(new IntRect(1750, 1070, 100, 350));
        borderlist.Add(new IntRect(1700, 1100, 100, 220));
        borderlist.Add(new IntRect(1650, 1098, 100, 100));
        //start ziel
        startFinishlist.Add(new IntRect(1960, 2192, 10, 230));
        checkpointlist.Add(new IntRect(2250, 50, 10, 280));
        checkpointlist1.Add(new IntRect(1800, 1400, 10, 280));
    }

    public override void Update(float deltaTime)
    {
    }

    public override void Draw(RenderWindow window)
    {
        window.Draw(backgroundSprite);
    }
}

//                                      MultiMediaTechnology / FHS  |  MultiMediaProjekt 1  | Lauterbach Dominik