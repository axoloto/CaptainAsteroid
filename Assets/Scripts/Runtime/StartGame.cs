using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class StartGame : MonoBehaviour 
{
    public static bool startGame = false;

    public GameObject m_pluginController;
    CaptainAsteroidPlugin m_plg;

	private Text m_startGameText;

	void Start()
    {
		m_startGameText = GetComponent<Text>();
		m_startGameText.enabled = false; 
        
        m_plg = m_pluginController.GetComponent<CaptainAsteroidPlugin>();

        if(!m_plg.IsPluginReady())
        {
            Debug.LogError("Incorrect plugin instantiation");
            return;
        }
	}

	void Update() 
    {
		m_startGameText.enabled = (m_plg.CurrentGameState() == CaptainAsteroidPlugin.GameState.StartGame);

        if(m_startGameText.enabled)
        {
            startGame = Input.GetKey(KeyCode.LeftArrow);
        }
        else
        {
            startGame = false;
        }
	}
}
