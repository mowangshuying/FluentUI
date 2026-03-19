#include "sharedbase.h"
#include "sharedbase_p.h"

namespace SysCmdLine {

    // static int g_cnt;

    SharedBasePrivate::SharedBasePrivate() : ref(1) {
        // printf("construct %d\n", ++g_cnt);
    }

    SharedBasePrivate::~SharedBasePrivate() {
        // printf("destruct %d\n", --g_cnt);
    }

    SharedBase::~SharedBase() {
        ref_deref(d_ptr);
    }

    SharedBase::SharedBase(const SharedBase &other) : d_ptr(other.d_ptr) {
        ref_ref(d_ptr);
    }

    SharedBase &SharedBase::operator=(const SharedBase &other) {
        if (this == &other) {
            return *this;
        }
        ref_assign(d_ptr, other.d_ptr);
        return *this;
    }

    bool SharedBase::isDetached() const {
        Q_D2(SharedBase);
        return d && d->ref.load() == 1;
    }

    void SharedBase::detach() {
        auto &d = d_ptr;
        if (d->ref.load() != 1) {
            auto x = d->clone();
            if (d->ref.fetch_sub(1) == 1) // atomicity
                delete d;
            d = x;
        }
    }

    SharedBase::SharedBase(SharedBasePrivate *d) : d_ptr(d) {
    }

}