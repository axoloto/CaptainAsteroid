using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AsteroidsGame : MonoBehaviour
{
    public GameObject pluginController;
    PluginControl plg;

    enum KeyState : int
    {
        Left = 1 << 0,
        Right = 1 << 1,
        Up = 1 << 2,
        Down = 1 << 3,
        Space = 1 << 4,
    }

    // Start is called before the first frame update
    void Start()
    {
        plg = pluginController.GetComponent<PluginControl>();
    }

    // Update is called once per frame
    void Update()
    {
        if(plg.isInGame())
        {
            return;
        }

        int a = UnityEngine.Random.Range(0, 100);
        int b = UnityEngine.Random.Range(0, 100);
        var retInt = plg.Multiply();
        Debug.Log($"LOOP GAAAAAME Multiply numbers {a} and {b}: " + retInt);

        int keyState = 0;

        keyState |= Input.GetKey(KeyCode.LeftArrow) ? (int)KeyState.Left : 0;
        keyState |= Input.GetKey(KeyCode.RightArrow) ? (int)KeyState.Right : 0;
        keyState |= Input.GetKey(KeyCode.UpArrow) ? (int)KeyState.Up : 0;
        keyState |= Input.GetKey(KeyCode.DownArrow) ? (int)KeyState.Down : 0;
        keyState |= Input.GetKey(KeyCode.Space) ? (int)KeyState.Space : 0;

        plg.SendUserCommandAndTime(keyState, Time.deltaTime);
    }
}
