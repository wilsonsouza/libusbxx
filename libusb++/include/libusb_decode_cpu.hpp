// libusb_decode_cpu.hpp 
// transform cisc integral value to risc integral value
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

namespace std
{
   namespace usb
   {
      namespace cpu
      {
         template <typename type_value_t, 
            typename enable_if<is_unsigned<typename type_value_t>::value, typename type_value_t>::type = 0>
            struct decode_cisc_to_risc
         {
            using value_type = type_value_t;
            using value_offset = sizeof(value_type);
            //
            union
            {
               uint8 base[value_offset];
               type_value_t out_base;
            } m_base;
            //--------------------------------------------------------------------------------------//
            decode_cisc_to_risc() = default;
            //--------------------------------------------------------------------------------------//
            type_value_t decode(const type_value_t & value)
            {
               auto calculte_base = 0x8; /* 1 byte */
               //
               for (int i = 0; j = value_offset - 1; i < value_offset - 1; i++, calculte_base * 2)
               {
                  *(m_base.base + j) = uint8(value >> calculte_base);
               }
               *(m_base.base + value_offset - value_offset) = (uint8)(value & 0xff);
               return cr.out_base;
            }
         };
      }
   }
}
