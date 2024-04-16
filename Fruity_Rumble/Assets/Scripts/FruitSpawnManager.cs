using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static Cinemachine.CinemachineFreeLook;

public class FruitSpawnManager : MonoBehaviour
{
    [SerializeField] private List<GameObject> fruitPrefabs;
    [SerializeField] private GameObject fruitSpawner;

    private readonly Dictionary<GameObject, float> fruitSpawnTimes = new();

    // Start is called before the first frame update
    void Start()
    {
        StartCoroutine(SpawnFruits());
        StartCoroutine(DespawnFruits());
    }

    IEnumerator SpawnFruits()
    {
        while (true)
        {
            yield return new WaitForSeconds(3f);
            SpawnFruit();
        }
    }

    IEnumerator DespawnFruits()
    {
        while (true)
        {
            yield return new WaitForSeconds(1f);

            List<GameObject> fruitsToDespawn = new List<GameObject>();
            foreach (var fruit in fruitSpawnTimes.Keys)
            {
                if (fruit != null && !fruit.CompareTag("ControlledFood") && Time.time - fruitSpawnTimes[fruit] > 10f)
                {
                    fruitsToDespawn.Add(fruit);
                }
            }

            foreach (var fruit in fruitsToDespawn)
            {
                DespawnFruit(fruit);
            }
        }
    }


    void SpawnFruit()
    {
        int randomIndex = Random.Range(0, fruitPrefabs.Count);
        int randomSpawnPointIndex = Random.Range(0, fruitSpawner.transform.childCount);
        GameObject fruit = Instantiate(fruitPrefabs[randomIndex], fruitSpawner.transform.GetChild(randomSpawnPointIndex).position, Quaternion.identity);
        fruitSpawnTimes[fruit] = Time.time;
    }

    void DespawnFruit(GameObject fruit)
    {
        fruitSpawnTimes.Remove(fruit);
        Destroy(fruit);
    }
}