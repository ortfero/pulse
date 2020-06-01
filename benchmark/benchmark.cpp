#include <stdio.h>
#include <pulse/pulse.hpp>
#include <ubench/ubench.hpp>


struct listener {
}; // listener

using slot_type = void(listener::*)();

bool flag = true;


struct handler: listener {
  void slot() {
    flag = !flag;
  }
}; // handler




int main() {

  handler h;
  listener* l = &h;
  slot_type s = slot_type(&handler::slot);
  pulse::source<void()> source;
  source.bind(&h, &handler::slot);

  auto const member_bench = ubench::run([&]{ (l->*s)(); });
  auto const pulse_bench = ubench::run([&]{ source(); });

  printf("member_ptr - %.1fns\n", member_bench.time.count());
  printf("pulse::signal - %.1fns\n", pulse_bench.time.count());
  printf("flag = %s\n", flag ? "true" : "false");

  return 0;
}
