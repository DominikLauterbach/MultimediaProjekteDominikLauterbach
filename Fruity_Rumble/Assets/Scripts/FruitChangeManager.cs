using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Random = UnityEngine.Random;

//Be sure to include the namespace RengeGames.HealthBars at the top of your scripts when using the health bars.
using RengeGames.HealthBars;
using UnityEngine.SceneManagement;

namespace RengeGames.HealthBars.Demo
{
    public class FruitChange : MonoBehaviour
    {
        public Sprite apple;
        public Sprite orange;
        public Sprite banana;
        public Sprite lemon;

        public Image defaultSprite;
        public Sprite finishImage;

        public List<int> availableIndices = new List<int> { 0, 1, 2, 3 };
        public int fruitsDisplayed = 0;

        // Dictionary to map sprites to texts
        public Dictionary<string, Sprite> spriteTextDictionary = new Dictionary<string, Sprite>();

        void Start()
        {
            SpriteTextDictionary();
            RandomFruitIndex();
        }

        void Update()
        {
            //if (Input.GetKeyDown(KeyCode.Q))
            //{
            //    RandomFruitIndex();
            //}
        }

        public void SpriteTextDictionary()
        {
            spriteTextDictionary.Add("Apple(Clone)", apple);
            spriteTextDictionary.Add("Orange(Clone)", orange);
            spriteTextDictionary.Add("Banana(Clone)", banana);
            spriteTextDictionary.Add("Lemon(Clone)", lemon);
        }

        public void RandomFruitIndex()
        {
            if (availableIndices.Count == 0)
            {
                // If all fruits have been displayed, use finishImage
                defaultSprite.sprite = finishImage;
                return;
            }
            int index = availableIndices[Random.Range(0, availableIndices.Count)];
            availableIndices.Remove(index);
            ChangeFruit(index);
            fruitsDisplayed++;
        }

        public void ChangeFruit(int fruitIndex)
        {
            Sprite selectedSprite = GetSpriteByIndex(fruitIndex);
            defaultSprite.sprite = selectedSprite;

            //// Retrieve the text corresponding to the selected sprite
            //string textForSprite = spriteTextDictionary[selectedSprite];
            //Debug.Log("Text for selected fruit: " + textForSprite);
        }

        // Method to get the sprite based on the index
        public Sprite GetSpriteByIndex(int index)
        {
            switch (index)
            {
                case 0:
                    return apple;
                case 1:
                    return banana;
                case 2:
                    return lemon;
                case 3:
                    return orange;
                default:
                    return null;
            }
        }
    }
}
