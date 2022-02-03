using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AsteroidsGame : MonoBehaviour
{
    enum EntityType : int
    {
        Asteroid_XXL = 1 << 0,
        Asteroid_M = 1 << 1,
        Asteroid_S = 1 << 2,
        LaserShot = 1 << 3,
    }

    public Camera m_camera;
    public GameObject m_pluginController;
    PluginControl m_plg;

    public List<GameObject> m_pooledAsteroids;
    public GameObject m_asteroidObject;
    public const int m_maxNbAsteroids = 200; 
    float[] m_posAsteroidList = new float[m_maxNbAsteroids * 3];

    public List<GameObject> m_pooledLaserShots;
    public GameObject m_laserShotObject;
    public const int m_maxNbLaserShots = 300;
    float[] m_posLaserShotList = new float[m_maxNbLaserShots * 3];

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
            Debug.LogError("Incorrect plugin instantiation");
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
            Debug.LogError("Incorrect camera setup, cannot init plugin");
            return;
        }

        InitPools();
    }

    void Update()
    {
        if(!m_plg.InstanceReady()) return;

        UpdatePlugin();

        ResetPools();

        FillPools();
    }

    void UpdatePlugin()
    {
        int keyState = 0;
        keyState |= Input.GetKey(KeyCode.LeftArrow) ? (int)KeyState.Left : 0;
        keyState |= Input.GetKey(KeyCode.RightArrow) ? (int)KeyState.Right : 0;
        keyState |= Input.GetKey(KeyCode.UpArrow) ? (int)KeyState.Up : 0;
        keyState |= Input.GetKey(KeyCode.DownArrow) ? (int)KeyState.Down : 0;
        keyState |= Input.GetKey(KeyCode.Space) ? (int)KeyState.Space : 0;

        Debug.Log("Delta Time :" + Time.deltaTime + " KeyState :" + keyState);

        m_plg.SendUserCommandAndTime(keyState, Time.deltaTime);
    }

    void InitPools()
    {
        GameObject tmp;

        m_pooledAsteroids = new List<GameObject>();
        for(int i = 0; i < m_maxNbAsteroids; ++i)
        {
            tmp = Instantiate(m_asteroidObject);
            tmp.SetActive(false);
            m_pooledAsteroids.Add(tmp);
        }

        m_pooledLaserShots = new List<GameObject>();
        for(int i = 0; i < m_maxNbLaserShots; ++i)
        {
            tmp = Instantiate(m_laserShotObject);
            tmp.SetActive(false);
            m_pooledLaserShots.Add(tmp);
        }
    }

    void ResetPools()
    {
        for(int i = 0; i < m_pooledAsteroids.Count; ++i)
        {
            m_pooledAsteroids[i].SetActive(false);
        }

        for(int i = 0; i < m_pooledLaserShots.Count; ++i)
        {
            m_pooledLaserShots[i].SetActive(false);
        }
    }

    void FillPools()
    {
        int currNbAsteroids = 0;
        m_plg.FillPosEntityList(m_posAsteroidList, m_posAsteroidList.Length, out currNbAsteroids, (int)EntityType.Asteroid_M);

        if(currNbAsteroids > m_pooledAsteroids.Count) currNbAsteroids = m_pooledAsteroids.Count; // Should never happen

        for(int i = 0; i < currNbAsteroids; i++)
        {
            GameObject asteroid = m_pooledAsteroids[i];
            if(asteroid != null)
            {
                int j = i * 3;
                asteroid.transform.position = new Vector3(m_posAsteroidList[j], m_posAsteroidList[j+1], 0);
                asteroid.transform.rotation = Quaternion.Euler(0, 0, m_posAsteroidList[j+2]);
                asteroid.SetActive(true);
            }
        }

        int currNbLaserShots = 0;
        m_plg.FillPosEntityList(m_posLaserShotList, m_posLaserShotList.Length, out currNbLaserShots, (int)EntityType.LaserShot);
        
        Debug.Log("Nb laser :" + currNbLaserShots);

        if(currNbLaserShots > m_pooledLaserShots.Count) currNbLaserShots = m_pooledLaserShots.Count; // Should never happen

        for(int i = 0; i < currNbLaserShots; i++)
        {
            GameObject laserShot = m_pooledLaserShots[i];
            if(laserShot != null)
            {
                int j = i * 3;
                laserShot.transform.position = new Vector3(m_posLaserShotList[j], m_posLaserShotList[j+1], 0);
                laserShot.transform.rotation = Quaternion.Euler(0, 0, m_posLaserShotList[j+2]);
                laserShot.SetActive(true);
            }
        }
    }
}
