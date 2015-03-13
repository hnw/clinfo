# clinfo

Display information for OpenCL devices

# 概要

OpenCLでデバイス情報を表示するプログラムです。

OpenCLを使ったプロジェクトのひな形として作りました。Autotoolsを利用しており、少なくともMacとLinuxで同じソースコードをコンパイルすることができます。

# ビルド

以下のものが必要です。

- autoconf
- automake
- OpenCLヘッダ・ライブラリ

```
$ autoreconf -vfi
$ ./configure
$ make
```

make installしてもいいですけど、オススメしません。

# 実行例

```
$ ./clinfo
The number of OpenCL platforms available: 1
The following devices are available for use:
Platform #1
  Name:         Apple
  Vendor:       Apple
  Profile:      FULL_PROFILE
  Version:      OpenCL 1.2 (Jul 29 2014 21:24:39)
Device #1
  Name:         GeForce 320M
  Vendor:       NVIDIA
  Profile:      FULL_PROFILE
  OpenCL CU:    6
  Clock speed:  950 MHz
  Memory:       256 MB
  Extensions:
    cl_APPLE_SetMemObjectDestructor
    cl_APPLE_ContextLoggingFunctions
    cl_APPLE_clut
    cl_APPLE_query_kernel_names
    cl_APPLE_gl_sharing
    cl_khr_gl_event
    cl_khr_byte_addressable_store
    cl_khr_global_int32_base_atomics
    cl_khr_global_int32_extended_atomics
    cl_khr_local_int32_base_atomics
    cl_khr_local_int32_extended_atomics
Device #2
  Name:         Intel(R) Core(TM)2 Duo CPU     U9400  @ 1.40GHz
  Vendor:       Intel
  Profile:      FULL_PROFILE
  OpenCL CU:    2
  Clock speed:  1400 MHz
  Memory:       2048 MB
  Extensions:
    cl_APPLE_SetMemObjectDestructor
    cl_APPLE_ContextLoggingFunctions
    cl_APPLE_clut
    cl_APPLE_query_kernel_names
    cl_APPLE_gl_sharing
    cl_khr_gl_event
    cl_khr_fp64
    cl_khr_global_int32_base_atomics
    cl_khr_global_int32_extended_atomics
    cl_khr_local_int32_base_atomics
    cl_khr_local_int32_extended_atomics
    cl_khr_byte_addressable_store
    cl_khr_int64_base_atomics
    cl_khr_int64_extended_atomics
    cl_khr_3d_image_writes
    cl_khr_image2d_from_buffer
    cl_APPLE_fp64_basic_ops
    cl_APPLE_fixed_alpha_channel_orders
    cl_APPLE_biased_fixed_point_image_formats
    cl_APPLE_command_queue_priority
```

# m4マクロの出所

- ax_opencl.m4 : ImageMagickのtrunkからコピーしてボチボチ修正
- ax_compiler_vendor.m4 : GNU Autoconf Archiveの最新版そのまま
- ax_pthread.m4 : GNU Autoconf Archiveの最新版そのまま
