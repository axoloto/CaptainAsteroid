using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class Test : MonoBehaviour
{
    private IntPtr m_GamePtr = IntPtr.Zero;
    
    public GameObject spaceShipTom;

    enum KeyState : int
    {
        Left = 1 << 0,
        Right = 1 << 1,
        Up = 1 << 2,
        Down = 1 << 3,
        Space = 1 << 4,
    }

    #region Native

#if UNITY_EDITOR_WIN || UNITY_STANDALONE_WIN
    private const string AsteroidNativeDLL = "CaptainAsteroid.dll";
#elif UNITY_EDITOR_OSX || UNITY_STANDALONE_OSX
    private const string AsteroidNativeDLL = "__Internal";
#endif

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr HelloWorld();

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int AddNumbers(int a, int b);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern int MultiplyNumbers(int a, int b);

    [DllImport(AsteroidNativeDLL, CallingConvention = CallingConvention.Cdecl)]
    static extern void Update(IntPtr gamePtr, int keyState, float deltaTime);
    #endregion

    // Start is called before the first frame update
    void Start()
    {
        //Instantiate(spaceShipTom, Vector3.null, Quaternion.identity);

        //Demo
        var ret = Marshal.PtrToStringAnsi(HelloWorld());
        Debug.Log("Got back string: " + ret);
        int a = UnityEngine.Random.Range(0, 100);
        int b = UnityEngine.Random.Range(0, 100);
        var retInt = AddNumbers(a, b);
        Debug.Log($"Adding numbers {a} and {b}: " + retInt);
    }

    public float Multiply()
    {
        int a = UnityEngine.Random.Range(0, 100);
        int b = UnityEngine.Random.Range(0, 100);
        return MultiplyNumbers(a, b);
    }

    // Update is called once per frame
    void Update()
    {
        if(m_GamePtr == null)
        {
            return;
        }

        int keyState = 0;

        int a = UnityEngine.Random.Range(0, 100);
        int b = UnityEngine.Random.Range(0, 100);
        var retInt = MultiplyNumbers(a, b);
        //Debug.Log($"LOOP Multiply numbers {a} and {b}: " + retInt);

        //spaceShipTom.Move(retInt / 1000.0f);

        keyState |= Input.GetKey(KeyCode.LeftArrow) ? (int)KeyState.Left : 0;
        keyState |= Input.GetKey(KeyCode.RightArrow) ? (int)KeyState.Right : 0;
        keyState |= Input.GetKey(KeyCode.UpArrow) ? (int)KeyState.Up : 0;
        keyState |= Input.GetKey(KeyCode.DownArrow) ? (int)KeyState.Down : 0;
        keyState |= Input.GetKey(KeyCode.Space) ? (int)KeyState.Space : 0;

        Update(m_GamePtr, keyState, Time.deltaTime);
    }
}
