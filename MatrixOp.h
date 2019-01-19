#pragma once
#include <vector>

template <class T>
class MatrixOp {
private:
	std::vector<std::vector<T>> matrix;
	size_t rowN;
	size_t colN;
public:
	MatrixOp(size_t _rowN, size_t _colN):
		rowN(_rowN), colN(_colN){
		std::cout << "Constructor of MatrixOp" << std::endl;
		matrix.resize(rowN);
		int i = 0;
		for (auto& row: matrix) {
			row.resize(colN);
			int j = 0;
			for (auto& cell: row) {
				std::cout << "a["<< i <<"]"<<"["<<j++<<"]"<< " ";
				cell = 0;
			}
			i++;
			std::cout << std::endl;
		}
	}
};