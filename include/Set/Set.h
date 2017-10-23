#ifndef H_SBL_SET
#define H_SBL_SET

#include <iostream>

namespace sbl {

    class Set {
    private:
        class SetItem {
        public:
            SetItem* next = nullptr;
            int value;
        };

        SetItem* first = nullptr;

        SetItem* newItem(int val, SetItem* next);
        SetItem* newItem(int val);

        void CopyFrom(const Set& cpy);
    public:
        Set();
        Set(const Set& cpy);
        ~Set();
        void insert(int a);
        bool find(int a);
        void remove(int a);
        bool isEmpty();
        void clear();
        int size();

        void operator = (Set cpy);

        friend std::ostream& operator << (std::ostream& out, Set& dt);

        void saveData(std::ostream out);
        void loadData(std::istream in);

        friend Set operator & (const Set& set1, const Set& set2);
        friend Set operator | (const Set& set1, const Set& set2);
    };

}

#endif // !H_SBL_SET
