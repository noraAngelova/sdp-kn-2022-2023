#define TEST_BOTH LinkedList<int>, DoubleLinkedList<int>

TEST_CASE_TEMPLATE("Insert consecutively elements at the end of the list", TestList, TEST_BOTH) {
    TestList l;
    for (int i = 1; i <= 10; i++)
        l += i;
    int i = 1;
    for (int x : l)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Insert after every element in the list", TestList, TEST_BOTH) {
    TestList l;
    // Вмъкват се нечетните числа от 1 до 10
    for (int i = 1; i <= 9; i += 2)
        l += i;
    // Вмъкват се стойности след всяко число
    for (typename TestList::I it = l.begin(); it; it += 2)
        l.insertAfter(it, *it + 1);

    // Очакван резултат - последователните числа от 1 до 10
    int i = 1;
    for (int x : l)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Delete every even element in a list", TestList, TEST_BOTH) {
    TestList l;
    // Добавят се всички числа от 1 до 10
    for (int i = 1; i <= 10; i++)
        l += i;
    // Изтриват се всички четни числа
    for (typename TestList::I it = l.begin(); it; ++it) {
        int x;
        CHECK(l.deleteAfter(it, x));
        CHECK_EQ(x, *it + 1);
    }
    // Проверява се дали са останали само нечетните числа
    int i = 1;
    for (int x : l) {
        CHECK_EQ(x, i);
        i += 2;
    }
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Delete last element works correctly", TestList, TEST_BOTH) {
    TestList l;
    // Добавят се всички числа от 1 до 10
    for (int i = 1; i <= 10; i++)
        l += i;
    typename TestList::I it = l.begin();
    it += 8;
    // Итераторът е върху предпоследния елемент
    int x;
    CHECK(l.deleteAfter(it, x));
    CHECK_EQ(x, 10);
    l += 11;
    // Последният елемент наистина ли е 11?
    it = l.begin();
    REQUIRE(it);
    CHECK_EQ(*(it += 9), 11);
}

TEST_CASE_TEMPLATE("Insert consecutively elements at the beginning of the list", TestList, TEST_BOTH) {
    TestList l;
    // Добавят се числата от 1 до 10
    for (int i = 1; i <= 10; i++)
        l.insertFirst(i);
    // Проверка дали back е коректен
    l.insertLast(0);
    int i = 10;
    for (int x : l)
        CHECK_EQ(x, i--);
    CHECK_EQ(i, -1);
}

TEST_CASE_TEMPLATE("Insert elements before every second element in the list", TestList, TEST_BOTH) {
    TestList l;
    // Добавят се четните числа от 2 до 10
    for (int i = 2; i <= 10; i += 2)
        l += i;
    // Вмъква се елемент преди всеки съществуващ елемент
    for (typename TestList::I it = l.begin(); it; ++it)
        l.insertBefore(it, *it - 1);
    // Очакван резултат: последователните числа от 1 до 10
    int i = 1;
    for (int x : l)
        CHECK_EQ(x, i++);
    CHECK_EQ(i, 11);
}

TEST_CASE_TEMPLATE("Delete every second element in the list", TestList, TEST_BOTH) {
    TestList l;
    // Добавят се числата от 1 до 10
    for (int i = 1; i <= 10; i++)
        l += i;
    int i = 1;
    for (typename TestList::I it = l.begin(); it; ++it, i += 2) {
        int x;
        CHECK(l.deleteAt(it++, x));
        CHECK_EQ(x, i);
    }
    i = 2;
    for (int x : l) {
        CHECK_EQ(x, i);
        i += 2;
    }
    CHECK_EQ(i, 12);
}


TEST_CASE_TEMPLATE("Delete before every second element of the list", TestList, TEST_BOTH) {
    TestList l;
    // Добавят се числата от 1 до 10
    for (int i = 1; i <= 10; i++)
        l += i;
    int i = 1;
    // Изтриваме елементите преди всички четни числа
    for (typename TestList::I it = l.begin(); it; ++it, i += 2) {
        ++it;
        int x;
        CHECK(l.deleteBefore(it, x));
        CHECK_EQ(i, x);
    }
    // остават само четните
    i = 2;
    for (int x : l) {
        CHECK_EQ(i, x);
        i += 2;
    }
    CHECK_EQ(i, 12);
}

TEST_CASE_TEMPLATE("Copy initialization of lists avoids sharing", TestList, TEST_BOTH) {
    TestList l1;
    // Добавят се числата от 1 до 10
    for (int i = 1; i <= 10; i++)
        l1 += i;

    TestList l2 = l1;
    l1 += 11;
    l1.insertFirst(0);

    for (int& x : l2)
        x *= 2;
    l2 += 22;
    l2.insertFirst(0);

    // в l1 са числата от 0 до 11
    int i = 0;
    for (int x : l1)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 12);

    // в l2 са четните числа от 0 до 22
    i = 0;
    for (int x : l2) {
        CHECK_EQ(i, x);
        i += 2;
    }
    CHECK_EQ(i, 24);
}

TEST_CASE_TEMPLATE("Assignment of lists avoids sharing", TestList, TEST_BOTH) {
    TestList l1, l2;
    // Добавят се числата от 1 до 10
    for (int i = 1; i <= 10; i++)
        l1 += i;

    // Добавят се числата от 11 до 20
    for (int i = 11; i <= 20; i++)
        l2 += i;

    l2 = l1;
    l1 += 11;
    l1.insertFirst(0);

    for (int& x : l2)
        x *= 2;
    l2 += 22;
    l2.insertFirst(0);

    // в l1 са числата от 0 до 11
    int i = 0;
    for (int x : l1)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 12);

    // в l2 са четните числа от 0 до 22
    i = 0;
    for (int x : l2) {
        CHECK_EQ(i, x);
        i += 2;
    }
    CHECK_EQ(i, 24);
}

TEST_CASE_TEMPLATE("Appending two lists", TestList, TEST_BOTH) {
    TestList l1, l2;
    // Добавят се числата от 1 до 10
    for (int i = 1; i <= 10; i++)
        l1 += i;

    // Добавят се числата от 11 до 20
    for (int i = 11; i <= 20; i++)
        l2 += i;

    l1.append(l2);

    // Очакван резултат: числата от 1 до 20
    int i = 1;
    for (int x : l1)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 21);
}

TEST_CASE_TEMPLATE("Append a second list by stealing its elements", TestList, TEST_BOTH) {
    TestList l1, l2;
    // Добавят се числата от 1 до 10
    for (int i = 1; i <= 10; i++)
        l1 += i;

    // Добавят се числата от 11 до 20
    for (int i = 11; i <= 20; i++)
        l2 += i;

    l1.appendAssign(l2);
    CHECK(l2.empty());

    // Очакван резултат: числата от 1 до 20
    int i = 1;
    for (int x : l1)
        CHECK_EQ(i++, x);
    CHECK_EQ(i, 21);
}
