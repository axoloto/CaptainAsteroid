using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpaceShipController : MonoBehaviour
{
    private Transform spaceShip;
    public float thrust;

    public GameObject pluginController;
    PluginControl plg;

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("I am alive and my name is ");
        spaceShip = GetComponent<Transform>();

        plg = pluginController.GetComponent<PluginControl>();
    }

    // Update is called once per frame
    void Update()
    {
        int a = UnityEngine.Random.Range(0, 100);
        int b = UnityEngine.Random.Range(0, 100);
        int retInt = plg.Multiply();
        Debug.Log($"LOOP PPPPPPP numbers {a} and {b}: " + retInt);
    }

    public void Move(float i)
    {
       spaceShip.position += Vector3.up * 0.08f; 
    }
}
