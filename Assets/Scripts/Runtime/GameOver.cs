using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameOver : MonoBehaviour 
{
    public static bool restartGame = false; 

    public GameObject m_pluginController;
    CaptainAsteroidPlugin m_plg;

	private Text m_gameOverText;

	void Start()
    {
		m_gameOverText = GetComponent<Text>();
		m_gameOverText.enabled = false;

        m_plg = m_pluginController.GetComponent<CaptainAsteroidPlugin>();

        if(!m_plg.IsPluginReady())
        {
            Debug.LogError("Incorrect plugin instantiation");
            return;
        }
	}

	void Update() 
    {
		m_gameOverText.enabled = (m_plg.CurrentGameState() == CaptainAsteroidPlugin.GameState.GameOver);
        
        if(m_gameOverText.enabled)
        {
            restartGame = Input.GetKey(KeyCode.LeftArrow);
        }
        else
       {
            restartGame = false;
        }
	}
}
