/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-02-02 16:51:10
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-02 17:00:34
 * @Description: 全局静态数据
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once


#include <deque>


const char* COMMAND_NAME        = "midi";
const char* COMMAND_ALIAS       = "mid";
const char* COMMAND_DESCRIPTION = "play you midi";

std::deque<const char*> PIANO_NOTES{
    "midi.piano.A0",  "midi.piano.Bb0", "midi.piano.B0", "midi.piano.C1",  "midi.piano.Db1", "midi.piano.D1",
    "midi.piano.Eb1", "midi.piano.E1",  "midi.piano.F1", "midi.piano.Gb1", "midi.piano.G1",  "midi.piano.Ab1",
    "midi.piano.A1",  "midi.piano.Bb1", "midi.piano.B1", "midi.piano.C2",  "midi.piano.Db2", "midi.piano.D2",
    "midi.piano.Eb2", "midi.piano.E2",  "midi.piano.F2", "midi.piano.Gb2", "midi.piano.G2",  "midi.piano.Ab2",
    "midi.piano.A2",  "midi.piano.Bb2", "midi.piano.B2", "midi.piano.C3",  "midi.piano.Db3", "midi.piano.D3",
    "midi.piano.Eb3", "midi.piano.E3",  "midi.piano.F3", "midi.piano.Gb3", "midi.piano.G3",  "midi.piano.Ab3",
    "midi.piano.A3",  "midi.piano.Bb3", "midi.piano.B3", "midi.piano.C4",  "midi.piano.Db4", "midi.piano.D4",
    "midi.piano.Eb4", "midi.piano.E4",  "midi.piano.F4", "midi.piano.Gb4", "midi.piano.G4",  "midi.piano.Ab4",
    "midi.piano.A4",  "midi.piano.Bb4", "midi.piano.B4", "midi.piano.C5",  "midi.piano.Db5", "midi.piano.D5",
    "midi.piano.Eb5", "midi.piano.E5",  "midi.piano.F5", "midi.piano.Gb5", "midi.piano.G5",  "midi.piano.Ab5",
    "midi.piano.A5",  "midi.piano.Bb5", "midi.piano.B5", "midi.piano.C6",  "midi.piano.Db6", "midi.piano.D6",
    "midi.piano.Eb6", "midi.piano.E6",  "midi.piano.F6", "midi.piano.Gb6", "midi.piano.G6",  "midi.piano.Ab6",
    "midi.piano.A6",  "midi.piano.Bb6", "midi.piano.B6", "midi.piano.C7",  "midi.piano.Db7", "midi.piano.D7",
    "midi.piano.Eb7", "midi.piano.E7",  "midi.piano.F7", "midi.piano.Gb7", "midi.piano.G7",  "midi.piano.Ab7",
    "midi.piano.A7",  "midi.piano.Bb7", "midi.piano.B7", "midi.piano.C8"
};