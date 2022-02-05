using UnityEngine;
using UnityEngine.UI;
 
public class FPSCounter : MonoBehaviour
{
    private Text m_fpsText;
    private float m_hudRefreshRate = 1f;
 
    private float m_timer;
 
    void Start()
    {
        m_fpsText = GetComponent<Text>();
    }

    void Update()
    {
        if (Time.unscaledTime > m_timer)
        {
            int fps = (int)(1f / Time.unscaledDeltaTime);
            m_fpsText.text = "FPS : " + fps;
            m_timer = Time.unscaledTime + m_hudRefreshRate;
        }
    }
}