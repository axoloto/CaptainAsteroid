using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

// Class controlling access to Captain Asteroid Plugin
public class CaptainAsteroidPlugin : MonoBehaviour
{
    private IntPtr m_GamePtr = IntPtr.Zero;

    public enum GameState : int
    {
        StartGame = 1 << 0,
        Playing = 1 << 1,
        GameOver = 1 << 2,
        Victory = 1 << 3,
    }

    // Input parameters to initialize the plugin
    // Some are modifiable on Unity UI side
    [StructLayout(LayoutKind.Sequential)]
    public struct InitParams
    {
        public float boundaryDomainV;
        public float boundaryDomainH;
        public int initNbAsteroidsXXL;
        public int initNbAsteroidsM;
        public int initNbAsteroidsS;
        public int maxNbAsteroidsByType;
    }

    #region Native

#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
    private const string CaptainAsteroidNativeDLL = "CaptainAsteroid.dll";
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
    private const string CaptainAsteroidNativeDLL = "__Internal";
#endif

    // First call to be made to generate the game on native side
    [DllImport(CaptainAsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr CreateNativeInstance();

    // Last call to be made to release memory on native side
    [DllImport(CaptainAsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void DeleteNativeInstance(IntPtr ptr);

    // Initializing the native game with the input parameters
    [DllImport(CaptainAsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void Init(IntPtr gamePtr, InitParams initParams);

    // Updating the native game at each time frame with player input
    [DllImport(CaptainAsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void Update(IntPtr gamePtr, int keyState, float deltaTime);

    // Specific Function for Space Ship Controller
    [DllImport(CaptainAsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void GetSpaceShipCoords(IntPtr gamePtr, ref float x, ref float y, ref float angle);

    // Generic Access to Non Playable Entities positions and angle (x,y,theta) from native side, used for Asteroids and Laser Shots
    // Buffer generated on managed memory side and never deleted during run-time, reused at every frame to improve performance
    // Native plugin is only filling it up to nbEntities
    [DllImport(CaptainAsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void FillPosEntityList(IntPtr gamePtr, IntPtr posEntities, int size, out int nbEntities, int typeEntity);

    [DllImport(CaptainAsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern GameState CurrentGameState(IntPtr gamePtr);

    [DllImport(CaptainAsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int CurrentScore(IntPtr gamePtr);

    [DllImport(CaptainAsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int CurrentNbAsteroids(IntPtr gamePtr);

    #endregion

    void Start()
    {
        Debug.Log("Creating Native Instance");

        if(!IsNativeInstanceReady())
        {
            m_GamePtr = CreateNativeInstance();
        }

        if(!IsNativeInstanceReady())
        {
            Debug.LogError("Incorrect Captain Asteroid plugin instantiation");
        }
    }

    void OnDestroy()
    {
        if(IsNativeInstanceReady())
        {
            DeleteNativeInstance(m_GamePtr);
            m_GamePtr = IntPtr.Zero;
            //Debug.Log("Removing Native Instance");
        }
    }

    void Update()
    {
    }

    bool IsNativeInstanceReady()
    {
        return m_GamePtr != IntPtr.Zero;
    }

    // API for other scripts

    public void ResetPlugin()
    {
        if(IsNativeInstanceReady())
        {
            DeleteNativeInstance(m_GamePtr);
            m_GamePtr = IntPtr.Zero;
        }
        if(!IsNativeInstanceReady())
        {
            m_GamePtr = CreateNativeInstance();
        }
        //Debug.Log("Resetting Native Instance");
    }

    // Friendlier than IsNativeInstanceReady outside of this class
    public bool IsPluginReady()
    {
        return IsNativeInstanceReady();
    }

    public void InitPlugin(InitParams initParams)
    {
        if(IsNativeInstanceReady())
        {
            Init(m_GamePtr, initParams);
        }
    }

    public void UpdatePlugin(int keyState, float deltaTime)
    {
        if(IsNativeInstanceReady())
        {
            Update(m_GamePtr, keyState, deltaTime);
        }
    }   

    public void GetSpaceShipCoords(ref float x, ref float y, ref float angle)
    {
        if(IsNativeInstanceReady())
        {
            GetSpaceShipCoords(m_GamePtr, ref x, ref y, ref angle);
        }
    }

    public unsafe void FillPosEntityList(float[] posEntities, int size, out int nbEntities, int entityType)
    {
        nbEntities = 0;

        if(IsNativeInstanceReady())
        {
            // Pin Memory
            fixed (float* fixPtr = posEntities)
            {
                FillPosEntityList(m_GamePtr, (IntPtr)fixPtr, size, out nbEntities, entityType);
            }
        }
    }

    public GameState CurrentGameState()
    {
        if(IsNativeInstanceReady())
        {
            return CurrentGameState(m_GamePtr);
        }
        return GameState.GameOver;
    }

    public int CurrentScore()
    {
        if(IsNativeInstanceReady())
        {
            return CurrentScore(m_GamePtr);
        }
        return 0;
    }

    public int CurrentNbAsteroids()
    {
        if(IsNativeInstanceReady())
        {
            return CurrentNbAsteroids(m_GamePtr);
        }
        return 0;
    }
}
