/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-01-31 22:36:37
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-02 16:07:48
 * @Description: 插件入口
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#include "Init.h"

#include "Listener.h"

#include <ll/api/plugin/NativePlugin.h>
#include <memory>


namespace Init {

Init::Init() = default;

Init& Init::getInstance() {
    static Init instance;
    return instance;
}

ll::plugin::NativePlugin& Init::getSelf() const { return *mSelf; }

bool Init::load(ll::plugin::NativePlugin& self) {
    mSelf = std::addressof(self);
    getSelf().getLogger().info("loading...");

    // Code for loading the plugin goes here.

    return true;
}

bool Init::enable() {
    getSelf().getLogger().info("enabling...");

    // 装载所有监听
    listener::install();

    return true;
}

bool Init::disable() {
    getSelf().getLogger().info("disabling...");

    // 移除所有监听
    listener::remove();

    return true;
}

extern "C" {
_declspec(dllexport) bool ll_plugin_load(ll::plugin::NativePlugin& self) { return Init::getInstance().load(self); }

_declspec(dllexport) bool ll_plugin_enable(ll::plugin::NativePlugin&) { return Init::getInstance().enable(); }

_declspec(dllexport) bool ll_plugin_disable(ll::plugin::NativePlugin&) { return Init::getInstance().disable(); }

/// @warning Unloading the plugin may cause a crash if the plugin has not released all of its
/// resources. If you are unsure, keep this function commented out.
// _declspec(dllexport) bool ll_plugin_unload(ll::plugin::NativePlugin&) {
//     return Init::getInstance().unload();
// }
}

} // namespace rename_this
