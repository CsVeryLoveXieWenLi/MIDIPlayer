/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-01-31 22:46:51
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-01 00:05:06
 * @Description: 事件监听与移除
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */

#include "Listener.h"

#include <cstdio>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/schedule/Scheduler.h>
#include <ll/api/schedule/Task.h>
#include <mc/network/packet/PlaySoundPacket.h>
#include <random>


namespace Listener {

using namespace ll::event;

ListenerPtr mPlayerJoinEventListener;

std::deque<std::string> SOUNDS{
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


// 装载所有监听
void install() {
    auto& eventBus = EventBus::getInstance();

    mPlayerJoinEventListener = eventBus.emplaceListener<PlayerJoinEvent>([&](PlayerJoinEvent& event) {
        using namespace ll::schedule;
        using namespace ll::chrono_literals;

        auto& player = static_cast<Player&>(event.self());

        SystemTimeScheduler scheduler;

        std::random_device                 rd;
        std::mt19937                       gen(rd());
        std::uniform_int_distribution<int> dist(0, 87);

        scheduler.add<RepeatTask>(std::chrono::milliseconds(1), [&player, &dist, &gen]() {
            printf("success\n");

            PlaySoundPacket packet("note.pling", player.getPosition(), 1.0, 1.0);
            packet.sendTo(player);
        });
    });
};

// 移除所有监听
void remove() {
    auto& eventBus = EventBus::getInstance();

    eventBus.removeListener(mPlayerJoinEventListener);
};

} // namespace Listener