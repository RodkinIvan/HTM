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

void print_connections(const Region& region) {
    for (size_t i = 0; i < region.column_dimensions[0]; ++i) {
        for (size_t j = 0; j < region.column_dimensions[1]; ++j) {
            for (size_t k = 0; k < region.cells_per_column; ++k) {
                for (auto& segment : region.cells[i][j][k].lateral_segments) {
                    for (auto& presynaptic_cell : segment.presynaptic_cells) {
                        auto[u, v, s] = region.get_coordinates(presynaptic_cell.first);
                        std::cout << '(' << u << ", " << v << ", " << s << ") ~> (" << i << ", " << j << ", " << k
                                  << ") with permanence = " << presynaptic_cell.second << '\n';
                    }
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
            0.4
    );
    std::vector<bool> bit_array{0, 1, 0, 1, 1, 0, 1, 0};
    auto sdrs = make_sdrs(bit_array);
    for (int i = 0; i < 10; ++i) {
        size_t iter = 0;
        for (auto& sdr : sdrs) {
            region.compute(sdr, true);
            std::cout << "Epoch " << i << ", sdr #" << iter << ":\n";
            print_connections(region);
            if (i > 0)
                print_predicted_cells(region);
            ++iter;
        }
    }
}
