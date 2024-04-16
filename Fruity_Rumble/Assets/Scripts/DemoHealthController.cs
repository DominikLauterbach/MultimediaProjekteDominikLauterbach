using UnityEngine;
using Random = UnityEngine.Random;

//Be sure to include the namespace RengeGames.HealthBars at the top of your scripts when using the health bars.
using RengeGames.HealthBars;
using UnityEngine.SceneManagement;

namespace RengeGames.HealthBars.Demo
{

    public class DemoHealthController : MonoBehaviour
    {

        // The parent name and the health bar name are used to identify the health bar you want to modify.
        // they are only used by the StatusBarsManager class, so if you don't want to use that class, you can ignore these.
        // they can be changed for every health bar in the inspector or in code 
        // <healthBar>.ParentName = "NewParentName";
        // <healthBar>.Name = "NewHealthBarName";
        public string parentName = "Player";
        public string healthBarName = "Primary";


        // these are just some example properties that can be changed in the inspector.
        public bool updateFromScript = true;
        public float value;



        // This is an example of how to get a reference to a health bar from a script.
        // This is the component name for the health bar.
        // Be sure to include the namespace RengeGames.HealthBars at the top of your own script.
        public RadialSegmentedHealthBar exampleHealthBar;

        void Start()
        {
            value = 0.2f;
            // Here are some examples of changing health bar properties directly.
            // Each porperty has a tooltip that explains what it does.
            //exampleHealthBar.InnerColor.Value = new Color(1,1,1,1); // set the color of the value. Hover over the property to see more information on it
            //exampleHealthBar.RemoveSegments.Value = 0; // Set the value by removing segments.
            //exampleHealthBar.SetPercent(1); // Set the value by percent.
        }
        private bool stopPulseCalled = false;
        private void Update()
        {
            if (updateFromScript)
            {
                // The StatusBarsManager class offers an easy way to modify health bars from anywhere without needing to get a reference to them.
                StatusBarsManager.SetPercent(parentName, healthBarName, value);
                if (Input.GetKeyDown(KeyCode.Q))
                {
                    if (!stopPulseCalled)
                    {
                        StopPulse();
                        stopPulseCalled = true;
                    }
                    else
                    {
                        AddFruit();
                    }

                }
                //if (value == 1)
                //{
                //    SceneManager.LoadScene("WinScreen");
                //    Debug.Log("WinScreen");

                //}
            }

        }

        public void ToggleNoise(bool toggle)
        {
            StatusBarsManager.SetShaderPropertyValue(parentName, healthBarName, RadialHealthBarProperties.EmptyNoiseEnabled, toggle);
        }

        public void Instantiate()
        {
            // This is an example of how to instantiate a health bar from a script.
            // Of course there are many ways to do this.
            var parent = new GameObject("Daddy o' 100");
            parent.transform.position = new Vector3(0, 0, 0);
            for (int i = 0; i < 100; i++)
            {
                var go = new GameObject("HealthBar" + i, typeof(RadialSegmentedHealthBar));
                go.transform.parent = parent.transform;
                go.transform.position = new Vector3((Random.value * 2 - 1) * 6, (Random.value * 2 - 1) * 3, 0);
            }
        }

        public void AddFruit()
        {
            value += 0.2f;
            Debug.Log(value);
        }

        public void StopPulse()
        {
            StatusBarsManager.SetShaderPropertyValue(parentName, healthBarName, RadialHealthBarProperties.PulsateWhenLow, false);
        }

    }
}