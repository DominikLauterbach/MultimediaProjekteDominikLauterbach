using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
using System.IO;
using System.Threading;
using System.Collections.Generic;
namespace GGD_Template;
public class Menu : GameObject
{
    private RenderWindow window;
    private bool bindingsRequested;
    public bool BindingsRequested => bindingsRequested;
    public Sprite menuSprite;
    private Boolean blive = false;
    Color BackgColor = ColorFromRGB(226, 13, 13);
    public Menu(RenderWindow window)
    {
        this.window = window;
    }
    public override void Initialize()
    {
        Texture menuTexture = new Texture("./Formula 1 car and trackset/Assets/menu.png");

        menuSprite = new Sprite(menuTexture);

        menuSprite.Position = new Vector2f(-15, 0);

        View view = window.GetView();
        window.SetView(view);
    }
    public override void Update(float deltaTime)
    {
        if (InputManager.Instance.GetKeyPressed(Keyboard.Key.Space))
        {
            bindingsRequested = true;
        }
    }

    public static Color ColorFromRGB(int R, int G, int B)
    {
        return new Color((byte)R, (byte)G, (byte)B);
    }
    public override void Draw(RenderWindow window)
    {
            window.Clear(BackgColor);

            // Die Textur zeichnen
            window.Draw(menuSprite);
            blive = true;

    }
}

//                                      MultiMediaTechnology / FHS  |  MultiMediaProjekt 1  | Lauterbach Dominik