using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

//Be sure to include the namespace RengeGames.HealthBars at the top of your scripts when using the health bars.
using RengeGames.HealthBars;
using UnityEngine.SceneManagement;

namespace RengeGames.HealthBars.Demo
{
    public class ProgressBar : MonoBehaviour
    {
        // Start is called before the first frame update
        public bool updateFromScript = true;
        public float value;

        public RadialSegmentedHealthBar progressBar;

        void Start()
        {

            value = 0.2f;
        }

        // Update is called once per frame
        void Update()
        {
        }
        public void StopPulsation()
        {
            // Setzen Sie die Pulsations-Eigenschaft auf "false"
            progressBar.PulsateWhenLow.Value = false;
            // Aktualisieren Sie die Leiste, um die Änderungen anzuwenden
            //Debug.Log("Pulsation stopped!");
        }

        public void AddSegment()
        {
            progressBar.AddRemoveSegments(-1);
            //Debug.Log("aaaaaaaaaaaaa");
            
            if (progressBar.RemoveSegments.Value == 0)
            {
                //Debug.Log("bbbbbbbbbbbb");
                SceneManager.LoadScene("Winscreen");
            }
        }
    }

}