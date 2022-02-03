using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

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
    static extern IntPtr HelloWorld();

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr CreateInstance();

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void DeleteInstance(IntPtr ptr);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void Init(IntPtr gamePtr, float boundaryV, float boundaryH);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void Update(IntPtr gamePtr, int keyState, float deltaTime);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void GetSpaceShipCoords(IntPtr gamePtr, ref float x, ref float y, ref float angle);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void FillPosEntityList(IntPtr gamePtr, IntPtr posEntities, int size, out int nbEntities, int typeEntity);

    #endregion

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("Plugin Controller Creating CPP Instance");

        if(m_GamePtr == IntPtr.Zero)
        {
            m_GamePtr = CreateInstance();
        }

        if(m_GamePtr == IntPtr.Zero)
        {
            Debug.LogError("Incorrect Captain Asteroids plugin instanciation");
        }
    }

    void OnDestroy()
    {
        DeleteInstance(m_GamePtr);
        Debug.Log("Plugin Controller Removing CPP Instance");
        m_GamePtr = IntPtr.Zero;
    }

    void Update()
    {
        // Do nothing
        // GameObjects will do what they need
    }

    public bool InstanceReady()
    {
        return m_GamePtr != IntPtr.Zero;
    }

    public void GetSpaceShipCoords(ref float x, ref float y, ref float angle)
    {
        if(InstanceReady())
        {
            GetSpaceShipCoords(m_GamePtr, ref x, ref y, ref angle);
        }
    }

    public unsafe void FillPosEntityList(float[] posEntities, int size, out int nbEntities, int entityType)
    {
        nbEntities = 0;

        if(InstanceReady())
        {
            // Pin Memory
            fixed (float* fixPtr = posEntities)
            {
                FillPosEntityList(m_GamePtr, (IntPtr)fixPtr, size, out nbEntities, entityType);
            }
        }
    }

    public void SendUserCommandAndTime(int keyState, float deltaTime)
    {
        if(InstanceReady())
        {
            Update(m_GamePtr, keyState, deltaTime);
        }
    }

    public void InitPlugin(float boundaryV, float boundaryH)
    {
        if(InstanceReady())
        {
            Init(m_GamePtr, boundaryV, boundaryH);
        }
    }
}
