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
The following devices are available for use:
#1
  Name:          GeForce 320M
  Vendor:        NVIDIA
  Compute unit:  6
  Clock freq.:   950 MHz
  Mem. size:     256 MB
#2
  Name:          Intel(R) Core(TM)2 Duo CPU     U9400  @ 1.40GHz
  Vendor:        Intel
  Compute unit:  2
  Clock freq.:   1400 MHz
  Mem. size:     2048 MB
```

# m4マクロの出所

- ax_opencl.m4 : ImageMagickのtrunkからコピーしてボチボチ修正
- ax_compiler_vendor.m4 : GNU Autoconf Archiveの最新版そのまま
- ax_pthread.m4 : GNU Autoconf Archiveの最新版そのまま
