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

#ifndef GLOBAL_H
#define GLOBAL_H

// Export define
#ifdef _MSC_VER
#  define SYSCMDLINE_DECL_EXPORT __declspec(dllexport)
#  define SYSCMDLINE_DECL_IMPORT __declspec(dllimport)
#else
#  define SYSCMDLINE_DECL_EXPORT __attribute__((visibility("default")))
#  define SYSCMDLINE_DECL_IMPORT __attribute__((visibility("default")))
#endif

#ifdef SYSCMDLINE_STATIC
#  define SYSCMDLINE_EXPORT
#else
#  ifdef SYSCMDLINE_LIBRARY
#    define SYSCMDLINE_EXPORT SYSCMDLINE_DECL_EXPORT
#  else
#    define SYSCMDLINE_EXPORT SYSCMDLINE_DECL_IMPORT
#  endif
#endif

#ifdef _MSC_VER
#  define SYSCMDLINE_DECL_DEPRECATED __declspec(deprecated)
#else
#  define SYSCMDLINE_DECL_DEPRECATED __attribute__((__deprecated__))
#endif

// Utils
#define SYSCMDLINE_UNUSED(X) (void) X;

#define SYSCMDLINE_DECL_PRIVATE(X)                                                                 \
public:                                                                                            \
    const X##Private *d_func() const {                                                             \
        return reinterpret_cast<const X##Private *>(d_ptr);                                        \
    }

#if defined(__GNUC__) || defined(__clang__)
#  define SYSCMDLINE_PRINTF_FORMAT(fmtpos, attrpos)                                                \
      __attribute__((__format__(__printf__, fmtpos, attrpos)))
#else
#  define SYSCMDLINE_PRINTF_FORMAT(fmtpos, attrpos)
#endif

#endif // GLOBAL_H
