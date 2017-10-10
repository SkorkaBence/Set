#include "Set/Set.h"

namespace sbl {

    Set::Set() {

    }

    bool Set::isEmpty() const {
        set_linkedlist_iterator it = data;
        return !it.isValid();
    }

    bool Set::insert(int value) {
        return data.add(value);
    }

    bool Set::remove(int value) {
        return data.removeAll(value);
    }

    bool Set::find(int value) {
        return data.find(value);
    }

}
