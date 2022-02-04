using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpaceShipController : MonoBehaviour
{
    private Transform spaceShip;

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
        float angle = spaceShip.rotation.z;
        
        plg.GetSpaceShipCoords(ref x, ref y, ref angle);

        spaceShip.position = new Vector3(x, y, 0.0f);
        spaceShip.rotation = Quaternion.Euler(0.0f, 0.0f, angle);
    }
}
