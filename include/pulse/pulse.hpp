/* This file is part of pulse library
 * Copyright 2020 Andrei Ilin <ortfero@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once


#include <utility>
#include <functional>


namespace pulse {

  template<typename>
  class signal;
  

  template<typename... Args>
  class signal<void (Args...)> {
  public:

    signal() noexcept = default;
    signal(signal const&) noexcept = default;
    signal& operator = (signal const&) noexcept = default;
    explicit operator bool () noexcept { return !!slot_; }


    bool bind(void (*slot)(Args...)) {
      if(slot_)
        return false;
      slot_ = slot;
      return true;
    }


    template<typename L>
    bool bind(L* listener, void (L::*slot)(Args...)) {
      if(slot_)
        return false;
      slot_ = [listener, slot](Args... args) { (listener->*slot)(args...); };
      return true;
    }


    template<typename F>
    bool bind(F&& slot) {
      if(slot_)
        return false;
      slot_ = slot;
      return true;
    }
    

    void unbind() {
      slot_ = std::function<void(Args...)>{};
    }


  protected:

    std::function<void(Args...)> slot_;

  }; // signal


  template<typename>
  class source;


  template<typename... Args>
  class source<void (Args...)> : public signal<void (Args...)> {
  public:

    using base_type = signal<void (Args...)>;

    source() noexcept = default;

    void operator ()(Args&&... args) {
      if(!base_type::slot_)
        return;
      base_type::slot_(std::forward<Args>(args)...);
    }

  }; // source

  
} // pulse
