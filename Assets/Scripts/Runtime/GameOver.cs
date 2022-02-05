using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameOver : MonoBehaviour 
{
    public GameObject m_pluginController;
    CaptainAsteroidPlugin m_plg;

	private Text gameOver;

	void Start ()
    {
		gameOver = GetComponent<Text>();
		gameOver.enabled = false;
	}

	void Update () 
    {
        m_plg = m_pluginController.GetComponent<CaptainAsteroidPlugin>();

        if(!m_plg.IsPluginReady())
        {
            Debug.LogError("Incorrect plugin instantiation");
            return;
        }

		gameOver.enabled = (m_plg.gameState() == CaptainAsteroidPlugin.GameState.GameOver);
	}
}
