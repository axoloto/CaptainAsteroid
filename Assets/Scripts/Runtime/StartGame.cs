using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class StartGame : MonoBehaviour 
{
    public GameObject m_pluginController;
    CaptainAsteroidPlugin m_plg;

	private Text startGame;

	void Start()
    {
		startGame = GetComponent<Text>();
		startGame.enabled = false; 
        
        m_plg = m_pluginController.GetComponent<CaptainAsteroidPlugin>();

        if(!m_plg.IsPluginReady())
        {
            Debug.LogError("Incorrect plugin instantiation");
            return;
        }
	}

	void Update() 
    {
		startGame.enabled = (m_plg.CurrentGameState() == CaptainAsteroidPlugin.GameState.StartGame);
	}
}
