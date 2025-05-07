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

#ifndef VALUE_H
#define VALUE_H

#include <string>
#include <vector>
#include <cstdint>

#include <syscmdline/global.h>

namespace SysCmdLine {

    class SYSCMDLINE_EXPORT Value {
    public:
        enum Type {
            Null,
            Bool,
            Int,
            Int64,
            Double,
            String,
        };

        Value(Type type = Null);
        inline Value(bool b);
        inline Value(int i);
        inline Value(int64_t l);
        inline Value(double d);
        inline Value(const std::string &s);
        inline Value(const char *ch, int size = -1);
        ~Value();

        Value(const Value &other);
        Value(Value &&other) noexcept;
        Value &operator=(const Value &other);
        Value &operator=(Value &&other) noexcept;

        inline Type type() const;
        bool isEmpty() const;

        bool toBool() const;
        int toInt() const;
        int64_t toInt64() const;
        double toDouble() const;
        std::string toString() const;

        bool operator==(const Value &other) const;
        bool operator!=(const Value &other) const;

        static Value fromString(const std::string &s, Type type);
        static std::vector<std::string> toStringList(const std::vector<Value> &values);
        static const char *typeName(Type type);

    protected:
        union {
            bool b;
            int i;
            int64_t l;
            double d;
            std::string *s;
        } data;
        Type _type;
    };

    inline Value::Value(bool b) : _type(Bool) {
        data.b = b;
    }

    inline Value::Value(int i) : _type(Int) {
        data.i = i;
    }

    inline Value::Value(int64_t l) : _type(Int64) {
        data.l = l;
    }

    inline Value::Value(double d) : _type(Double) {
        data.d = d;
    }

    inline Value::Value(const std::string &s) : _type(String) {
        data.s = new std::string(s);
    }

    inline Value::Value(const char *ch, int size) : _type(String) {
        data.s = size >= 0 ? new std::string(ch, size) : new std::string(ch);
    }

    inline Value::Type Value::type() const {
        return _type;
    }

}

#endif // VALUE_H
