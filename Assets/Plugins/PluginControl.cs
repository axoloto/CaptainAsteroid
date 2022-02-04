using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

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

public class PluginControl : MonoBehaviour
{
    private IntPtr m_GamePtr = IntPtr.Zero;

    #region Native

#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
    private const string AsteroidNativeDLL = "CaptainAsteroid.dll";
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
    private const string AsteroidNativeDLL = "__Internal";
#endif

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr CreateNativeInstance();

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void DeleteNativeInstance(IntPtr ptr);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void Init(IntPtr gamePtr, InitParams initParams);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void Update(IntPtr gamePtr, int keyState, float deltaTime);

    // Helper Function for Space Ship Controller
    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void GetSpaceShipCoords(IntPtr gamePtr, ref float x, ref float y, ref float angle);

    // Generic Access to Entities positions and angle (x,y,theta) from native side
    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void FillPosEntityList(IntPtr gamePtr, IntPtr posEntities, int size, out int nbEntities, int typeEntity);

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
            Debug.LogError("Incorrect Captain Asteroids plugin instantiation");
        }
    }

    void OnDestroy()
    {
        if(IsNativeInstanceReady())
        {
            DeleteNativeInstance(m_GamePtr);
            m_GamePtr = IntPtr.Zero;
            Debug.Log("Removing Native Instance");
        }
    }

    void Update()
    {
    }

    bool IsNativeInstanceReady()
    {
        return m_GamePtr != IntPtr.Zero;
    }

    // Friendlier API
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
}
