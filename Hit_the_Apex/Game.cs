using SFML.Graphics;
using SFML.System;
using System.IO;
using SFML.Window;
using SFML.Audio;
using System.Threading;
using System.Collections.Generic;
namespace GGD_Template;

public class Game : GameObject
{
    private const string TITLE = "MMP1_Lauterbach_Dominik";
    private readonly float animationSpeed = 8;
    private double fastestLap = 10000;
    private double thisLap;
    public float penaltyOffTrack = 20f;
    public int maxSpeedOffTrack = 200;
    public float startingPositionX = 1967f;
    public float startingPositionY = 2392f;
     public float textPositionX = 200f;
    public float textPositionY = -450f;
    // public string startText = "Bereithalten";
    
    private List<GameObject> gameObjects = new();
    // private readonly VideoMode mode = new(WIDTH, HEIGHT);

    private Player player;
    public GameManager gameManager;
    private background backgroundSprite;
    private RenderWindow window;

    private float animationTimeIndex;

    public Game(RenderWindow window, GameManager gameManager)
    {
        this.gameManager = gameManager;

        window.KeyPressed += CloseGame;

        window.Closed += OnWindowClose;

        DebugDraw.ActiveWindow = window;

        this.window = window;
    }

    public void offtrack()
    {
        foreach (IntRect rect in backgroundSprite.borderlist.ToList())
        {
            if (player.CollisionRect.Intersects(rect))
            {
                if (player.carSpeed > maxSpeedOffTrack)
                {
                    player.carSpeed -= penaltyOffTrack;
                }
                break;
            }
        }
    }

    public void startTimer()
    {

        foreach (IntRect rect in backgroundSprite.startFinishlist.ToList())
        {
            if (player.CollisionRect.Intersects(rect))
            {
                if (player.checkpointPassed1 == true && player.checkpointPassed2 == true)
                {
                    if (player.timer < fastestLap)
                    {
                        fastestLap = player.timer;
                    }
                    thisLap = player.timer;

                    string text = File.ReadAllText("./Formula 1 car and trackset/Score.txt");
                    if (text.Length == 0)
                    {
                        StreamWriter sw = new StreamWriter("./Formula 1 car and trackset/Score.txt");
                        sw.WriteLine(fastestLap);
                        sw.Close();
                    }
                    else if (int.Parse(text) > fastestLap)
                    {
                        StreamWriter sw = new StreamWriter("./Formula 1 car and trackset/Score.txt");
                        sw.WriteLine(fastestLap);
                        sw.Close();
                    }

                    player.timer = 0;
                    player.checkpointPassed1 = false;
                    player.checkpointPassed2 = false;

                    System.Console.WriteLine("gewertete Runde");

                }
                else if (player.checkpointPassed1 == true || player.checkpointPassed2 == true)
                {
                    player.timer = 0;
                    player.checkpointPassed1 = false;
                    player.checkpointPassed2 = false;
                    System.Console.WriteLine("abgekürzt");
                }
                break;
            }
        }
    }

    public void Checkpoint()
    {
        foreach (IntRect rect in backgroundSprite.checkpointlist.ToList())
        {
            if (player.CollisionRect.Intersects(rect))
            {
                player.checkpointPassed1 = true;
                break;
            }
        }

        foreach (IntRect rect in backgroundSprite.checkpointlist1.ToList())
        {
            if (player.CollisionRect.Intersects(rect))
            {
                player.checkpointPassed2 = true;
                break;
            }
        }
    }



    private void OnWindowResized(object? sender, SizeEventArgs e)
    {
        window.SetView(new View(window.GetView().Center, (Vector2f)window.Size));
    }

    private void OnWindowClose(object? sender, EventArgs e)
    {
        window.Close();
    }

    public void Run()
    {
        Initialize();



        Clock clock = new Clock();

        while (window.IsOpen)
        {
            float deltaTime = clock.Restart().AsSeconds();

            HandleEvents();

            Update(deltaTime);

            Draw(window);
        }
    }

    public override void Initialize()
    {
        //background einfügen
        backgroundSprite = new background();
        backgroundSprite.Initialize();
        gameObjects.Add(backgroundSprite);

        //Player einfügen
        player = new Player(startingPositionX, startingPositionY, gameManager);
        player.Initialize();
        gameObjects.Add(player);


    }
    public static Color ColorFromRGB(int R, int G, int B)
    {
        return new Color((byte)R, (byte)G, (byte)B);
    }

    public override void Update(float deltaTime)
    {
        startTimer();
        Checkpoint();
        offtrack();
        foreach (GameObject gameObject in gameObjects)
        {
            gameObject.Update(deltaTime);
        }

        animationTimeIndex += deltaTime * animationSpeed;

        View view = window.GetView();
        view.Center = player.sprite.Position;
        view.Size = new Vector2f(window.Size.X * 1.5f, window.Size.Y * 1.5f);
        window.SetView(view);
    }

    private void HandleEvents()
    {
        window.DispatchEvents();
    }

    private String getTime(double time)
    {
        String sRet = "--:--.-";
        int minutes = (int)time / 600;
        int seconds = ((int)time % 600) / 10;
        int tenthsOfASecond = (int)time % 10;
        sRet = minutes.ToString("D2") + ":" + seconds.ToString("D2") + "." + tenthsOfASecond;
        return sRet;
    }

    public override void Draw(RenderWindow window)
    {
        Color BackgColor = ColorFromRGB(1, 148, 0);
        window.Clear(BackgColor);

        foreach (GameObject gameObject in gameObjects)
        {
            gameObject.Draw(window);
        }

        Font font = new Font("./Formula 1 car and trackset/Fonts/FreeMonoBold.otf");
        Text text = new Text(gameManager.startText, font, 60);
        text.Position = new Vector2f(1967f, 2395f);
        Text text1 = new Text(getTime(player.timer), font, 60);
        text1.Position = player.sprite.Position + new Vector2f(textPositionX, textPositionY);
       

    Text text2 = new Text("Runde:    " + "--:--.-", font, 35);
        if (thisLap > 0)
        {
            text2 = new Text("Runde:    " + getTime(thisLap), font, 35);
        }
        text2.Position = player.sprite.Position + new Vector2f(-600f, -400f);

        string highscore = File.ReadAllText("./Formula 1 car and trackset/Score.txt");
        Text fastestLapText = new Text("Bestzeit: " + "--:--.-", font, 35);
        if (highscore.Length != 0)
        {
            fastestLapText = new Text("Bestzeit: " + getTime(Double.Parse(highscore)), font, 35);
            fastestLap = Double.Parse(highscore);
        }

        if (fastestLap < 10000)
        {
            fastestLapText = new Text("Bestzeit: " + getTime(fastestLap), font, 35);
        }
        fastestLapText.Position = player.sprite.Position + new Vector2f(-600f, -450f);

        if (gameManager.delayStarted == false)
        {
            gameManager.DelayStart();
            text2 = new Text("START IN:    " + gameManager.countdown, font, 60);
            text2.Position = player.sprite.Position + new Vector2f(-600f, -400f);
        }

        // draw the text
        window.Draw(text);
        window.Draw(text1);
        window.Draw(text2);
        window.Draw(fastestLapText);
        window.Display();

    }

    private void CloseGame(object sender, KeyEventArgs e)
    {
        if (e.Code == Keyboard.Key.Escape)
            window?.Close();

    }
}

//                                      MultiMediaTechnology / FHS  |  MultiMediaProjekt 1  | Lauterbach Dominik