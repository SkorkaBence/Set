#include "Set/Set.h"

#define DEBUG_ENABLED

#ifdef DEBUG_ENABLED
#define debug(x) std:: cout << "DEBUG: " << x << std::endl
#else
#define debug(x) // Debug here
#endif

namespace sbl {

    Set::Set() {
        first = nullptr;
    }

    Set::Set(const Set& cpy) {
        CopyFrom(cpy);
    }

    Set::~Set() {
        clear();
    }

    void Set::CopyFrom(const Set& cpy) {
        clear();
        SetItem* p = cpy.first;
        while (p != nullptr) {
            insert(p->value);
            p = p->next;
        }
    }

    void Set::operator = (Set cpy) {
        CopyFrom(cpy);
    }

    void Set::insert(int a) {
        if (first == nullptr || first->value > a) {
            first = this->newItem(a, first);
        } else {
            SetItem* p = first->next;
            SetItem* c = first;
            while (p != nullptr && p->value <= a) {
                c = p;
                p = p->next;
            }
            if (c->value != a) {
                c->next = newItem(a, c->next);
            }
        }
    }

    Set::SetItem* Set::newItem(int val, Set::SetItem* next) {
        SetItem* newitem = new SetItem();
        newitem->value = val;
        newitem->next = next;
        return newitem;
    }

    Set::SetItem* Set::newItem(int val) {
        return this->newItem(val, nullptr);
    }

    bool Set::find(int a) {
        SetItem* p = first;
        while (p != nullptr && p->value <= a) {
            if (p->value == a) {
                return true;
            }
            p = p->next;
        }
        return false;
    }

    void Set::remove(int val) {
        while (first != nullptr && first->value == val) {
            SetItem* p = first;
            first = first->next;
            delete p;
        }

        if (first != nullptr) {
            SetItem* p = first->next;
            SetItem* c = first;
            while (p != nullptr && p->value <= val) {
                if (p->value == val) {
                    c->next = p->next;
                    SetItem* t = p;
                    p = p->next;
                    delete t;
                } else {
                    c = p;
                    p = p->next;
                }
            }
        }
    }

    bool Set::isEmpty() {
        return first == nullptr;
    }

    int Set::size() {
        int s = 0;

        Set::SetItem* p = first;
        while (p != nullptr) {
            s++;
            p = p->next;
        }

        return s;
    }

    void Set::clear() {
        SetItem* p = first;
        while (p != nullptr) {
            SetItem* c = p;
            p = p->next;
            delete c;
        }
        first = nullptr;
    }

    std::ostream& operator << (std::ostream& out, Set& dt) {
        out << "Set";
        int s = 0;
        Set::SetItem* p = dt.first;
        while (p != nullptr) {
            s++;
            out << " " << p->value;
            p = p->next;
        }
        std::cout << " {" << s << "}";
        return out;
    }

    void Set::saveData(std::ostream out) {
        Set::SetItem* p = first;
        while (p != nullptr) {
            out << " " << p->value;
            p = p->next;
        }
    }

    void Set::loadData(std::istream in) {
        clear();

        int a;
        while (in >> a) {
            insert(a);
        }
    }

    Set operator & (const Set& set1, const Set& set2) {
        Set::SetItem* p1 = set1.first;
        Set::SetItem* p2 = set2.first;

        Set newset;
        Set::SetItem* np = nullptr;

        while (p1 != nullptr && p2 != nullptr) {
            if (p1->value < p2->value) {
                p1 = p1->next;
            } else if (p1->value == p2->value) {
                if (np == nullptr) {
                    newset.first = newset.newItem(p1->value);
                    np = newset.first;
                } else {
                    np->next = newset.newItem(p1->value);
                    np = np->next;
                }
                p1 = p1->next;
                p2 = p2->next;
            } else if (p1->value > p2->value) {
                p2 = p2->next;
            }
        }

        return newset;
    }

    Set operator | (const Set& set1, const Set& set2) {
        Set::SetItem* p1 = set1.first;
        Set::SetItem* p2 = set2.first;

        Set newset;
        Set::SetItem* np = nullptr;

        while (p1 != nullptr || p2 != nullptr) {
            if ((p2 == nullptr) || (p1 != nullptr && p1->value < p2->value)) {
                if (np == nullptr) {
                    np = newset.newItem(p1->value);
                    newset.first = np;
                } else {
                    np->next = newset.newItem(p1->value);
                    np = np->next;
                }
                p1 = p1->next;
            } else if (p1 != nullptr && p2 != nullptr && p1->value == p2->value) {
                p1 = p1->next;
                p2 = p2->next;
            } else if ((p1 == nullptr) || (p2 != nullptr && p1->value > p2->value)) {
                if (np == nullptr) {
                    np = newset.newItem(p2->value);
                    newset.first = np;
                } else {
                    np->next = newset.newItem(p2->value);
                    np = np->next;
                }
                p2 = p2->next;
            }
        }

        return newset;
    }

}
