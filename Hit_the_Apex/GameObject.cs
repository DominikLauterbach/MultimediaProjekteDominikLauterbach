using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;

namespace GGD_Template;

public abstract class GameObject : Transformable
{
    public abstract void Initialize();

    public abstract void Update(float deltaTime);

    public abstract void Draw(RenderWindow window);
}

//                                      MultiMediaTechnology / FHS  |  MultiMediaProjekt 1  | Lauterbach Dominik