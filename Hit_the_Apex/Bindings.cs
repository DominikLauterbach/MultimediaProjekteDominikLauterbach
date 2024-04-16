using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
using System.IO;
using System.Threading;
using System.Collections.Generic;
namespace GGD_Template;

public class Bindings : GameObject
{
    private RenderWindow window;
    private bool gameRequested;
    public bool GameRequested => gameRequested;
    public Sprite bindingsSprite;

    private Boolean blive = false;
    public Bindings(RenderWindow window)
    {
        this.window = window;
    }

    public override void Initialize()
    {
        Texture menuTexture = new Texture("./Formula 1 car and trackset/Assets/bindings.png");

        bindingsSprite = new Sprite(menuTexture);

        bindingsSprite.Position = new Vector2f(-15, 0);

        View view = window.GetView();
        window.SetView(view);
    }

    public override void Update(float deltaTime)
    {
        if (InputManager.Instance.GetKeyPressed(Keyboard.Key.Num1))
        {
            gameRequested = true;
        }
    }
    public static Color ColorFromRGB(int R, int G, int B)
    {
        return new Color((byte)R, (byte)G, (byte)B);
    }
    public override void Draw(RenderWindow window)
    {
            window.Clear();
            // Das Fenster löschen
            Color BackgColor = ColorFromRGB(226, 13, 13);
            window.Clear(BackgColor);

            // Die Textur zeichnen
            window.Draw(bindingsSprite);
            blive = true;
    }
};

//                                      MultiMediaTechnology / FHS  |  MultiMediaProjekt 1  | Lauterbach Dominik