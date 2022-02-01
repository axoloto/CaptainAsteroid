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
    static extern int AddNumbers(int a, int b);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int MultiplyNumbers(int a, int b);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void GetSpaceShip(IntPtr gamePtr, ref float x, ref float y);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void Update(IntPtr gamePtr, int keyState, float deltaTime);
    #endregion

    // Start is called before the first frame update
    void Start()
    {
        Debug.Log($"Plugin Controller !!!!! Creating CPP Instance");
        if(m_GamePtr == IntPtr.Zero)
        {
            m_GamePtr = CreateInstance();
        }
        Debug.Log($"Plugin Controller !!!!! Created CPP Instance" + m_GamePtr);
    }

    void OnDestroy()
    {
        DeleteInstance(m_GamePtr);
        Debug.Log($"Plugin Controller !!!!! Removing CPP Instance");
        m_GamePtr = IntPtr.Zero;
    }

    void Update()
    {
        // Do nothing
        // GameObjects will do what they need
    }

    public bool isInGame()
    {
        return m_GamePtr != IntPtr.Zero;
    }

    public int Multiply()
    {
        int a = UnityEngine.Random.Range(0, 100);
        int b = UnityEngine.Random.Range(0, 100);
        return AddNumbers(a, b);
    }

    public void GetSpaceShipCoords(ref float x, ref float y)
    {
        if(isInGame())
        {
            //Debug.Log($"Plugin Controller / Old space ship coords, x" + x + " y " + y);
            GetSpaceShip(m_GamePtr, ref x, ref y);
            //Debug.Log($"Plugin Controller / New space ship coords, x" + x + " y " + y);
        }
    }

    public void SendUserCommandAndTime(int keyState, float deltaTime)
    {
        if(isInGame())
        {
            Update(m_GamePtr, keyState, deltaTime);
        }
    }
}
