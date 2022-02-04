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

    public List<GameObject> m_pooledAsteroidsXXL;
    public GameObject m_asteroidObjectXXL;
    public int m_initNbAsteroidsXXL = 30;

    public List<GameObject> m_pooledAsteroidsM;
    public GameObject m_asteroidObjectM;
    public int m_initNbAsteroidsM = 0;

    public List<GameObject> m_pooledAsteroidsS;
    public GameObject m_asteroidObjectS;
    public int m_initNbAsteroidsS = 0;
    
    public const int m_maxNbAsteroidsByType = 200; 
    float[] m_posAsteroidList = new float[m_maxNbAsteroidsByType * 3];

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

        if(!m_plg.IsPluginReady())
        {
            Debug.LogError("Incorrect plugin instantiation");
            return;
        }

        if(m_camera.orthographic)
        {
            InitParams initParams;
            initParams.initNbAsteroidsXXL = m_initNbAsteroidsXXL;
            initParams.initNbAsteroidsM = m_initNbAsteroidsM;
            initParams.initNbAsteroidsS = m_initNbAsteroidsS;
            initParams.maxNbAsteroidsByType = m_maxNbAsteroidsByType;
            initParams.boundaryDomainV = m_camera.orthographicSize;
            initParams.boundaryDomainH = m_camera.aspect * initParams.boundaryDomainV;

            m_plg.InitPlugin(initParams);
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
        if(m_plg.IsPluginReady())
        {
            UpdatePlugin();

            ResetPools();

            FillPools();
        }
    }

    void UpdatePlugin()
    {
        int keyState = 0;

        keyState |= Input.GetKey(KeyCode.LeftArrow) ? (int)KeyState.Left : 0;
        keyState |= Input.GetKey(KeyCode.RightArrow) ? (int)KeyState.Right : 0;
        keyState |= Input.GetKey(KeyCode.UpArrow) ? (int)KeyState.Up : 0;
        keyState |= Input.GetKey(KeyCode.DownArrow) ? (int)KeyState.Down : 0;
        keyState |= Input.GetKey(KeyCode.Space) ? (int)KeyState.Space : 0;

        m_plg.UpdatePlugin(keyState, Time.deltaTime);
    }

    void InitPools()
    {
        GameObject tmp;

        m_pooledAsteroidsXXL = new List<GameObject>();
        for(int i = 0; i < m_maxNbAsteroidsByType; ++i)
        {
            tmp = Instantiate(m_asteroidObjectXXL);
            tmp.SetActive(false);
            m_pooledAsteroidsXXL.Add(tmp);
        }

        m_pooledAsteroidsM = new List<GameObject>();
        for(int i = 0; i < m_maxNbAsteroidsByType; ++i)
        {
            tmp = Instantiate(m_asteroidObjectM);
            tmp.SetActive(false);
            m_pooledAsteroidsM.Add(tmp);
        }

        m_pooledAsteroidsS = new List<GameObject>();
        for(int i = 0; i < m_maxNbAsteroidsByType; ++i)
        {
            tmp = Instantiate(m_asteroidObjectS);
            tmp.SetActive(false);
            m_pooledAsteroidsS.Add(tmp);
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
        for(int i = 0; i < m_pooledAsteroidsXXL.Count; ++i)
        {
            m_pooledAsteroidsXXL[i].SetActive(false);
        }

        for(int i = 0; i < m_pooledAsteroidsM.Count; ++i)
        {
            m_pooledAsteroidsM[i].SetActive(false);
        }

        for(int i = 0; i < m_pooledAsteroidsS.Count; ++i)
        {
            m_pooledAsteroidsS[i].SetActive(false);
        }

        for(int i = 0; i < m_pooledLaserShots.Count; ++i)
        {
            m_pooledLaserShots[i].SetActive(false);
        }
    }

    void FillPools()
    {
        int currNbAsteroids = 0;
        m_plg.FillPosEntityList(m_posAsteroidList, m_posAsteroidList.Length, out currNbAsteroids, (int)EntityType.Asteroid_XXL);
        Debug.Log("Pool xxl :" + currNbAsteroids);

        if(currNbAsteroids > m_pooledAsteroidsXXL.Count) currNbAsteroids = m_pooledAsteroidsXXL.Count; // Should never happen

        for(int i = 0; i < currNbAsteroids; i++)
        {
            GameObject asteroid = m_pooledAsteroidsXXL[i];
            if(asteroid != null)
            {
                int j = i * 3;
                asteroid.transform.position = new Vector3(m_posAsteroidList[j], m_posAsteroidList[j+1], 0);
                asteroid.transform.rotation = Quaternion.Euler(0, 0, m_posAsteroidList[j+2]);
                asteroid.SetActive(true);
            }
        }

        m_plg.FillPosEntityList(m_posAsteroidList, m_posAsteroidList.Length, out currNbAsteroids, (int)EntityType.Asteroid_M);

        if(currNbAsteroids > m_pooledAsteroidsM.Count) currNbAsteroids = m_pooledAsteroidsM.Count; // Should never happen

        for(int i = 0; i < currNbAsteroids; i++)
        {
            GameObject asteroid = m_pooledAsteroidsM[i];
            if(asteroid != null)
            {
                int j = i * 3;
                asteroid.transform.position = new Vector3(m_posAsteroidList[j], m_posAsteroidList[j+1], 0);
                asteroid.transform.rotation = Quaternion.Euler(0, 0, m_posAsteroidList[j+2]);
                asteroid.SetActive(true);
            }
        }

        m_plg.FillPosEntityList(m_posAsteroidList, m_posAsteroidList.Length, out currNbAsteroids, (int)EntityType.Asteroid_S);

        if(currNbAsteroids > m_pooledAsteroidsS.Count) currNbAsteroids = m_pooledAsteroidsS.Count; // Should never happen

        for(int i = 0; i < currNbAsteroids; i++)
        {
            GameObject asteroid = m_pooledAsteroidsS[i];
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

        Debug.Log("Current Nb Asteroids : " + currNbAsteroids + " Current Nb Laser Shots :" + currNbLaserShots);
    }
}
