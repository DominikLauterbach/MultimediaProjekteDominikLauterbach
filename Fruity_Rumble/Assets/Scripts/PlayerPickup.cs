using RengeGames.HealthBars.Demo;
using System.Collections;
using System.Collections.Generic;
using StarterAssets;
using UnityEngine;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.LowLevel;
using UnityEngine.InputSystem.Utilities;
using UnityEngine.XR;

public class PlayerPickup : MonoBehaviour
{
    // Start is called before the first frame update
    [SerializeField] private GameObject player;
    private GameObject heldItem;
    [SerializeField] private GameObject basePlayer;
    [SerializeField] private GameObject currentApperance;
    private GameObject lastHit;
    [SerializeField] private GameObject pickupCone;
    [SerializeField] private InputActionAsset playerInput;
    public bool isTryingToPickUp = false;
    void Start()
    {
        
    }

    void Update()
    {
        //Debug.Log("test");
    }

    void OnPickup()
    {
        Debug.Log("OnPickup called");

        isTryingToPickUp = true;
        transform.Find("PickupCone").gameObject.GetComponent<PlayerPickup>().isTryingToPickUp = true;
        

    }

    private void OnTriggerEnter(Collider other)
    {
        if ((other.gameObject.CompareTag("Pickup")) && lastHit == null)
        {
            //Debug.Log("Hit " + other.gameObject.name);
            lastHit = other.gameObject;
            lastHit.transform.Find("hover_effect").gameObject.SetActive(true);
        }
    }

    private void OnTriggerStay(Collider other)
    {
        //Debug.Log(isTryingToPickUp);
        //Debug.Log(lastHit.name);
        //Debug.Log(other.gameObject.name);
        //Debug.Log(other.tag);
        //Debug.Log(isTryingToPickUp);
        //Debug.Log(tag);
        if ((Input.GetKeyDown(KeyCode.E) || isTryingToPickUp) && other.tag == "Pickup" && other.gameObject == lastHit)
        {
            TryPickUp(other);
            isTryingToPickUp = false;
            GameObject pickupCone = transform.Find("PickupCone").gameObject;
            if (pickupCone != null)
            {
                pickupCone.GetComponent<PlayerPickup>().isTryingToPickUp = false;
            }
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.CompareTag("Pickup") && other.gameObject == lastHit)
        {
            other.transform.Find("hover_effect").gameObject.SetActive(false);
            lastHit = null;
        }
    }

    public void TrySettingPickUpTrue()
    {
        Debug.Log("Setting pickup to true");
        isTryingToPickUp = true;
    }


    void TryPickUp(Collider hit)
    {
        Debug.Log("Picked up " + hit.gameObject.name);
        heldItem = hit.gameObject;
        if (heldItem == null)
            return;
        heldItem.transform.tag = "ControlledFood";
        // insert eating sounds here

        //PlayerInput playerInput = GetComponent<PlayerInput>();
        //playerInput.SwitchCurrentActionMap("Sphere");

        // hide player
        //player.transform.Find("Capsule").GetComponent<MeshRenderer>().enabled = false;
        //player.transform.Find("Geometry").GetComponent<MeshRenderer>().enabled = false;
        player.transform.Find("Geometry").transform.gameObject.SetActive(false);
        //player.SetActive(false);

        //player.isStatic = true;
        player.GetComponent<ThirdPersonController>().enabled = false;
        //Destroy(player);
        //player.SetActive(false);

        heldItem.GetComponent<SphereController>().playerId = GetComponentInParent<PlayerInformation>().playerId;
        heldItem.GetComponent<SphereController>().controllerId = GetComponentInParent<PlayerInformation>().controllerId;

        heldItem.AddComponent<PlayerInput>();
        heldItem.GetComponent<PlayerInput>().actions = playerInput;
        heldItem.GetComponent<PlayerInput>().SwitchCurrentActionMap("Sphere");
        heldItem.GetComponent<SphereController>().isActive = true;
        //isTryingToPickUp = false;

    }
}
