using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Menu : MonoBehaviour
{
    public void OnplayButton ()
    {
        SceneManager.LoadScene("MainGame");
    }

    public void OnQuitButton ()
    {
        Application.Quit();
    }
}
