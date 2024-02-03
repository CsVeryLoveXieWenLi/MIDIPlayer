/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-02-02 17:27:32
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-04 04:23:55
 * @Description: 播放队列
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */

#include "Task.h"

#include <ll/api/base/StdInt.h>
#include <ll/api/schedule/Scheduler.h>
#include <ll/api/schedule/Task.h>
#include <mc/network/packet/PlaySoundPacket.h>
#include <mc/world/actor/player/Player.h>


namespace task {

using namespace ll::schedule;
using namespace ll::chrono_literals;


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


// 初始化
MusicPlayer::MusicPlayer(Player* player) { this->player = player; }

// 播放
void MusicPlayer::play(std::deque<std::deque<uint8>>& notes, std::deque<uint16>& times) {
    // 清空缓存
    if (is_play) stop();

    // 状态
    this->is_play = true;

    // 缓存
    this->notes = notes;
    this->times = times;

    // 首个音符
    this->note = this->notes.front();
    this->notes.pop_front();

    this->time = this->times.front();
    this->times.pop_front();

    // 每1毫秒检查一次
    scheduler.add<RepeatTask>(1ms, [&]() {
        // 每次经过1毫秒
        this->time--;

        // printf("%zu %i %zu %zu\n", this->note.size(), this->time, this->notes.size(), this->times.size());

        // 播放完毕
        if (this->notes.empty()) {
            return stop();
        }

        // 时间未到
        if (this->time > 0) {
            return;
        }

        // 播放
        for (uint8 pitch : this->note) {
            pitch -= 21;
            if (pitch > 87 || pitch < 0) continue;

            PlaySoundPacket packet(PIANO_NOTES[pitch], player->getPosition(), 1.0, 1.0);
            packet.sendTo(*player);
        }

        // 播放完毕 修改
        this->note = this->notes.front();
        this->notes.pop_front();

        this->time = this->times.front();
        this->times.pop_front();
    });
}

// 停止
void MusicPlayer::stop() {
    scheduler.clear();

    notes.clear();
    times.clear();

    note.clear();
    time = 0;

    is_play = false;
}

} // namespace task