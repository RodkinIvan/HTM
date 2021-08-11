#include <iostream>
#include "src/Region.h"

std::tuple<int, int> f(int x) {
    return {x, 2 * x};
}

std::vector<Region::plate> make_sdrs(const std::vector<bool>& bit_array) {
    std::vector<Region::plate> result(bit_array.size());
    size_t iter = 0;
    for (bool b : bit_array) {
        result[iter] = std::vector<std::vector<bool>>({{!b, b}});
        ++iter;
    }
    return result;
}

void print_predicted_cells(const Region& region) {
    for (size_t i = 0; i < region.column_dimensions[0]; ++i) {
        for (size_t j = 0; j < region.column_dimensions[1]; ++j) {
            for (size_t k = 0; k < region.cells_per_column; ++k) {
                if (region.cells[i][j][k].predict) {
                    std::cout << "Column: " << i << ", " << j << ' ' << "Cell: " << k << '\n';
                }
            }
        }
    }
    std::cout << '\n';
}

int main() {
    Region region(
            {1, 2},
            4,
            1,
            1,
            0.5
    );
    std::vector<bool> bit_array{0, 1, 0, 1, 1, 0, 1, 0};
    auto sdrs = make_sdrs(bit_array);
    for (int i = 0; i < 10; ++i) {
        for (auto& sdr : sdrs) {
            if(i == 1){
                int a = 0;
            }
            region.compute(sdr, true);

            if (i > 3)
                print_predicted_cells(region);
        }
    }
}
