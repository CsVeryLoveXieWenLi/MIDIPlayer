/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-01-31 22:36:37
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-01-31 22:42:35
 * @Description: 插件入口 头文件
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once


#include <ll/api/plugin/NativePlugin.h>


namespace Init {

class Init {
    Init();

public:
    Init(Init&&)                 = delete;
    Init(const Init&)            = delete;
    Init& operator=(Init&&)      = delete;
    Init& operator=(const Init&) = delete;

    static Init& getInstance();

    [[nodiscard]] ll::plugin::NativePlugin& getSelf() const;

    /// @return True if the plugin is loaded successfully.
    bool load(ll::plugin::NativePlugin&);

    /// @return True if the plugin is enabled successfully.
    bool enable();

    /// @return True if the plugin is disabled successfully.
    bool disable();

private:
    ll::plugin::NativePlugin* mSelf{};
};

} // namespace Init
