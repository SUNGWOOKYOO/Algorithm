#include "merge.h"

#include "output_buffer.h"
#include "read_buffer.h"

void merge(int page_size, string in_file_path1, string in_file_path2,
		string out_file_path, string debug_out_file_path) {
	OutputBuffer out_buf(page_size, out_file_path, debug_out_file_path);
	ReadBuffer read_buf1(page_size, in_file_path1);
	ReadBuffer read_buf2(page_size, in_file_path2);

	int x1, x2;
	read_buf1.read(x1);
	read_buf2.read(x2);
	while (true) {
		if (x1 < x2) {
			out_buf.add(x1);
			if (!read_buf1.read(x1)) {
				out_buf.add(x2);
				break;
			}
		} else {
			out_buf.add(x2);
			if (!read_buf2.read(x2)) {
				out_buf.add(x1);
				break;
			}
		}
	}
	while (read_buf1.read(x1)) {
		out_buf.add(x1);
	}
	while (read_buf2.read(x2)) {
		out_buf.add(x2);
	}
}
