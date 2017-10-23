#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Set/Set.h"

#define CATCH_CONFIG_MAIN

#include "Catch/catch.hpp"

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
    set.insert(5);
    REQUIRE( set.find(5) );
    set.insert(12);
    REQUIRE( set.find(12) );
    set.remove(8);
    REQUIRE( ! set.find(8) );
}

TEST_CASE("Clear set", "[set]") {
    sbl::Set set;

    for (int i = 0; i < 1000; i++) {
        set.insert(i);
        REQUIRE( set.find(i) );
    }

    set.clear();

    for (int i = -500; i < 1500; i++) {
        REQUIRE( ! set.find(i) );
    }
}

TEST_CASE("& and |", "[set]") {
    sbl::Set set1;
    sbl::Set set2;

    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {
            set1.insert(i);
        }
        if (i % 3 == 0) {
            set2.insert(i);
        }
    }

    sbl::Set intersect = set1 & set2;
    sbl::Set diff = set1 | set2;

    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {
            REQUIRE( set1.find(i) );
        }
        if (i % 3 == 0) {
            REQUIRE( set2.find(i) );
        }

        if (i % 6 == 0) {
            REQUIRE( intersect.find(i) );
            REQUIRE( ! diff.find(i) );
        } else {
            REQUIRE( ! intersect.find(i) );
            if (i % 2 == 0 || i % 3 == 0) {
                REQUIRE( diff.find(i) );
            }
        }
    }
}

TEST_CASE("copy", "[set]") {
    sbl::Set set1;
    sbl::Set set2;

    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {
            set1.insert(i);
        }
        if (i % 3 == 0) {
            set2.insert(i);
        }
    }

    set2 = set1;

    for (int i = 0; i < 1000; i++) {
        if (i % 2 == 0) {
            REQUIRE( set1.find(i) );
            REQUIRE( set2.find(i) );
        } else {
            REQUIRE( ! set1.find(i) );
            REQUIRE( ! set2.find(i) );
        }
    }
}
