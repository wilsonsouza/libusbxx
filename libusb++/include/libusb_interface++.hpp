// libusb_interface++.hpp
//
// libusb++ full c++14 library
//
// Created by wilson.souza 2018
// (c) 2018 WRDev Info
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation
//
#pragma once
#include <libusb++.hpp>
#include <libusb_decode_cpu.hpp>
#include <mutex>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   namespace usb
   {
      namespace interface
      {
         //must be removed
         using interface_pointer = void *;
         #if defined(_MSC_VER)
         #if defined(_WIN64)
         #define ALIGNED(8) __declspec(align(8))
         #else
         #define ALIGNED __declspec(align(4))
         #endif
         #elif defined(__GNUC__)
         #define ALIGNED __attribute__((aligned(sizeof(void *))))
         #else
         #define ALIGNED
         #endif
         //
         enum class event_flags: unsigned
         {
            POLLFDS_MODIFIED = 1 << 0,
            USER_INTERRUPT = 1 << 1,
            HOTPLUG_CB_DEREGISTERED = 1 << 2,
         };
      }
   }
}
