#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "List/LinkedList.h"
#include "Set/Set.h"

#define CATCH_CONFIG_MAIN

#include "Catch/catch.hpp"

TEST_CASE("Add in order", "[list]") {
    srand(time(NULL));

    sbl::LinkedList<int, true, false> list;
    for (int i = 0; i < 10000; i++) {
        int a = rand() % 100 + 1;
        list.add(a);
    }

    sbl::LinkedList<int, true, false>::iterator it = list;
    int last = *it;
    for (it++; !it.isEnd(); it++) {
        REQUIRE( last <= *it );
        last = *it;
    }
}

TEST_CASE("Add in order (unique)", "[list]") {
    srand(time(NULL));

    sbl::LinkedList<int, true, true> list;
    for (int i = 0; i < 10000; i++) {
        int a = rand() % 100 + 1;
        list.add(a);
    }

    sbl::LinkedList<int, true, true>::iterator it = list;
    int last = *it;
    for (it++; !it.isEnd(); it++) {
        REQUIRE( last < *it );
        last = *it;
    }
}

TEST_CASE("Set empty", "[set]") {
    sbl::Set set;
    REQUIRE( set.isEmpty() );
    set.insert(5);
    REQUIRE( ! set.isEmpty() );
    set.remove(5);
    REQUIRE( set.isEmpty() );
}

TEST_CASE("Set find", "[set]") {
    sbl::Set set;
    REQUIRE( ! set.find(5) );
    set.insert(5);
    REQUIRE( set.find(5) );
    set.insert(8);
    REQUIRE( set.find(5) );
    set.remove(5);
    REQUIRE( ! set.find(5) );
}
