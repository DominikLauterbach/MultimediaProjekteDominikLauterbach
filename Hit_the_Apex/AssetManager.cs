using SFML.Graphics;
using SFML.System;
using SFML.Window;
using SFML.Audio;
using System.Collections.Generic;
namespace GGD_Template;

public class AssetManager
{
    private static AssetManager? instance;
    public Game game;

    public static AssetManager Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new AssetManager();
            }
            return instance;
        }
    }
    public readonly Dictionary<string, Texture> Textures = new Dictionary<string, Texture>();
    public static readonly Dictionary<string, Music> Music = new();
    public static readonly Dictionary<string, Sound> Sounds = new();
    public readonly Dictionary<string, Font> Font = new Dictionary<string, Font>();

    private AssetManager() { }
    //________________________________________________________________________________________________________________
    public void LoadTexture(string name, string fileName)
    {
        // Create a new texture object
        Texture texture = new Texture(fileName);

        // Add the texture to the dictionary using the specified name
        Textures[name] = texture;

    }
    //________________________________________________________________________________________________________________
    public static void LoadSound(string name, string fileName)
    {
        if (Sounds.ContainsKey(name))
            return;

        var sound = new SoundBuffer(fileName);
        Sounds.Add(name, new Sound(sound));
    }
    //________________________________________________________________________________________________________________
    public static void LoadMusic(string name, string fileName)
    {
        if (Music.ContainsKey(name))
            return;

        var music = new Music(fileName);
        Music.Add(name, music);
    }
    public static void LoadMusic1(string name, string fileName)
    {
        if (Music.ContainsKey(name))
            return;

        var music = new Music(fileName);
        Music.Add(name, music);
    }
    //________________________________________________________________________________________________________________
    public void LoadFont(string name, string fileName)
    {
        // Create a new texture object
        Font font = new Font(fileName);

        // Add the texture to the dictionary using the specified name
        Font[name] = font;
    }
    //________________________________________________________________________________________________________________
}

//                                      MultiMediaTechnology / FHS  |  MultiMediaProjekt 1  | Lauterbach Dominik