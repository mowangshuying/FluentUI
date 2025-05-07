#ifndef QMSETUP_GLOBAL_H
#define QMSETUP_GLOBAL_H

// Export define
#ifdef _MSC_VER
#  define QMSETUP_DECL_EXPORT __declspec(dllexport)
#  define QMSETUP_DECL_IMPORT __declspec(dllimport)
#else
#  define QMSETUP_DECL_EXPORT __attribute__((visibility("default")))
#  define QMSETUP_DECL_IMPORT __attribute__((visibility("default")))
#endif

// Qt style P-IMPL
#define QMSETUP_DECL_PRIVATE(Class)                                                              \
    inline Class##Private *d_func() {                                                              \
        return reinterpret_cast<Class##Private *>(d_ptr.get());                                    \
    }                                                                                              \
    inline const Class##Private *d_func() const {                                                  \
        return reinterpret_cast<const Class##Private *>(d_ptr.get());                              \
    }                                                                                              \
    friend class Class##Private;

#define QMSETUP_DECL_PUBLIC(Class)                                                               \
    inline Class *q_func() {                                                                       \
        return static_cast<Class *>(q_ptr);                                                        \
    }                                                                                              \
    inline const Class *q_func() const {                                                           \
        return static_cast<const Class *>(q_ptr);                                                  \
    }                                                                                              \
    friend class Class;

#define QM_D(Class) Class##Private *const d = d_func()
#define QM_Q(Class) Class *const q = q_func()

// Some classes do not permit copies to be made of an object.
#define QMSETUP_DISABLE_COPY(Class)                                                              \
    Class(const Class &) = delete;                                                                 \
    Class &operator=(const Class &) = delete;

#define QMSETUP_DISABLE_MOVE(Class)                                                              \
    Class(Class &&) = delete;                                                                      \
    Class &operator=(Class &&) = delete;

#define QMSETUP_DISABLE_COPY_MOVE(Class)                                                         \
    QMSETUP_DISABLE_COPY(Class)                                                                  \
    QMSETUP_DISABLE_MOVE(Class)

// Logging functions
#ifndef QMSETUP_TRACE
#  ifdef QMSETUP_YES_TRACE
#    define QMSETUP_TRACE_(fmt, ...)                                                             \
        printf("%s:%d:trace: " fmt "%s\n", __FILE__, __LINE__, __VA_ARGS__)
#    define QMSETUP_TRACE(...) QMSETUP_TRACE_(__VA_ARGS__, "")
#  else
#    define QMSETUP_TRACE(...)
#  endif
#endif

#ifndef QMSETUP_DEBUG
#  ifndef QMSETUP_NO_DEBUG
#    define QMSETUP_DEBUG_(fmt, ...)                                                             \
        printf("%s:%d:debug: " fmt "%s\n", __FILE__, __LINE__, __VA_ARGS__)
#    define QMSETUP_DEBUG(...) QMSETUP_DEBUG_(__VA_ARGS__, "")
#  else
#    define QMSETUP_DEBUG(...)
#  endif
#endif

#ifndef QMSETUP_WARNING
#  ifndef QMSETUP_NO_WARNING
#    define QMSETUP_WARNING_(fmt, ...)                                                           \
        printf("%s:%d:warning: " fmt "%s\n", __FILE__, __LINE__, __VA_ARGS__)
#    define QMSETUP_WARNING(...) QMSETUP_WARNING_(__VA_ARGS__, "")
#  else
#    define QMSETUP_WARNING(...)
#  endif
#endif

#ifndef QMSETUP_FATAL
#  ifndef QMSETUP_NO_FATAL
#    define QMSETUP_FATAL_(fmt, ...)                                                             \
        (fprintf(stderr, "%s:%d:fatal: " fmt "%s\n", __FILE__, __LINE__, __VA_ARGS__), std::abort())
#    define QMSETUP_FATAL(...) QMSETUP_FATAL_(__VA_ARGS__, "")
#  else
#    define QMSETUP_FATAL(...)
#  endif
#endif

// Utils
#define QM_UNUSED(X) (void) X;

#endif // QMSETUP_GLOBAL_H
