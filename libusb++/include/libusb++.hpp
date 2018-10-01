// libusb++.hpp main header
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
#include <algorithm>
#include <memory>
#include <set>
#include <functional>
//-----------------------------------------------------------------------------------------------//
namespace std
{
   namespace usb
   {
      enum class class_code : unsigned
      {
         PER_INTERFACE = 0,
         AUDIO = 1,
         COMM = 2,
         HID = 3,
         PHYSICAL = 5,
         PRINTER = 7,
         PTP = 6,
         IMAGE = 6,
         MASS_STORAGE = 8,
         HUB = 9,
         DATA = 10,
         SMART_CARD = 0x0b,
         CONTENT_SECURITY = 0x0d,
         VIDEO = 0x0e,
         PERSONAL_HEALTHCARE = 0x0f,
         DIAGNOSTIC_DEVICE = 0xdc,
         WIRELESS = 0xe0,
         APPLICATION = 0xfe,
         VENDOR_SPEC = 0xff,
         UNKNOW = 0x00ff
      };
      //decode cpu cisc cpu to arm cpu
      using uint8 = unsigned char;
      using uint8_ptr = uint8 * ;
      using uint16 = unsigned short;
      using uint32 = unsigned int;
      using uint64 = unsigned long;
      //
      enum class descriptor_type : unsigned
      {
         DEVICE = 0x01,
         CONFIG = 0x02,
         STRING = 0x03,
         INTERFACE = 0x04,
         ENDPOINT = 0x05,
         BOS = 0x0f,
         DEVICE_CAPABILITY = 0x10,
         HID = 0x21,
         REPORT = 0x22,
         PHYSICAL = 0x23,
         HUB = 0x29,
         SUPERSPEED_HUB = 0x2a,
         SS_ENDPOINT_COMPANION = 0x30,
         UNKNOW = 0x00ff
      };
      //offset description type
      static const uint16 DTYPE_DEVICE_SIZE = 0x12;
      static const uint16 DTYPE_CONFIG_SIZE = 0x9;
      static const uint16 DTYPE_INTERFACE_SIZE = 0x9;
      static const uint16 DTYPE_ENDPOINT_SIZE = 0x7;
      static const uint16 DTYPE_ENDPOINT_AUDIO_SIZE = 0x9;
      static const uint16 DTYPE_HUB_NONVAR_SIZE = 0x7;
      static const uint16 DTYPE_SS_ENDPOINT_COMPANION_SIZE = 0x6;
      static const uint16 DTYPE_BOS_SIZE = 0x5;
      static const uint16 DTYPE_DEVICE_CAPABILITY_SIZE = 0x3;
      //BOS descriptor sizes
      static const uint16 BTYPE_USB_2_0_EXTENSION_SIZE = 0x7;
      static const uint16 BTYPE_SS_USB_DEVICE_CAPABILITY_SIZE = 0xA;
      static const uint16 BTYPE_CONTAINER_ID_SIZE = 0x14;
      //define max size to BOS
      static const uint16 DTYPE_BOX_MAX_SIZE = (DTYPE_BOX_SIZE +
                                                BTYPE_USB_2_0_EXTENSION_SIZE +
                                                BTYPE_SS_USB_DEVICE_CAPABILITY_SIZE +
                                                BTYPE_CONTAINER_ID_SIZE);
      //define endpoint address
      static const uint16 ENDPOINT_ADDRESS_MASK = 0xf;
      static const uint16 ENDPOINT_DIR_MASK = 0x80;
      //endpoint direction
      enum class endpoint_direction : unsigned
      {
         IN = 0x80,
         OUT = 0x00
      };
      //
      static const uint16 TRANSFER_TYPE_MASK = 0x03;
      //trasnfer
      enum class transfer_type : unsigned
      {
         CONTROL = 0x0,
         ISO_CHRONOUS = 0x1,
         BULK = 0x2,
         INTERRUPT = 0x3,
         BULK_STREAM = 0x4,
      };
      //
      //Standard requests, USB 3.0 specifications//
      enum class standard_request : unsigned
      {
         GET_STATUS = 0x00,
         CLEAR_FEATURE = 0x01,
         SET_FEATURE = 0x03,
         SET_ADDRESS = 0x05,
         GET_DESCRIPTOR = 0x06,
         SET_DESCRIPTOR = 0x07,
         GET_CONFIGURATION = 0x08,
         SET_CONFIGURATION = 0x09,
         GET_INTERFACE = 0x0A,
         SET_INTERFACE = 0x0B,
         SYNCH_FRAME = 0x0C,
         SET_SEL = 0x30,
         ISOCH_DELAY = 0x31,
      };
      //
      enum class request_type : unsigned
      {
         STANDARD = (0x00 << 5),
         CLASS = (0x01 << 5),
         VENDOR = (0x02 << 5),
         RESERVED = (0x03 << 5)
      };
      //
      enum class request_recipient : unsigned
      {
         DEVICE = 0x00,
         INTERFACE = 0x01,
         ENDPOINT = 0x02,
         OTHER = 0x03,
      };
      //
      static const uint16 IS0_SYNC_TYPE_MASK = 0x0c;
      static const uint16 ISO_USAGE_TYPE_MASK = 0x30;
      //
      enum class iso_sync_type : unsigned
      {
         NONE = 0x0,
         ASYNC = 0x1,
         ADAPTIVE = 0x2,
         SYNC = 0x3
      };
      //
      enum class iso_usage_type : unsigned
      {
         DATA = 0x0,
         FEEDBACK = 0x1,
         IMPLICIT = 0x2,
      };
      //
      enum class speed: unsigned
      {
         UNKNOW = 0x0, 
         LOW = 0x1,
         FULL = 0x2,
         HIGH = 0x3,
         SUPER = 0x4,
         SUPER_PLUS = 0x5
      };
      //
      enum class usb_2_0_extension_attributes: unsigned
      {
         LPM = 0x2
      };
      //
      enum class ss_usb_device_capability_attributes : unsigned
      {
         LTM = 0x2
      };
      //
      enum class libusb_bos_type: unsigned
      {
         WIRELESS_USB_DEVICE_CAPABILITY = 1,
         USB_2_0_EXTENSION = 2,
         SS_USB_DEVICE_CAPABILITY = 3,
         CONTAINER_ID = 4,
      };
      //
   #undef OVERFLOW //remove conflict
      enum class error: int
      {
         SUCCESS = 0,
         IO = -1,
         INVALID_PARAM = -2,
         ACCESS = -3,
         NO_DEVICE = -4,
         NOT_FOUND = -5,
         BUSY = -6,
         TIMEOUT = -7,
         OVERFLOW = -8,
         PIPE = -9,
         INTERRUPTED = -10,
         NO_MEM = -11,
         NOT_SUPPORTED = -12,
         OTHER = -99,
         COUNT = 0xe //total of error codes
      };
      //
      enum class transfer_status: unsigned
      {
         COMPLETED,
         ERROR,
         TIMED_OUT,
         CANCELLED,
         STALL,
         NO_DEVICE,
         OVERFLOW,
      };
      //
      enum class transfer_flags: unsigned
      {
         SHORT_NOT_OK = 1 << 0,
         FREE_BUFFER = 1 << 1,
         FREE_TRANSFER = 1 << 2,
         ADD_ZERO_PACKET = 1 << 3,
      };
      //
      enum class supported_speed
      {
         LOW = 0x1,
         FULL = 0x2,
         HIGH = 0x4,
         SUPER = 0x8
      };
      //
      struct device_descriptor
      {
         using device_descriptor_ptr = device_descriptor * ;
         //
         uint8  length;
         uint8  descriptor_type;
         uint16 cd_usb;
         uint8  device_class;
         uint8  device_subclass;
         uint8  device_protocol;
         uint8  max_packet_size_0;
         uint16 device_vendor;
         uint16 device_product;
         uint16 cd_device;
         uint8  manufacturer;
         uint8  product;
         uint8  serial_number;
         uint8  number_configurations;
         //
         device_descriptor() = default;
      };
      //
      struct endpoint_descriptor
      {
         using endpoint_descriptor_ptr = endpoint_descriptor * ;
         //
         uint8  length;
         uint8  descriptor_type;
         uint8  endpoint_address;
         uint8  max_attributes;
         uint16 max_packet_size;
         uint8  interval;
         uint8  refresh;
         uint8  synch_address;
         const uint8_ptr extra;
         int extra_length;
         //
         endpoint_descriptor() = default;
      };
      //
      struct interface_descriptor
      {
         using interface_descriptor_ptr = interface_descriptor * ;
         //
         uint8  length;
         uint8  descriptor_type;
         uint8  interface_number;
         uint8  alternate_setting;
         uint8  numbers_endpoints;
         uint8  interface_class;
         uint8  interface_subclass;
         uint8  interface_protocol;
         uint8  interface;
         const endpoint_descriptor::endpoint_descriptor_ptr endpoint;
         const uint8_ptr extra;
         int extra_length;
         //
         interface_descriptor() = default;
      };
      //
      struct interface
      {
         using interface_ptr = interface * ;
         //
         const interface_descriptor::interface_descriptor_ptr alternative_setting;
         int num_alternative_setting;
         //
         interface() = default;
      };
      //
      struct config_descriptor
      {
         using config_descriptor_ptr = config_descriptor * ;
         //
         uint8  length;
         uint8  descriptor_type;
         uint16 total_length;
         uint8  number_interfaces;
         uint8  configuration_value;
         uint8  configuration;
         uint8  max_attributes;
         uint8  max_power;
         const interface::interface_pointer interface_handle;
         const uint8_ptr extra;
         int extra_length;
         //
         config_descriptor() = default;
      };
      //
      struct ss_endpoint_companion_descriptor
      {
         using ss_endpoint_companion_descriptor_ptr = ss_endpoint_companion_descriptor * ;
         //
         uint8  length;
         uint8  descriptor_type;
         uint8  max_burst;
         uint8  max_attributes;
         uint16 bytes_per_interval;
         //
         ss_endpoint_companion_descriptor() = default;
      };
      //
      struct bos_dev_capability_descriptor
      {
         using bos_dev_capability_descriptor_ptr = bos_dev_capability_descriptor * ;
         //
         uint8 length;
         uint8 descriptor_type;
         uint8 dev_capability_type;
         uint8 dev_capability_data[0];
         //
         bos_dev_capability_descriptor() = default;
      };
      //
      struct bos_descriptor
      {
         using bos_descriptor_ptr = bos_descriptor * ;
         //
         uint8  length;
         uint8  descriptor_type;
         uint16 total_length;
         uint8  number_device_caps;
         //
         bos_dev_capability_descriptor::bos_dev_capability_descriptor_ptr device_capability[0];
         //
         bos_descriptor() = default;
      };
      //
      struct usb_2_0_extension_descriptor
      {
         using usb_2_0_extension_descriptor_ptr = usb_2_0_extension_descriptor * ;
         //
         uint8  length;
         uint8  descriptor_type;
         uint8  dev_capability_type;
         uint32  max_attributes;
         //
         usb_2_0_extension_descriptor() = default;
      };
      //
      struct ss_usb_device_capability_descriptor
      {
         using ss_usb_device_capability_descriptor_ptr = ss_usb_device_capability_descriptor * ;
         //
         uint8  length;
         uint8  descriptor_type;
         uint8  dev_capability_type;
         uint8  max_attributes;
         uint16 speed_supported;
         uint8  functionality_support;
         uint8  u1_dev_exitlat;
         uint16 u2_dev_exitlat;
         //
         ss_usb_device_capability_descriptor() = default;
      };
      //
      struct container_id_descriptor
      {
         using container_id_descriptor_ptr = container_id_descriptor * ;
         //
         uint8 length;
         uint8 descriptor_type;
         uint8 devcapability_type;
         uint8 reserved;
         uint8 containerid[0x10];
         //
         container_id_descriptor() = default;
      };
      //
      struct control_setup
      {
         using control_setup_ptr = control_setup * ;
         //
         uint8  max_request_type;
         uint8  request;
         uint16 value;
         uint16 index;
         uint16 length;
         //
         control_setup() = default;
         template<typename offset_t> 
         typename enable_if<is_arithmetic<typename offset_t>::value, typename offset_t>::type get_sizeof()
         {
            return offset_t(sizeof(*this));
         }
      };
      //
      struct iso_packet_descriptor
      {
         using iso_packet_descriptor_ptr = iso_packet_descriptor * ;
         //
         unsigned int length;
         unsigned int actual_length;
         transfer_status status{ transfer_status::ERROR };
      };
      //
      struct device_handle;
      struct transfer;
      using transfer_cb_fn = std::function<void(*)(std::usb::transfer * value)>;
      struct transfer
      {
         using transfer_ptr = transfer * ;
         //
         device_handle * dev_handle;
         uint8_t flags;
         unsigned char endpoint;
         unsigned char type;
         unsigned int timeout;
         transfer_status status;
         int length;
         int actual_length;
         transfer_cb_fn callback;
         void *user_data;
         uint8_ptr buffer;
         int num_iso_packets;
         iso_packet_descriptor iso_packet_desc[0];
      };
      //
      enum class capability: unsigned
      {
         CAPABILITY = 0x0000,
         HOTPLUG = 0x0001,
         HID_ACCESS = 0x0100,
         SUPPORTS_DETACH_KERNEL_DRIVER = 0x0101
      };
      //
      enum class log_level: unsigned
      {
         NONE = 0x0,
         ERROR = 0x1,
         WARNING = 0x2,
         INFO = 0x3,
         DEBUG = 0x4,
      };
   }
}
