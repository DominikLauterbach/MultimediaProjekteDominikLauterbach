using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
using System.IO;
using System.Threading;
using System.Collections.Generic;
namespace GGD_Template;

public class GameManager : GameObject
{
    public enum Scene
    {
        Menu,
        Game,
        Bindings
    }
    private Scene currentScene;
    private Menu menuScene;
    private Game gameScene;
    private Bindings bindingsScene;
    private RenderWindow window;

    private Boolean bGameLoaded = false;
    private long tmpcountdown;
    public int countdown = 4;
    public string startText = "Bereithalten";
    public Boolean delayStarted = false;
    public GameManager()
    {
        //window info
        VideoMode videoMode = new VideoMode(800, 600);
        string title = "Hit The Apex";
        window = new RenderWindow(videoMode, title);

        //close & resize
        window.Closed += OnWindowClose;
        window.Resized += OnWindowResized;
        window.SetFramerateLimit(60);
        window.SetVerticalSyncEnabled(true);

        //Scenes
        currentScene = Scene.Menu;
        menuScene = new Menu(window);
        //gameScene = new Game(window);
        bindingsScene = new Bindings(window);
    }

    //close & resize
    private void OnWindowResized(object? sender, SizeEventArgs e)
    {
        window.SetView(new View(window.GetView().Center, (Vector2f)window.Size));
    }
    private void OnWindowClose(object? sender, EventArgs e)
    {
        window.Close();
    }

    //___________________________________________________________________________________________________Run
    public void Run()
    {
        Initialize();
        Clock clock = new Clock();

        while (window.IsOpen && !bGameLoaded)
        {
            float deltaTime = clock.Restart().AsSeconds();
            HandleEvents();
            Update(deltaTime);
            Draw(window);
        }
    }
    //___________________________________________________________________________________________________Initialize
    public override void Initialize()
    {
        //first Initialize
        menuScene.Initialize();
        //gameScene.Initialize();
        bindingsScene.Initialize();

        AssetManager.LoadMusic("MusicTrack", "./Formula 1 car and trackset/menusound.wav");
        AssetManager.Music["MusicTrack"].Volume = 40;
        AssetManager.Music["MusicTrack"].Play();

        InputManager.Instance.Initialize(window);

        //view
        View view = new View(new Vector2f(window.Size.X / 2, window.Size.Y / 2), (Vector2f)window.Size);
        window.SetView(view);
    }
    //___________________________________________________________________________________________________Update
    public override void Update(float deltaTime)
    {
        //change Scene
        switch (currentScene)
        {
            case Scene.Menu:
                menuScene.Update(deltaTime);
                if (menuScene.BindingsRequested)
                {
                    currentScene = Scene.Bindings;
                }
                break;
            case Scene.Bindings:
                bindingsScene.Update(deltaTime);
                if (bindingsScene.GameRequested)
                {
                    AssetManager.Music["MusicTrack"].Stop();
                    currentScene = Scene.Game;
                    new Game(window, this).Run();
                    bGameLoaded = true;
                }
                break;
            default:
                break;
        } 
    }
    public void DelayStart()
    {
        if (countdown != 0)
        {
            long timenow = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
            if ((tmpcountdown + 1) < timenow)
            {
               countdown--;
               tmpcountdown = timenow;
            }
        }
        if(countdown == 0 && startText != "Los!")
        {
            startText = "Los!";
            delayStarted = true;
        }
    }
    //___________________________________________________________________________________________________Draw
    public override void Draw(RenderWindow window)
    {
        switch (currentScene)
        {
            case Scene.Menu:
                menuScene.Draw(window);
                break;
            case Scene.Bindings:
                bindingsScene.Draw(window);
                break;
            default:
                menuScene.Draw(window);
                break;
        }
        window.Display();
    }
    //___________________________________________________________________________________________________HandleEvents
    private void HandleEvents()
    {
        window.DispatchEvents();
    }
}

//                                      MultiMediaTechnology / FHS  |  MultiMediaProjekt 1  | Lauterbach Dominik