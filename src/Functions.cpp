/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-02-02 16:34:19
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-02 18:49:41
 * @Description: 功能的实现
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */

#include "Functions.h"

#include "MIDI.h"
#include "Task.h"

#include <unordered_map>


namespace function {

using namespace ll::event;


// 所有玩家的播放器
std::unordered_map<mce::UUID, task::MusicPlayer*> MusicList;


// 玩家加入监听
void playerJoinEventFunction(PlayerJoinEvent& event) {
    auto& player = event.self();
    auto& uuid   = player.getUuid();

    MusicList[uuid] = new task::MusicPlayer(&player);
}

// 玩家离开监听
void playerLeaveEventFunction(PlayerLeaveEvent& event) {
    auto& player = event.self();
    auto& uuid   = player.getUuid();

    delete MusicList[uuid];
    MusicList.erase(uuid);
}

// 命令回调
void commandCallback(
    DynamicCommand const&                                    command,
    CommandOrigin const&                                     origin,
    CommandOutput&                                           output,
    std::unordered_map<std::string, DynamicCommand::Result>& results
) {
    // 实体
    auto* entity = origin.getEntity();
    if (entity == nullptr || !entity->isType(ActorType::Player)) {
        output.error("Can't play music");
        return;
    }

    // 玩家
    auto* player = static_cast<Player*>(entity);

    // 标识
    auto& uuid = player->getUuid();

    // 功能
    std::string func = results.at("func").get<std::string>();

    // 播放器
    auto* music = MusicList[player->getUuid()];

    if (func == "play") {

        std::string path = results.at("path").get<std::string>();

        auto result = midi::parse(path);

        music->play(result.notes, result.times);

        output.success("Music is playing");

    } else if (func == "stop") {

        music->stop();

        output.success("Music stops playing");
    }
}

} // namespace function