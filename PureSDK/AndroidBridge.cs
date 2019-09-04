﻿using System;
using PureSDK;
using UnityEngine;
using UnityEngine.Android;

namespace Unaty.PureSDK
{
    internal class AndroidBridge : IPureSdk
    {
        private bool isTracking;

        private bool _waitingForUserToAcceptLocation;
        private readonly AndroidJavaObject _applicationContext;

        public AndroidBridge(String publisherId)
        {
#if UNITY_ANDROID
            var unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
            var activity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
            _applicationContext = activity.Call<AndroidJavaObject>("getApplicationContext");
            
            var sdk = GetSDK();
            sdk.Call("init",publisherId, null);
            isTracking = sdk.Call<bool>("isTracking");
#endif
        }

        private AndroidJavaObject GetSDK()
        {
            var sdkClass = new AndroidJavaClass("com.pure.sdk.Pure");
            return sdkClass.CallStatic<AndroidJavaObject>("getInstance", _applicationContext);
        }

        public void StartTracking()
        {
#if UNITY_ANDROID
            if (!Permission.HasUserAuthorizedPermission(Permission.FineLocation))
            {
                Permission.RequestUserPermission(Permission.FineLocation);
                _waitingForUserToAcceptLocation = true;
            }

            GetSDK().Call("startTracking");
            isTracking = true;
#endif
        }
    
        public void StopTracking()
        {
#if UNITY_ANDROID
            GetSDK().Call("stopTracking");
#endif
            isTracking = false;
        }

        public bool IsTracking()
        {
            if (isTracking && _waitingForUserToAcceptLocation)
            {
                _waitingForUserToAcceptLocation = !Permission.HasUserAuthorizedPermission(Permission.FineLocation);
            }
            return isTracking && !_waitingForUserToAcceptLocation;
        }
    }
}
