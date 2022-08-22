// Template Library for C++
//
// Copyright (c) 2020 - present, Hawtian Wang
// All rights reserved.
//
// For the license information refer to version.h.

#include <iostream>
#include <queue>

#include "catch2/catch_all.hpp"
#include "ht/container/fib_heap.hpp"

using ht::FibonacciHeap;

TEST_CASE("simple push", "[fib-heap][container]") {
  FibonacciHeap<int, int> heap;
  std::priority_queue<int, std::vector<int>, std::greater<>> queue;

  heap.insert(135, 1);
  queue.push(135);
  heap.insert(3976, 1);
  queue.push(3976);
  heap.insert(1623, 1);
  queue.push(1623);
  heap.insert(5402, 1);
  queue.push(5402);
  heap.insert(2244, 1);
  queue.push(2244);
  heap.insert(3245, 1);
  queue.push(3245);
  heap.insert(5822, 1);
  queue.push(5822);
  heap.insert(9734, 1);
  queue.push(9734);
  heap.insert(8282, 1);
  queue.push(8282);
  heap.insert(9358, 1);
  queue.push(9358);
}

TEST_CASE("same priority queue", "[fib-heap][container]") {
  FibonacciHeap<int, int> heap;
  std::priority_queue<int, std::vector<int>, std::greater<>> queue;

  heap.insert(479, 1);
  queue.push(479);
  heap.insert(4518, 1);
  queue.push(4518);

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(8539, 1);
  queue.push(8539);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1223, 1);
  queue.push(1223);
  heap.insert(7243, 1);
  queue.push(7243);
  heap.insert(718, 1);
  queue.push(718);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(6418, 1);
  queue.push(6418);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9652, 1);
  queue.push(9652);
  heap.insert(4487, 1);
  queue.push(4487);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(3625, 1);
  queue.push(3625);
  heap.insert(1502, 1);
  queue.push(1502);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }
}

TEST_CASE("same priority queue2", "[fib-heap][container]") {
  FibonacciHeap<int, int> heap;
  std::priority_queue<int, std::vector<int>, std::greater<>> queue;

  heap.insert(9686, 1);
  queue.push(9686);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(2852, 1);
  queue.push(2852);
  heap.insert(8240, 1);
  queue.push(8240);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(6982, 1);
  queue.push(6982);
  heap.insert(7403, 1);
  queue.push(7403);
  heap.insert(3393, 1);
  queue.push(3393);
  heap.insert(4319, 1);
  queue.push(4319);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1113, 1);
  queue.push(1113);
  heap.insert(2090, 1);
  queue.push(2090);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(4526, 1);
  queue.push(4526);
  heap.insert(9514, 1);
  queue.push(9514);
  heap.insert(2707, 1);
  queue.push(2707);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(621, 1);
  queue.push(621);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(6053, 1);
  queue.push(6053);
  heap.insert(6336, 1);
  queue.push(6336);
  heap.insert(9841, 1);
  queue.push(9841);
  heap.insert(4946, 1);
  queue.push(4946);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(4964, 1);
  queue.push(4964);
  heap.insert(5595, 1);
  queue.push(5595);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(2678, 1);
  queue.push(2678);
  heap.insert(7325, 1);
  queue.push(7325);
  heap.insert(1748, 1);
  queue.push(1748);
  heap.insert(508, 1);
  queue.push(508);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9193, 1);
  queue.push(9193);
  heap.insert(7884, 1);
  queue.push(7884);
  heap.insert(3351, 1);
  queue.push(3351);
  heap.insert(2814, 1);
  queue.push(2814);
  heap.insert(4796, 1);
  queue.push(4796);
  heap.insert(5326, 1);
  queue.push(5326);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(8357, 1);
  queue.push(8357);
  heap.insert(3880, 1);
  queue.push(3880);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(8586, 1);
  queue.push(8586);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }
}

