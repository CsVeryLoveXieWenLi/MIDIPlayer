/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-02-02 16:34:44
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-02 18:27:21
 * @Description: 功能的实现 头文件
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once


#include <ll/api/command/DynamicCommand.h>
#include <ll/api/event/player/PlayerJoinEvent.h>
#include <ll/api/event/player/PlayerLeaveEvent.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>



namespace function {

using namespace ll::event;

// 玩家加入监听
void playerJoinEventFunction(PlayerJoinEvent& event);

// 玩家离开监听
void playerLeaveEventFunction(PlayerLeaveEvent& event);

// 命令回调
void commandCallback(
    DynamicCommand const&                                    command,
    CommandOrigin const&                                     origin,
    CommandOutput&                                           output,
    std::unordered_map<std::string, DynamicCommand::Result>& results
);

} // namespace function