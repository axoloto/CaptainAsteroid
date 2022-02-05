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

    enum KeyState : int
    {
        Left = 1 << 0,
        Right = 1 << 1,
        Up = 1 << 2,
        Down = 1 << 3,
        Space = 1 << 4,
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
    public const int m_maxNbLaserShots = 100;
    float[] m_posLaserShotList = new float[m_maxNbLaserShots * 3];

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
            PluginControl.InitParams initParams;

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

        InitAllPools();
    }

    void Update()
    {
        if(m_plg.IsPluginReady())
        {
            UpdatePlugin();

            FillAllPools();
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

    void InitAllPools()
    {
        m_pooledAsteroidsXXL = new List<GameObject>();
        InitPool(ref m_pooledAsteroidsXXL, m_asteroidObjectXXL, m_maxNbAsteroidsByType);

        m_pooledAsteroidsM = new List<GameObject>();
        InitPool(ref m_pooledAsteroidsM, m_asteroidObjectM, m_maxNbAsteroidsByType);

        m_pooledAsteroidsS = new List<GameObject>();
        InitPool(ref m_pooledAsteroidsS, m_asteroidObjectS, m_maxNbAsteroidsByType);

        m_pooledLaserShots = new List<GameObject>();
        InitPool(ref m_pooledLaserShots, m_laserShotObject, m_maxNbLaserShots);
    }

    void InitPool(ref List<GameObject> list, GameObject gameObjectType, int listSize)
    {
        GameObject tmp;
        for(int i = 0; i < listSize; ++i)
        {
            tmp = Instantiate(gameObjectType);
            tmp.SetActive(false);
            list.Add(tmp);
        }
    }

    void FillAllPools()
    {
        FillPool(ref m_pooledAsteroidsXXL, ref m_posAsteroidList, EntityType.Asteroid_XXL);
        FillPool(ref m_pooledAsteroidsM, ref m_posAsteroidList, EntityType.Asteroid_M);
        FillPool(ref m_pooledAsteroidsS, ref m_posAsteroidList, EntityType.Asteroid_S);
        FillPool(ref m_pooledLaserShots, ref m_posLaserShotList, EntityType.LaserShot);
    }

    void FillPool(ref List<GameObject> pool, ref float[] buffer, EntityType type)
    {
        int currNbEntities = 0;

        m_plg.FillPosEntityList(buffer, buffer.Length, out currNbEntities, (int)type);

        for(int i = 0; i < pool.Count; i++)
        {
            GameObject entity = pool[i];
            if(entity != null)
            {
                if(i < currNbEntities)
                {
                    int j = i * 3;
                    entity.transform.position = new Vector3(buffer[j], buffer[j+1], 0);
                    entity.transform.rotation = Quaternion.Euler(0, 0, buffer[j+2]);
                    entity.SetActive(true);
                }
                else
                {
                    entity.SetActive(false);
                }
            }
        }        
    }
}
