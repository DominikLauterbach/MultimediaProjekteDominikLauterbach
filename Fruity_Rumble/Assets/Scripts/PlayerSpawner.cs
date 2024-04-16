using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;

public class PlayerSpawner : MonoBehaviour
{
    private int playerCount = 4;
    [SerializeField] private GameObject playerPrefab;
    // Start is called before the first frame update
    void Start()
    {
        if (Gamepad.all.Count > 0)
        {
            playerCount = Gamepad.all.Count;
        }
        for (int i = 0; i < playerCount; i++)
        {
            var playerForBuild = PlayerInput.Instantiate(playerPrefab, i, "Gamepad", -1, InputSystem.devices[i]);
            playerForBuild.transform.position = new Vector3(0.8f - i * 0.5f, 1, 1.1f);
            GameObject player = Instantiate(playerPrefab) as GameObject;
            player.name = "Player" + i;
            player.transform.position = new Vector3(0.8f - i * 0.5f, 1, 1.1f);
            player.GetComponent<PlayerInformation>().playerId = i;
            player.GetComponent<PlayerInformation>().controllerId = InputSystem.devices[i].deviceId;
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
