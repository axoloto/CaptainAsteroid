using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AsteroidsGame : MonoBehaviour
{
    public Camera m_camera;
    public GameObject m_pluginController;
    PluginControl m_plg;

    const int m_maxNbAsteroid = 200;
    float[] m_posAsteroidList = new float[m_maxNbAsteroid * 3];

    enum EntityType : int
    {
        Asteroid_XXL = 1 << 0,
        Asteroid_M = 1 << 1,
        Asteroid_S = 1 << 2,
        LaserShot = 1 << 3,
    }

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
        m_plg = m_pluginController.GetComponent<PluginControl>();
        if(!m_plg.InstanceReady())
        {
            Debug.LogError("Incorrect Captain Asteroids plugin instantiation");
            return;
        }

        if(m_camera.orthographic)
        {
            float boundaryV = m_camera.orthographicSize;
            float boundaryH = m_camera.aspect * boundaryV;
            Debug.Log("Boundary " + boundaryV + " " + boundaryH);

            m_plg.InitPlugin(boundaryV, boundaryH);
        }
        else
        {
            Debug.LogError("Incorrect camera setup, cannot init Captain Asteroids plugin");
        }
    }

    void Update()
    {
        if(!m_plg.InstanceReady()) return;

        int keyState = 0;
        keyState |= Input.GetKey(KeyCode.LeftArrow) ? (int)KeyState.Left : 0;
        keyState |= Input.GetKey(KeyCode.RightArrow) ? (int)KeyState.Right : 0;
        keyState |= Input.GetKey(KeyCode.UpArrow) ? (int)KeyState.Up : 0;
        keyState |= Input.GetKey(KeyCode.DownArrow) ? (int)KeyState.Down : 0;
        keyState |= Input.GetKey(KeyCode.Space) ? (int)KeyState.Space : 0;

        //Debug.Log(" Delta Time " + Time.deltaTime + " KeyState " + keyState);

        m_plg.SendUserCommandAndTime(keyState, Time.deltaTime);

        int filledAmount = 0;
        m_plg.FillPosEntityList(m_posAsteroidList, m_maxNbAsteroid * 3, out filledAmount, (int)EntityType.Asteroid_M);
        Debug.Log(" Fill Pos Entity " + m_posAsteroidList[0] + "  " + m_posAsteroidList[1] + " " + filledAmount);
    }
}
