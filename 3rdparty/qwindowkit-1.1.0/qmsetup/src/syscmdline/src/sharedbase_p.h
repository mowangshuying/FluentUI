#ifndef SHAREDBASE_P_H
#define SHAREDBASE_P_H

#include <atomic>

namespace SysCmdLine {

    class SharedBasePrivate {
    public:
        SharedBasePrivate();
        virtual ~SharedBasePrivate();

        virtual SharedBasePrivate *clone() const = 0;

        // Declare basic copy constructor
        SharedBasePrivate(const SharedBasePrivate &) : ref(0) {
        }

        SharedBasePrivate &operator=(const SharedBasePrivate &) = delete;

        std::atomic_int ref;
    };

    inline void ref_ref(SharedBasePrivate *d) {
        if (d)
            d->ref.fetch_add(1);
    }

    inline void ref_deref(SharedBasePrivate *d) {
        if (d && d->ref.fetch_sub(1) == 1)
            delete d;
    }

    inline void ref_assign(SharedBasePrivate *&d, SharedBasePrivate *d2) {
        if (d2)
            d2->ref.fetch_add(1);
        if (d && d->ref.fetch_sub(1) == 1)
            delete d;
        d = d2;
    }

#define Q_D(T)                                                                                     \
  detach();                                                                                        \
  T##Private *const d = reinterpret_cast<T##Private *>(d_ptr)

#define Q_D2(T)                                                                                    \
    const T##Private *const d = reinterpret_cast<const T##Private *>(d_ptr)

}

#endif // SHAREDBASE_P_H
