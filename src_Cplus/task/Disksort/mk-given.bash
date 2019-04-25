#!/bin/bash
given_dir="../given"
rm -rf $given_dir
mkdir $given_dir
cp main.cpp misc.h misc.cpp read_buffer.h output_buffer.h sort.h ext_merge_sort.h ext_merge_sort.cpp merge.h run_ext_sort.h run_ext_sort.cpp  \
  $given_dir
