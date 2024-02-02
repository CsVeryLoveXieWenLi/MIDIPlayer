/**
 * @Author: CsVeryLoveXieWenLi
 * @Date: 2024-02-02 17:23:28
 * @LastEditors: CsVeryLoveXieWenLi
 * @LastEditTime: 2024-02-02 18:09:49
 * @Description: 解析MIDI文件
 * @QQ: 1172236399
 * @Sign: 有些故事，总是美妙又缥缈，郁郁不得终。
 * @Copyright (c) 2024 by CsVeryLoveXieWenLi, All Rights Reserved.
 */

#include "MIDI.h"

#include "Lib/MIDI/MidiEvent.h"
#include "Lib/MIDI/MidiFile.h"

#include <deque>
#include <ll/api/base/StdInt.h>
#include <string>


namespace midi {

/**
 * 解析MIDI文件
 */
Result parse(std::string& path) {
    using namespace smf;

    // 初始化
    std::deque<std::deque<uint8>> notes;
    std::deque<uint64>            times;

    Result   result(notes, times);
    MidiFile file;

    // 读取文件
    file.read(path);

    if (!file.status()) {
        return result;
    }

    // 合并音轨 -> 计算真实时间(s)
    file.joinTracks();
    file.doTimeAnalysis();

    // 计算
    MidiEvent* event;
    MidiEvent* old;

    std::deque<MidiEvent*> list;

    uint8  note;
    uint64 time;

    uint64 diff;

    MidiEventList* tracks = &file[0];
    int            length = tracks->size();

    for (int index = 0; index < length; index++) {
        event = &(*tracks)[index];

        // 只记录音符按下
        if (!event->isNoteOn()) continue;

        list.push_back(event);
    }

    length = static_cast<int>(list.size());

    for (int index = 0; index < length; index++) {
        event = list[index];

        // 不为0 记录前面的
        if (index > 0) {
            old = list[index - 1];
        }

        // 事件0 音高1 力度2
        note = (uint8)(*event)[1];

        // 绝对时间 ms
        time = (uint64)round(event->seconds * 1000);

        // 计算时间差
        if (index > 0) {
            diff = time - (uint64)round(old->seconds * 1000);
        } else {
            diff = time;
        }

        // 时间差非0 不同时演奏 新建集合
        if (diff > 0) {
            std::deque<uint8> notes;

            // 音符
            notes.push_back(note);
            result.notes.push_back(notes);

            // 时间
            result.times.push_back(diff);
        } else {
            // 音符添加到最后一个
            result.notes.back().push_back(note);
        }
    }

    return result;
}

} // namespace midi