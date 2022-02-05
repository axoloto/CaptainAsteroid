using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public GameObject m_pluginController;
    CaptainAsteroidPlugin m_plg;

	private Text m_scoreText;

    void Start()
    {
        m_scoreText = GetComponent<Text>();

        m_plg = m_pluginController.GetComponent<CaptainAsteroidPlugin>();

        if(!m_plg.IsPluginReady())
        {
            Debug.LogError("Incorrect plugin instantiation");
            return;
        }
    }

    void Update()
    {
        m_scoreText.text = "Score : " + m_plg.CurrentScore() + " Asteroids : " + m_plg.CurrentNbAsteroids();
    }
}
