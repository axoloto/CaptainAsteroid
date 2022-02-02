using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AsteroidsGame : MonoBehaviour
{
    public Camera m_camera;
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

    void Start()
    {
        plg = pluginController.GetComponent<PluginControl>();
        if(!plg.InstanceReady())
        {
            Debug.LogError("Incorrect Captain Asteroids plugin instantiation");
            return;
        }

        if(m_camera.orthographic)
        {
            float boundaryV = m_camera.orthographicSize;
            float boundaryH = m_camera.aspect * boundaryV;
            Debug.Log("Boundary " + boundaryV + " " + boundaryH);

            plg.InitPlugin(boundaryV, boundaryH);
        }
        else
        {
            Debug.LogError("Incorrect camera setup, cannot init Captain Asteroids plugin");
        }
    }

    void Update()
    {
        if(!plg.InstanceReady()) return;

        int keyState = 0;
        keyState |= Input.GetKey(KeyCode.LeftArrow) ? (int)KeyState.Left : 0;
        keyState |= Input.GetKey(KeyCode.RightArrow) ? (int)KeyState.Right : 0;
        keyState |= Input.GetKey(KeyCode.UpArrow) ? (int)KeyState.Up : 0;
        keyState |= Input.GetKey(KeyCode.DownArrow) ? (int)KeyState.Down : 0;
        keyState |= Input.GetKey(KeyCode.Space) ? (int)KeyState.Space : 0;

        Debug.Log(" Delta Time " + Time.deltaTime + " KeyState " + keyState);

        plg.SendUserCommandAndTime(keyState, Time.deltaTime);
    }
}