TEST_CASE("same priority queue3", "[fib-heap][container]") {
  FibonacciHeap<int, int> heap;
  std::priority_queue<int, std::vector<int>, std::greater<>> queue;

  heap.insert(6070, 1);
  queue.push(6070);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5076, 1);
  queue.push(5076);
  heap.insert(9204, 1);
  queue.push(9204);
  heap.insert(1617, 1);
  queue.push(1617);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5276, 1);
  queue.push(5276);
  heap.insert(2661, 1);
  queue.push(2661);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5519, 1);
  queue.push(5519);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5741, 1);
  queue.push(5741);
  heap.insert(649, 1);
  queue.push(649);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(3367, 1);
  queue.push(3367);
  heap.insert(2727, 1);
  queue.push(2727);
  heap.insert(7902, 1);
  queue.push(7902);
  heap.insert(2415, 1);
  queue.push(2415);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(7490, 1);
  queue.push(7490);
  heap.insert(4107, 1);
  queue.push(4107);
  heap.insert(9777, 1);
  queue.push(9777);
  heap.insert(2606, 1);
  queue.push(2606);
  heap.insert(6305, 1);
  queue.push(6305);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(8291, 1);
  queue.push(8291);
  heap.insert(4786, 1);
  queue.push(4786);
  heap.insert(7258, 1);
  queue.push(7258);
  heap.insert(9894, 1);
  queue.push(9894);
  heap.insert(5901, 1);
  queue.push(5901);
  heap.insert(3479, 1);
  queue.push(3479);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1775, 1);
  queue.push(1775);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(7559, 1);
  queue.push(7559);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1434, 1);
  queue.push(1434);
  heap.insert(2011, 1);
  queue.push(2011);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(3005, 1);
  queue.push(3005);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(2675, 1);
  queue.push(2675);
  heap.insert(3806, 1);
  queue.push(3806);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1001, 1);
  queue.push(1001);
  heap.insert(2318, 1);
  queue.push(2318);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9079, 1);
  queue.push(9079);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(360, 1);
  queue.push(360);
  heap.insert(2474, 1);
  queue.push(2474);
  heap.insert(672, 1);
  queue.push(672);
  heap.insert(4757, 1);
  queue.push(4757);
  heap.insert(7487, 1);
  queue.push(7487);
  heap.insert(4147, 1);
  queue.push(4147);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(3005, 1);
  queue.push(3005);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(299, 1);
  queue.push(299);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(8712, 1);
  queue.push(8712);
  heap.insert(2160, 1);
  queue.push(2160);
  heap.insert(8782, 1);
  queue.push(8782);
  heap.insert(2574, 1);
  queue.push(2574);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9702, 1);
  queue.push(9702);
  heap.insert(2754, 1);
  queue.push(2754);
  heap.insert(5068, 1);
  queue.push(5068);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9225, 1);
  queue.push(9225);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5350, 1);
  queue.push(5350);
  heap.insert(9201, 1);
  queue.push(9201);
  heap.insert(7060, 1);
  queue.push(7060);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9807, 1);
  queue.push(9807);
  heap.insert(3227, 1);
  queue.push(3227);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1022, 1);
  queue.push(1022);
  heap.insert(4953, 1);
  queue.push(4953);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(7400, 1);
  queue.push(7400);
  heap.insert(5790, 1);
  queue.push(5790);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(2952, 1);
  queue.push(2952);
  heap.insert(8752, 1);
  queue.push(8752);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(2702, 1);
  queue.push(2702);
  heap.insert(7342, 1);
  queue.push(7342);
  heap.insert(9589, 1);
  queue.push(9589);
  heap.insert(8543, 1);
  queue.push(8543);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(4226, 1);
  queue.push(4226);
  heap.insert(167, 1);
  queue.push(167);
  heap.insert(2533, 1);
  queue.push(2533);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(994, 1);
  queue.push(994);
  heap.insert(8913, 1);
  queue.push(8913);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9970, 1);
  queue.push(9970);
  heap.insert(8734, 1);
  queue.push(8734);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(8468, 1);
  queue.push(8468);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(143, 1);
  queue.push(143);
  heap.insert(9729, 1);
  queue.push(9729);
  heap.insert(9882, 1);
  queue.push(9882);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9075, 1);
  queue.push(9075);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1018, 1);
  queue.push(1018);
  heap.insert(3712, 1);
  queue.push(3712);
  heap.insert(3054, 1);
  queue.push(3054);
  heap.insert(3756, 1);
  queue.push(3756);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(4452, 1);
  queue.push(4452);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(7586, 1);
  queue.push(7586);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9778, 1);
  queue.push(9778);
  heap.insert(8221, 1);
  queue.push(8221);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9022, 1);
  queue.push(9022);
  heap.insert(9805, 1);
  queue.push(9805);
  heap.insert(8208, 1);
  queue.push(8208);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(4977, 1);
  queue.push(4977);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5992, 1);
  queue.push(5992);
  heap.insert(4979, 1);
  queue.push(4979);
  heap.insert(8719, 1);
  queue.push(8719);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5538, 1);
  queue.push(5538);
  heap.insert(5852, 1);
  queue.push(5852);
  heap.insert(8, 1);
  queue.push(8);
  heap.insert(5582, 1);
  queue.push(5582);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(2314, 1);
  queue.push(2314);
  heap.insert(6308, 1);
  queue.push(6308);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1230, 1);
  queue.push(1230);
  heap.insert(8857, 1);
  queue.push(8857);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1986, 1);
  queue.push(1986);
  heap.insert(8556, 1);
  queue.push(8556);
  heap.insert(8596, 1);
  queue.push(8596);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(2041, 1);
  queue.push(2041);
  heap.insert(7540, 1);
  queue.push(7540);
  heap.insert(5583, 1);
  queue.push(5583);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(730, 1);
  queue.push(730);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(4402, 1);
  queue.push(4402);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5053, 1);
  queue.push(5053);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9056, 1);
  queue.push(9056);
  heap.insert(7854, 1);
  queue.push(7854);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(8041, 1);
  queue.push(8041);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(3270, 1);
  queue.push(3270);
  heap.insert(8142, 1);
  queue.push(8142);
  heap.insert(9259, 1);
  queue.push(9259);
  heap.insert(2853, 1);
  queue.push(2853);
  heap.insert(3816, 1);
  queue.push(3816);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(2821, 1);
  queue.push(2821);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5511, 1);
  queue.push(5511);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(9233, 1);
  queue.push(9233);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(5007, 1);
  queue.push(5007);
  heap.insert(1710, 1);
  queue.push(1710);
  {
    auto v1 = heap.top_key();
    auto v2 = queue.top();

    heap.pop();
    queue.pop();

    REQUIRE(v1 == v2);
  }

  heap.insert(1259, 1);
  queue.push(1259);
}
