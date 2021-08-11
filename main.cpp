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
    std::cout << "Prediction:\n";
    auto preds = region.get_predicted_cells_coordinates();
    for(auto [i, j, k] : preds){
        std::cout << "Column: " << i << ", " << j << ' ' << "Cell: " << k << '\n';
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

void test_bit_sequence(){
    Region region(
            {1, 2},
            4,
            1,
            1
            );
    std::vector<bool> bit_array{0, 1, 0, 1, 1, 0, 1, 0};
    auto sdrs = make_sdrs(bit_array);
    for (int i = 0; i < 10; ++i) {
        region.compute(sdrs);
    }
    std::cout << "Graph:\n";
    print_connections(region);
}

void real_time_test(){
    std::cout << "Cells per column: ";
    size_t cells_per_col = 1;
    std::cin >> cells_per_col;
    std::cout << '\n';
    std::cout << "Min threshold and activation threshold: ";
    size_t min = 0;
    size_t act = 0;
    std::cin >> min >> act;
    Region region(
            {1, 2},
            cells_per_col,
            min,
            act,
            0.4,
            0.5,
            0.1,
            0.1,
            0.05
            );
    std::cout << "Your bits array ('-1' to stop):\n";
    int b;
    while(std::cin >> b && b != -1){
        region.compute({{!bool(b), bool(b)}}, true);
        auto pred = region.get_predicted_cells_coordinates();
        std::cout << "Prediction: " <<( pred.empty() ? "None" : std::string(1, '0' + std::get<1>(pred[0]))) << '\n';
    }
    print_connections(region);
}

int main() {
//    test_bit_sequence();
    real_time_test();
}
