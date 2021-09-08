#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <pulse/pulse.hpp>


TEST_CASE("signal::signal") {
  pulse::signal<void()> signal;
  REQUIRE(!signal);
}


void handler() { }

TEST_CASE("Binding to function") {
  pulse::signal<void()> signal;
  signal.bind(&handler);
  REQUIRE(!!signal);
}


struct foo {
  void method() {}
};

TEST_CASE("Binding to lambda") {
  pulse::signal<void()> signal;
  signal.bind([]{});
  REQUIRE(!!signal);
}


TEST_CASE("Binding to member") {
  struct test {
    void method() {}
  } obj;
  pulse::signal<void()> signal;
  signal.bind(&obj, &test::method);
  REQUIRE(!!signal);
}


TEST_CASE("Binding to other signal") {
  pulse::signal<void()> s1;
  s1.bind([]{});
  pulse::signal<void()> s2;
  s2 = s1;
  REQUIRE(!!s2);
}


TEST_CASE("Invoking empty signal") {
  pulse::source<void()> source;
  source();
  REQUIRE(!source);
}


TEST_CASE("Invoking signal") {
  struct test {
    int x{0};
    void method(int n) { x = n; }
  } obj;
  pulse::source<void(int)> source;
  source.bind(&obj, &test::method);
  source(-1);
  REQUIRE(obj.x == -1);
}
