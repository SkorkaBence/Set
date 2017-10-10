#ifndef H_SBL_SET
#define H_SBL_SET

#include "List/LinkedList.h"

typedef sbl::LinkedList<int, true, true> set_linkedlist_type;
typedef set_linkedlist_type::iterator set_linkedlist_iterator;

namespace sbl {

    class Set {
    private:
        set_linkedlist_type data;
    public:

        Set();

        bool isEmpty() const;
        bool insert(int value);
        bool remove(int value);
        bool find(int value);

    };

}

#endif // !H_SBL_SET
