/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-02-02 17:27:32
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-02 18:07:18
 * @Description: 播放队列
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */

#include "Task.h"

#include "Static.h"

#include <ll/api/base/StdInt.h>
#include <ll/api/schedule/Scheduler.h>
#include <ll/api/schedule/Task.h>
#include <mc/network/packet/PlaySoundPacket.h>
#include <mc/world/actor/player/Player.h>


namespace task {

// 初始化
MusicPlayer::MusicPlayer(Player* player) { this->player = player; }

// 播放
void MusicPlayer::play(std::deque<std::deque<uint8>>& notes, std::deque<uint64>& times) {
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
            PlaySoundPacket packet(PIANO_NOTES[pitch - 21], player->getPosition(), 1.0, 1.0);
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