using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Victory : MonoBehaviour 
{
    public static bool restartGame = false;

    public GameObject m_pluginController;
    CaptainAsteroidPlugin m_plg;

	private Text m_victoryText;

	void Start()
    {
        
		m_victoryText = GetComponent<Text>();
		m_victoryText.enabled = false;

        m_plg = m_pluginController.GetComponent<CaptainAsteroidPlugin>();

        if(!m_plg.IsPluginReady())
        {
            Debug.LogError("Incorrect plugin instantiation");
            return;
        }
        
	}

	void Update() 
    {
		m_victoryText.enabled = (m_plg.CurrentGameState() == CaptainAsteroidPlugin.GameState.Victory);

        if(m_victoryText.enabled)
        {
            restartGame = Input.GetKey(KeyCode.LeftArrow);
        }
        else
        {
            restartGame = false;
        }
	}
}
