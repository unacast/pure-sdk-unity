﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UpgradeSizeText : MonoBehaviour
{
    public GameState state;
    private Text _text;

    // Start is called before the first frame update
    void Start()
    {
        _text = GetComponent<Text>();
    }

    // Update is called once per frame
    void Update()
    {
        _text.text = "+" + GameStateUtil.FormatNumber(state.nextUpgradeSize);
    }
}