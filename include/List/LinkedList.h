#ifndef H_SBL_LINKEDLIST
#define H_SBL_LINKEDLIST

#include <iostream>

namespace sbl {

    template<typename T, bool ordered = false, bool unique = false>
    class LinkedList {
    private:
        class ListItem {
        public:
            T value;
            ListItem* next;
        };

        ListItem* head;

        ListItem* newItem(T val, ListItem* next) {
            ListItem* newitem = new ListItem();
            newitem->value = val;
            newitem->next = next;
            return newitem;
        }
        ListItem* newItem(T val) {
            return this->newItem(val, nullptr);
        }
    public:
        class iterator {
        private:
        public:
            ListItem* point;

            iterator& operator ++ (int a) {
                if (point != nullptr && point->next != nullptr) {
                    point = point->next;
                }
                return *this;
            }
            iterator& operator += (int num) {
                for (int i = 0; i < num; i++) {
                    (*this)++;
                }
                return *this;
            }
            bool isEnd() {
                return (point == nullptr || point->next == nullptr);
            }
            bool isValid() {
                return (point != nullptr);
            }
            const T& operator * () const {
                return point->value;
            }
        };

        LinkedList() {
            head = nullptr;
            if (!ordered) {
                if (unique) {
                    throw 0;
                }
            }
        }

        ~LinkedList() {
            ListItem* p = head;
            ListItem* c;
            while (p != nullptr) {
                c = p;
                p = p->next;
                delete c;
            }
        }

        void prepend(T val) {
            if (ordered) {
                throw 0;
            }
            head = this->newItem(val, head);
        }

        void pushback(T val) {
            if (ordered) {
                throw 0;
            }
            if (head == nullptr) {
                head = this->newItem(val, head);
            } else {
                ListItem* p = head->next;
                ListItem* c = head;
                while (p->next != nullptr) {
                    c = p;
                    p = p->next;
                }
                c->next = this->newItem(val);
            }
        }

        bool add(T val) {
            if (!ordered) {
                throw 0;
            }
            if (head == nullptr || head->value > val) {
                head = this->newItem(val, head);
                return true;
            } else {
                ListItem* p = head->next;
                ListItem* c = head;
                while (p != nullptr && p->value <= val) {
                    c = p;
                    p = p->next;
                }
                if (!unique || c->value != val) {
                    c->next = this->newItem(val, c->next);
                    return true;
                }
            }
            return false;
        }

        /*bool addIfNotExists(T val) {
            if (!ordered) {
                throw 0;
            }
            if (head == nullptr || head->value > val) {
                head = this->newItem(val, head);
                return true;
            } else {
                ListItem* p = head->next;
                ListItem* c = head;
                while (p != nullptr && p->value <= val) {
                    c = p;
                    p = p->next;
                }
                if (c->value != val) {
                    c->next = this->newItem(val, c->next);
                    return true;
                }
            }
            return false;
        }*/

        bool removeAll(T val) {
            bool wasRemoved = false;

            while (head != nullptr && head->value == val) {
                ListItem* p = head;
                head = head->next;
                delete p;
                wasRemoved = true;
            }

            if (head == nullptr) {
                return wasRemoved;
            }

            ListItem* p = head->next;
            ListItem* c = head;
            while (p != nullptr) {
                if (p->value == val) {
                    c->next = p->next;
                    ListItem* t = p;
                    p = p->next;
                    delete t;
                    wasRemoved = true;
                }
            }

            return wasRemoved;
        }

        bool find(T val) const {
            ListItem* p = head;
            while (p != nullptr && (!ordered || p->value <= val)) {
                if (p->value == val) {
                    return true;
                }
                p = p->next;
            }
            return false;
        }

        friend std::ostream& operator << (std::ostream& out, LinkedList list) {
            ListItem* p = list.head;
            while (p != nullptr) {
                out << p->value;
                p = p->next;
                if (p != nullptr) {
                    out << " ";
                }
            }
            return out;
        }

        iterator& getIterator() const {
            iterator* it = new iterator();
            it->point = head;
            return *it;
        }

        operator iterator () const {
            return this->getIterator();
        }

    };

}

#endif // !H_SBL_LINKEDLIST
