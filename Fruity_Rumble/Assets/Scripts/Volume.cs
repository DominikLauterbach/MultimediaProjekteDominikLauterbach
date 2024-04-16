using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Audio;
using UnityEngine.UI;

public class Volume : MonoBehaviour
{
    [SerializeField] private Slider soundslider;
    [SerializeField] private AudioMixer audioMixer;

    private void Start()
    {
        SetVolume(UnityEngine.PlayerPrefs.GetFloat("SavedmasterVolume", 100));
    }

    public void SetVolume(float _value)
    {
        if(_value < 1)
        {
            _value = .001f;
        }

        RefreshSlider(_value);
        PlayerPrefs.SetFloat("SavedMasterVolume", _value);
        audioMixer.SetFloat("MasterVolume", Mathf.Log10(_value/100) * 20f);


    }
    public void RefreshSlider(float _value)
        {
            soundslider.value = _value;
        }

    public void SetVolumeFromSlider()
    {
        SetVolume(soundslider.value);
    }
}
