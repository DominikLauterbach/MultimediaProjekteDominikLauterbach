using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using RengeGames.HealthBars.Demo;
using RengeGames.HealthBars;
using UnityEngine.SceneManagement;
using UnityEngine.InputSystem;

public class SphereController : MonoBehaviour
{
    [SerializeField] public FruitChange fruitChange;
    [SerializeField] public ProgressBar progressBar;

    [SerializeField] private GameObject fruit;
    [SerializeField] private float speed;
    private Rigidbody rb;
    public bool isActive = false;
    public bool onGround = true;

    public bool canJump = true;

    public int playerId;
    public int controllerId;

    [SerializeField] private GameObject humanPlayer;
    
    private GameObject blender;


    // Start is called before the first frame update
    void Start()
    {
        fruitChange = GameObject.Find("Player" + playerId + "HUD").transform.Find("Fruit").GetComponent<FruitChange>();
        progressBar = GameObject.Find("Player" + playerId + "HUD").transform.Find("ProgressBar").GetComponent<ProgressBar>();
        rb = GetComponent<Rigidbody>();
        blender = GameObject.Find("Mixer");
    }

    // Update is called once per frame
    void Update()
    {
        if (isActive)
        {
            Move();
            if (Input.GetKeyDown(KeyCode.Space))
            {
                Jump();
            }

            if (Input.GetKeyDown(KeyCode.Q))
            {
                Invoke("RespawnAsPlayer", 1);
            }
            

        }
    }

    public void OnBlender()
    {
        
    }

    public void OnJump()
    {
        if (canJump)
        {
            Debug.Log("Jump");
            if (rb != null)
            {
                rb.AddForce(Vector3.up * speed * 10f, ForceMode.Impulse);

            }
            canJump = false;
            Invoke("AllowJump", 1);
        }

    }

    void Move()
    {
        if (onGround)
        {
            var gamepads = Gamepad.all;
            int tempGamePadId = 1;
            //Debug.Log(controllerId);
            foreach (var gamepad in gamepads)
            {
                
                //if (gamepad.deviceId == controllerId)
                if (controllerId == tempGamePadId)
                {
                    float horizontalInput = gamepad.leftStick.x.ReadValue() * -1;
                    float verticalInput = gamepad.leftStick.y.ReadValue() * -1;
                    if (rb == null)
                        rb = GetComponent<Rigidbody>();
                    rb.AddForce(new Vector3(horizontalInput, 0, verticalInput) * speed);
                
                }

                tempGamePadId++;

                //    //Debug.Log("Gamepad: " + gamepad.deviceId);
                //    //Debug.Log("tempGamePadId: " + tempGamePadId);
                //    //Debug.Log("Player ID: " + playerId);
                //    //if (gamepad.deviceId == playerId + 13)
                //    //if (tempGamePadId == playerId)
                //    //{
                //        //tempGamePadId++;
                //    float horizontalInput = gamepad.leftStick.x.ReadValue();
                //    float verticalInput = gamepad.leftStick.y.ReadValue();
                //    rb.AddForce(new Vector3(horizontalInput, 0, verticalInput) * speed);
                //    //}
            }

            //float horizontalInput = Input.GetAxis("Horizontal") * -1;
            //float verticalInput = Input.GetAxis("Vertical") * -1;
            //rb.AddForce(new Vector3(horizontalInput, 0, verticalInput) * speed);
        }
    }

    void Jump()
    {
        if (onGround)
        {
            rb.AddForce(Vector3.up * speed, ForceMode.Impulse);
            onGround = false;

            Invoke("AllowJump", 1);
        }
    }
    public void OnTriggerEnter(Collider other)
    {
        Debug.Log("Collision Detected");
        if (other.GetComponent<Collider>().isTrigger && other.CompareTag("Blender_Trigger"))
        {
            Debug.Log("Blender Triggered");
            fruitChange.RandomFruitIndex();
            progressBar.AddSegment();
            Invoke("RespawnAsPlayer", 2);
        }
    }

    void RespawnAsPlayer()
    {
        isActive = false;
        //GameObject newHumanPlayer = Instantiate(humanPlayer, transform.position, new Quaternion(0, 0, 0, 0));

        //PlayerInput.Instantiate(humanPlayer, playerId, "Gamepad", -1, InputSystem.devices[playerId]);
        //GameObject player = Instantiate(humanPlayer) as GameObject;
        //player.transform.position = new Vector3(0.8f - playerId * 0.5f, 1, 1.1f);
        //player.GetComponent<PlayerInformation>().playerId = playerId;
        //player.GetComponent<PlayerInformation>().controllerId = InputSystem.devices[playerId].deviceId;
        GameObject player = GameObject.Find("Player" + playerId);
        //player.transform.Find("Capsule").GetComponent<MeshRenderer>().enabled = true;
        player.transform.Find("Geometry").transform.gameObject.SetActive(true);
        //player.SetActive(true);
        //player.transform.position = transform.position;
        //player.transform.position = new Vector3(0.5f, 1, 1.1f);
        //player.transform.Find("Capsule").transform.position = new Vector3(0.5f, 1, 1.1f);
        player.GetComponent<PlayerInformation>().isRespawning = true;
        //player.GetComponent<PlayerInformation>().respawnPos = blender.transform.position;
        //player.GetComponent<PlayerInformation>().respawnPos = new Vector3(0, 0, 0.5f);
        Destroy(fruit);
    }

    void AllowJump()
    {
        onGround = true;
        canJump = true;
    }
}
