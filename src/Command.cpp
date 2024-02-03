/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-02-02 16:36:23
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-04 04:29:53
 * @Description: 命令注册
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */

#include "Command.h"

#include "Functions.h"
#include "Static.h"

#include <ll/api/command/DynamicCommand.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>


namespace command {


// 装载所有命令
void install() {
    using ParamType = DynamicCommand::ParameterType;
    using Param     = DynamicCommand::ParameterData;

    // 注册表
    auto registry = ll::service::getCommandRegistry();

    // 实例
    auto command =
        DynamicCommand::createCommand(registry, COMMAND_NAME, COMMAND_DESCRIPTION, CommandPermissionLevel::Any);

    // 别名
    command->setAlias(COMMAND_ALIAS);

    // 枚举
    command->setEnum("play", {"play"});
    command->setEnum("stop", {"stop"});

    // 参数 CommandParameterOption::EnumAutocompleteExpansion -> 必选
    command->mandatory("path", ParamType::String, CommandParameterOption::EnumAutocompleteExpansion);

    command->mandatory("func", ParamType::Enum, "play", CommandParameterOption::EnumAutocompleteExpansion);
    command->mandatory("func", ParamType::Enum, "stop", CommandParameterOption::EnumAutocompleteExpansion);

    // 重载命令 -> 组合
    command->addOverload({"play", "path"});
    command->addOverload({"stop"});

    // 回调 处理功能
    command->setCallback(&function::commandCallback);

    // 装载命令 -> why move? -> this is unique_ptr
    DynamicCommand::setup(registry, std::move(command));
}

// 卸载所有命令
void remove() {
    auto registry = ll::service::getCommandRegistry();

    registry->unregisterCommand(COMMAND_NAME);
}

} // namespace command