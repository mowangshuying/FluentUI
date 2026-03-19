#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include <atomic>
#include <utility>

#include <qmsetup/qmsetup_global.h>

template <class T>
class QMSharedDataPointer;

class QMSharedData {
public:
    mutable std::atomic_int ref;

    inline QMSharedData() noexcept : ref(0){};
    inline QMSharedData(const QMSharedData &) noexcept : ref(0){};
    virtual ~QMSharedData() = default;

    // using the assignment operator would lead to corruption in the ref-counting
    QMSharedData &operator=(const QMSharedData &) = delete;

    // NOTICE: must define a function named `clone()` which returns a copy
};

template <class T>
class QMSharedDataPointer {
public:
    typedef T Type;
    typedef T *pointer;

    inline void detach() {
        if (d && d->ref.load() != 1)
            detach_helper();
    }
    inline T &operator*() {
        detach();
        return *d;
    }
    inline const T &operator*() const {
        return *d;
    }
    inline T *operator->() {
        detach();
        return d;
    }
    inline const T *operator->() const {
        return d;
    }
    inline operator T *() {
        detach();
        return d;
    }
    inline operator const T *() const {
        return d;
    }
    inline T *data() {
        detach();
        return d;
    }
    inline const T *data() const {
        return d;
    }
    inline const T *constData() const {
        return d;
    }

    // Compatible with std::unique_ptr
    inline T *get() {
        detach();
        return d;
    }
    inline const T *get() const {
        return d;
    }

    inline bool operator==(const QMSharedDataPointer<T> &other) const {
        return d == other.d;
    }
    inline bool operator!=(const QMSharedDataPointer<T> &other) const {
        return d != other.d;
    }

    inline QMSharedDataPointer() {
        d = nullptr;
    }
    inline ~QMSharedDataPointer() {
        if (d && d->ref.fetch_sub(1) == 1)
            delete d;
    }

    explicit QMSharedDataPointer(T *data) noexcept;
    inline QMSharedDataPointer(const QMSharedDataPointer<T> &o) : d(o.d) {
        if (d)
            d->ref.fetch_add(1);
    }
    inline QMSharedDataPointer<T> &operator=(const QMSharedDataPointer<T> &o) {
        if (o.d != d) {
            if (o.d)
                o.d->ref.fetch_add(1);
            T *old = d;
            d = o.d;
            if (old && old->ref.fetch_sub(1) == 1)
                delete old;
        }
        return *this;
    }
    inline QMSharedDataPointer &operator=(T *o) {
        if (o != d) {
            if (o)
                o->ref.fetch_add(1);
            T *old = d;
            d = o;
            if (old && old->ref.fetch_sub(1) == 1)
                delete old;
        }
        return *this;
    }
    QMSharedDataPointer(QMSharedDataPointer &&o) noexcept : d(o.d) {
        o.d = nullptr;
    }
    inline QMSharedDataPointer<T> &operator=(QMSharedDataPointer<T> &&other) noexcept {
        QMSharedDataPointer moved(std::move(other));
        swap(moved);
        return *this;
    }

    inline bool operator!() const {
        return !d;
    }

    inline void swap(QMSharedDataPointer &other) noexcept {
        std::swap(d, other.d);
    }

protected:
    T *clone();

private:
    void detach_helper();

    T *d;
};

template <class T>
inline bool operator==(std::nullptr_t p1, const QMSharedDataPointer<T> &p2) {
    (void) p1;
    return !p2;
}

template <class T>
inline bool operator==(const QMSharedDataPointer<T> &p1, std::nullptr_t p2) {
    (void) p2;
    return !p1;
}

template <class T>
inline QMSharedDataPointer<T>::QMSharedDataPointer(T *adata) noexcept : d(adata) {
    if (d)
        d->ref.fetch_add(1);
}

template <class T>
inline T *QMSharedDataPointer<T>::clone() {
    return d->clone();
}

template <class T>
inline void QMSharedDataPointer<T>::detach_helper() {
    T *x = clone();
    x->ref.fetch_add(1);
    if (d->ref.fetch_sub(1) == 1)
        delete d;
    d = x;
}

#endif // SHAREDDATA_H
