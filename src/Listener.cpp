/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-01-31 22:46:51
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-02 18:24:16
 * @Description: 事件监听与移除
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */

#include "Listener.h"

#include "Functions.h"

#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/player/PlayerLeaveEvent.h>
#include <ll/api/schedule/Scheduler.h>
#include <ll/api/schedule/Task.h>
#include <mc/network/packet/PlaySoundPacket.h>


namespace listener {

using namespace ll::event;


ListenerPtr mPlayerJoinEventListener;
ListenerPtr mPlayerLeaveEventListener;


// 装载所有监听
void install() {
    auto& bus = EventBus::getInstance();

    mPlayerJoinEventListener = bus.emplaceListener<PlayerJoinEvent>(function::playerJoinEventFunction);

    mPlayerLeaveEventListener = bus.emplaceListener<PlayerLeaveEvent>(function::playerLeaveEventFunction);
}

// 移除所有监听
void remove() {
    auto& bus = EventBus::getInstance();

    bus.removeListener(mPlayerJoinEventListener);
    bus.removeListener(mPlayerLeaveEventListener);
}

} // namespace listener