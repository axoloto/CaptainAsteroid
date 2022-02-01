using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpaceShipController : MonoBehaviour
{
    private Transform spaceShip;
    public float thrust;

    public GameObject pluginController;
    PluginControl plg;

    void Start()
    {
        spaceShip = GetComponent<Transform>();
        plg = pluginController.GetComponent<PluginControl>();
    }

    void Update()
    {
        float x = spaceShip.position.x;
        float y = spaceShip.position.y;
        plg.GetSpaceShipCoords(ref x, ref y);

        spaceShip.position = new Vector3(x, y, 0.0f);

        Debug.Log(" SpaceShip Coords x " + spaceShip.position.x + " y " + spaceShip.position.y);
    }

    public void Move(float i)
    {
       //spaceShip.position += Vector3.up * 0.08f; 
    }
}
