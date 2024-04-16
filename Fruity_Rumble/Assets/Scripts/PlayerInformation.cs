using System.Collections;
using System.Collections.Generic;
using StarterAssets;
using UnityEngine;

public class PlayerInformation : MonoBehaviour
{
    public int playerId;
    public int controllerId;
    public bool isRespawning = false;
    //public Vector2 respawnPos;

    public void Start()
    {
        transform.position = new Vector3(0.8f - playerId * 0.5f, 1, 1.1f);
    }

    public void Update()
    {
        if (isRespawning)
        {
            Respawn();
        }
    }

    public void Respawn()
    {
        transform.position = new Vector3(0.8f - playerId * 0.5f, 1, 1.1f);
        //transform.position = new Vector3(respawnPos.x, 1, respawnPos.y);
        isRespawning = false;
        transform.GetComponent<ThirdPersonController>().enabled = true;
    }
}
