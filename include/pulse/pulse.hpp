// This file is part of pulse library
// Copyright 2020-2022 Andrei Ilin <ortfero@gmail.com>
// SPDX-License-Identifier: MIT

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
            slot_ = [listener, slot](Args... args) { (listener->*slot)(std::forward<Args>(args)...); };
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

        void operator ()(Args... args) {
          if(!base_type::slot_)
            return;
          base_type::slot_(std::forward<Args>(args)...);
        }

    }; // source

  
} // pulse
