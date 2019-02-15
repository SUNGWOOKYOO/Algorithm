#include "run_ext_sort.h"

#include "ext_merge_sort.h"
#include "misc.h"

void run_ext_sort(int page_size) {
	ExtMergeSort ext_merge_sort(page_size);
	ext_merge_sort.main();
}


