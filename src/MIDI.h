/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-02-02 17:23:39
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-02 18:02:08
 * @Description: 解析MIDI文件 头文件
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */
#pragma once


#include <deque>
#include <ll/api/base/StdInt.h>
#include <string>


namespace midi {

/**
 * 返回数据
 */
struct Result {
    Result(std::deque<std::deque<uint8>>& notes, std::deque<uint16>& times) {
        this->notes = notes;
        this->times = times;
    };

    std::deque<std::deque<uint8>> notes;
    std::deque<uint16>            times;
};

/**
 * 解析MIDI文件
 */
Result parse(std::string& path);

} // namespace midi