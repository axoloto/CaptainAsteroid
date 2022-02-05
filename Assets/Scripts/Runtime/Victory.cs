using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Victory : MonoBehaviour 
{
    public GameObject m_pluginController;
    CaptainAsteroidPlugin m_plg;

	private Text victory;

	void Start()
    {
		victory = GetComponent<Text>();
		victory.enabled = false;

        m_plg = m_pluginController.GetComponent<CaptainAsteroidPlugin>();

        if(!m_plg.IsPluginReady())
        {
            Debug.LogError("Incorrect plugin instantiation");
            return;
        }
	}

	void Update() 
    {
		victory.enabled = (m_plg.CurrentGameState() == CaptainAsteroidPlugin.GameState.Victory);
	}
}
