# pulse
C++ signal/slot library

## Snippet

```cpp
#include <cstdio>
#include <pulse/pulse.hpp>


class component {
public:

  pulse::signal<void(int)>& property_changed() noexcept {
    return property_changed_;
  }

  void change(int p) noexcept {
    if(p == property_)
      return;
    property_ = p;
    property_changed_(p);
  }
  
  
  
private:

  int property_{0};
  pulse::source<void(int)> property_changed_;
  
};


int main() {

  component c;
  bool vonst binded = c.property_changed().bind([](int p) {
    std::printf("Property changed: %d\n", p);
  });
  
  if(!binded) {
    std::printf("Unable to bind handler\n");
    return 1;
  }
  
  c.change(-1);

  return 0;
}
```
