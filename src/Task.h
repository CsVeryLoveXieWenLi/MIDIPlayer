/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-02-02 17:27:40
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-02 19:07:16
 * @Description: 播放队列
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once


#include <ll/api/base/StdInt.h>
#include <ll/api/schedule/Scheduler.h>
#include <ll/api/schedule/Task.h>
#include <mc/network/packet/PlaySoundPacket.h>
#include <mc/world/actor/player/Player.h>


namespace task {

using namespace ll::schedule;
using namespace ll::chrono_literals;

class MusicPlayer {

public:
    // 初始化
    explicit MusicPlayer(Player* player);

    // 播放
    void play(std::deque<std::deque<uint8>>& notes, std::deque<uint16>& times);

    // 停止
    void stop();

private:
    Player* player;
    bool    is_play = false;

    std::deque<std::deque<uint8>> notes;
    std::deque<uint16>            times;

    std::deque<uint8> note;
    uint16            time = 0;

    // 定时器十分重要 ? ServerTimeAsyncScheduler ServerTimeScheduler SystemTimeScheduler
    SystemTimeScheduler scheduler;
};

} // namespace task