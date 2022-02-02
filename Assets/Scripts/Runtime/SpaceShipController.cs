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
        float rotDeg = 0.0f;
        plg.GetSpaceShipCoords(ref x, ref y, ref rotDeg);

        spaceShip.position = new Vector3(x, y, 0.0f);

        spaceShip.Rotate(0,0, rotDeg);
        
        Debug.Log(" SpaceShip Coords x " + spaceShip.position.x + " y " + spaceShip.position.y + " rotation " + rotDeg);
    }

    public void Move(float i)
    {
       //spaceShip.position += Vector3.up * 0.08f; 
    }
}
