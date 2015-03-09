# clinfo

Display information for OpenCL devices

# 概要

OpenCLでデバイス情報を表示するプログラムです。

OpenCLを使ったプロジェクトのひな形として作りました。Autotoolsを利用しており、少なくともMacとLinuxで同じソースコードをコンパイルすることができます。

# ビルド

```
$ ./configure
$ make
```

make installしてもいいですけど、特にオススメしません。

# 実行例

```

```

# m4マクロの出所

- ax_opencl.m4 : ImageMagickのtrunkをボチボチ修正
- ax_compiler_vendor.m4 : GNU Autoconf Archiveの最新版そのまま
- ax_pthread.m4 : GNU Autoconf Archiveの最新版そのまま
