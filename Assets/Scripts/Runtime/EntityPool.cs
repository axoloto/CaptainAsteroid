using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EntityPool : MonoBehaviour
{
    public static EntityPool Instance;
    
    public List<GameObject> m_pooledAsteroids;
    public GameObject m_asteroid;
    public int m_maxNbAsteroids;

    void Awake()
    {
       Instance = this;
    }

    void Start()
    {
        m_pooledAsteroids = new List<GameObject>();
        GameObject tmp;
        for(int i = 0; i < m_maxNbAsteroids; ++i)
        {
            tmp = Instantiate(m_asteroid);
            tmp.SetActive(false);
            m_pooledAsteroids.Add(tmp);
        }
    }

    void Update()
    {
    }

    public GameObject GetPooledObject()
    {
        for(int i = 0; i < m_maxNbAsteroids; ++i)
        {
            if(!m_pooledAsteroids[i].activeInHierarchy)
            {
                return m_pooledAsteroids[i];
            }
        }
        return null;
    }

    public void ResetPool()
    {
        for(int i =0; i < m_maxNbAsteroids; ++i)
        {
            m_pooledAsteroids[i].SetActive(false);
        }
    }
}
