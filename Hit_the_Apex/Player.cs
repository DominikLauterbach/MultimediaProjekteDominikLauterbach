using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;

namespace GGD_Template;


public class Player : GameObject
{

    private const int PLAYER_TILING_X = 4; //6 frames horizontal
    private const int PLAYER_TILING_Y = 1; //1 frame vertical

    public double carSpeed = 0;
    public float startingCarDirection = -90f;
    public IntRect CollisionRect { get; private set; }
    private Vector2f vPlayerDirection = new Vector2f(0f, 1f);
    public Sprite sprite;
    public GameManager gameManager;
    private float  positionX = 0f, positionY = 0f;

    private float animationTime = 0;
    private float animationSpeed = 1;

    private float lastRotation = -1;

    private float carRotation = 0f;
    private long carslower = 0;
    private Boolean resetCondition = false;
    public double carslowerIntervall = 0.2;
    public Game game;
    public Boolean checkpointPassed1 = false;
    public Boolean checkpointPassed2 = false;
    public double timer = 0;
    private long tmptimer;

    public Player(float X, float Y, GameManager gameManager)
    {
        this.gameManager = gameManager;
        positionX = X;
        positionY = Y;
    }
    public override void Initialize()
    {
        Texture playerTexture = new Texture("./Formula 1 car and trackset/Assets/F1_car_set.png");
        sprite = new Sprite(playerTexture);
        sprite.TextureRect = new IntRect
        (
            0, 0,
            (int)(playerTexture.Size.X / PLAYER_TILING_X),
            (int)(playerTexture.Size.Y / PLAYER_TILING_Y)
        );
        sprite.Scale *= 1;
        sprite.Scale = new Vector2f(0.4f, 0.5f);
        sprite.Position += new Vector2f(positionX, positionY);
        sprite.Rotation += -90f;

        CollisionRect = new IntRect
        (
            (int)sprite.Position.X, (int)sprite.Position.Y,
            (int)sprite.GetGlobalBounds().Width,
            (int)sprite.GetGlobalBounds().Height
        );
    }
    public override void Update(float deltaTime)
    {
        animationTime += deltaTime * animationSpeed;

        long timenow = DateTimeOffset.UtcNow.ToUnixTimeMilliseconds();
        if ((tmptimer + 100) < timenow && gameManager.delayStarted)   //1000 = sek 100 = 10tel 10 = 100tel
        {
            timer++;
            tmptimer = timenow;
        }


        if (gameManager.countdown == 0)
        {
            if (InputManager.Instance.GetKeyPressed(Keyboard.Key.W))
            {
                //drive
                if (carSpeed <= 0)
                {
                    carSpeed += 5;
                }
                else if (carSpeed < 700)
                {
                    carSpeed = carSpeed + 10;
                }
                if (resetCondition == false)
                {
                    resetCondition = true;
                }

            }
            if (InputManager.Instance.GetKeyPressed(Keyboard.Key.A))
            {
                sprite.Rotation += -2f;

            }

            if (InputManager.Instance.GetKeyPressed(Keyboard.Key.S))
            {
                switch (carSpeed)
                {
                    case var speed when speed > 100:
                        carSpeed = speed - 10;
                        break;

                    case var speed when speed > 0:
                        carSpeed = (int)(speed * 0.9f);
                        break;

                    case var speed when speed < 80:
                        carSpeed = 0;
                        break;

                    case var speed when speed == 0:
                        carSpeed -= 20;
                        break;
                }
            }
            if (InputManager.Instance.GetKeyPressed(Keyboard.Key.Space))
            {
                switch (carSpeed)
                {
                    case var speed when speed > 100:
                        carSpeed = speed - 10;
                        break;

                    case var speed when speed > 0:
                        carSpeed = (int)(speed * 0.9f);
                        break;

                    case var speed when speed < 80:
                        carSpeed = 0;
                        break;

                    case var speed when speed == 0:
                        carSpeed -= 20;
                        break;
                }
            }
            if (InputManager.Instance.GetKeyPressed(Keyboard.Key.D))
            {
                sprite.Rotation += 2f;
            }
            if (InputManager.Instance.GetKeyPressed(Keyboard.Key.R))
            {

                if(resetCondition)
                {
                    sprite.Position = new Vector2f(1967f, 2392f);
                    sprite.Rotation = startingCarDirection;
                    carSpeed = 0;
                    resetCondition = false;
                    timer = 0;
                    checkpointPassed1 = false;
                    checkpointPassed2 = false;
                }
            }
            else  //auslauf
            {
                long currentTimeInSeconds = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
                if ((carslower + carslowerIntervall) < currentTimeInSeconds)
                {
                    if (carSpeed > 0)
                    {
                        carSpeed -= 80;
                    }
                    carslower = currentTimeInSeconds;
                }

            }
        }

        if (sprite.Rotation != lastRotation)
        {
            carRotation = sprite.Rotation - 90;
            float angleInRadians = (float)(carRotation * Math.PI / 180f);
            vPlayerDirection = new Vector2f((float)Math.Cos(angleInRadians), (float)Math.Sin(angleInRadians));
            lastRotation = sprite.Rotation;
        }

        sprite.Position += vPlayerDirection * (float)carSpeed * deltaTime;

        float x_tmp = 0, y_tmp = 0;

        if(vPlayerDirection.X > 0 && vPlayerDirection.Y > 0){
            x_tmp = sprite.Position.X - sprite.GetGlobalBounds().Width/1.25f;
            y_tmp = sprite.Position.Y   - (sprite.GetGlobalBounds().Height * vPlayerDirection.Y)/1.25f;
        } else if (vPlayerDirection.X < 0 && vPlayerDirection.Y < 0){
            x_tmp = sprite.Position.X + sprite.GetGlobalBounds().Width/3.25f;
            y_tmp = sprite.Position.Y - sprite.GetGlobalBounds().Height/1.25f - (sprite.GetGlobalBounds().Height * vPlayerDirection.Y);
        } else if (vPlayerDirection.X > 0 && vPlayerDirection.Y < 0)
        {
            x_tmp = sprite.Position.X - (sprite.GetGlobalBounds().Width * vPlayerDirection.X)/1.25f;;
            y_tmp = sprite.Position.Y + sprite.GetGlobalBounds().Height/3.25f;
        }
        else if (vPlayerDirection.X < 0 && vPlayerDirection.Y > 0)
        {
            x_tmp = sprite.Position.X - sprite.GetGlobalBounds().Width /1.25f - (sprite.GetGlobalBounds().Width * vPlayerDirection.X);
            y_tmp = sprite.Position.Y - sprite.GetGlobalBounds().Height/1.25f ;
        }
        CollisionRect = new IntRect
        (
            (int)x_tmp, (int)y_tmp,
            (int)sprite.GetGlobalBounds().Width /2,
            (int)sprite.GetGlobalBounds().Height /2

        );
    }

    public override void Draw(RenderWindow window)
    {
        window.Draw(sprite);
    }
}

//                                      MultiMediaTechnology / FHS  |  MultiMediaProjekt 1  | Lauterbach Dominik