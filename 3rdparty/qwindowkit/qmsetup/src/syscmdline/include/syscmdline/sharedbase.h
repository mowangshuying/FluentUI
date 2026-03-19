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

#ifndef SHAREDBASE_H
#define SHAREDBASE_H

#include <utility>

#include <syscmdline/global.h>
namespace SysCmdLine {

    class SharedBasePrivate;

    class SYSCMDLINE_EXPORT SharedBase {
        SYSCMDLINE_DECL_PRIVATE(SharedBase)
    public:
        virtual ~SharedBase();

        SharedBase(const SharedBase &other);
        inline SharedBase(SharedBase &&other) noexcept;
        SharedBase &operator=(const SharedBase &other);
        inline SharedBase &operator=(SharedBase &&other) noexcept;

    public:
        inline void swap(SharedBase &other) noexcept;
        bool isDetached() const;
        void detach();

    protected:
        SharedBase(SharedBasePrivate *d);
        SharedBasePrivate *d_ptr;
    };

    inline SharedBase::SharedBase(SharedBase &&other) noexcept : d_ptr(nullptr) {
        swap(other);
    }

    inline SharedBase &SharedBase::operator=(SharedBase &&other) noexcept {
        swap(other);
        return *this;
    }

    void SharedBase::swap(SharedBase &other) noexcept {
        std::swap(d_ptr, other.d_ptr);
    }

}

#endif // SHAREDBASE_H
