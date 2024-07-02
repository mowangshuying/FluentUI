/****************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2023 SineStriker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ****************************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include <syscmdline/global.h>

namespace SysCmdLine {

    SYSCMDLINE_EXPORT std::string wideToUtf8(const std::wstring &s);
    SYSCMDLINE_EXPORT std::wstring utf8ToWide(const std::string &s);

    SYSCMDLINE_EXPORT std::string appPath();
    SYSCMDLINE_EXPORT std::string appDirectory();
    SYSCMDLINE_EXPORT std::string appFileName();
    SYSCMDLINE_EXPORT std::string appName();
    SYSCMDLINE_EXPORT std::vector<std::string> commandLineArguments();

    enum MessageType {
        MT_Debug,
        MT_Information,
        MT_Healthy,
        MT_Warning,
        MT_Critical,
    };
    SYSCMDLINE_EXPORT int u8debug(MessageType messageType, bool highlight, const char *fmt, ...);
    SYSCMDLINE_EXPORT int u8printf(const char *fmt, ...);

}

#endif // SYSTEM_H
