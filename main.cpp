#include <iostream>
#include "src/Region.h"

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
    for (auto[i, j, k] : preds) {
        std::cout << "Column: " << i << ", " << j << ' ' << "Cell: " << k << '\n';
    }
    std::cout << '\n';
}

void print_connections(const Region& region, bool all=false) {
    for (size_t i = 0; i < region.column_dimensions[0]; ++i) {
        for (size_t j = 0; j < region.column_dimensions[1]; ++j) {
            for (size_t k = 0; k < region.cells_per_column; ++k) {
                for (auto& segment : region.cells[i][j][k].lateral_segments) {
                    for (auto& presynaptic_cell : segment.presynaptic_cells) {
                        auto[u, v, s] = region.get_coordinates(presynaptic_cell.first);
                        if(presynaptic_cell.second >= region.connected_permanence || all){
                            std::cout << '(' << u << ", " << v << ", " << s << ") ~> (" << i << ", " << j << ", " << k
                            << ") with permanence = " << presynaptic_cell.second << '\n';
                        }
                    }
                }
            }
        }
    }
    std::cout << '\n';
}

void test_bit_sequence() {
    std::cerr << "Bit sequence test\n";
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

void real_time_test() {
    std::cerr << "Real-time test\n";
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
    while (std::cin >> b && b != -1) {
        region.compute({{!bool(b), bool(b)}}, true);
        auto pred = region.get_predicted_cells_coordinates();
        std::cout << "Prediction: " << (pred.empty() ? "None" : std::string(1, '0' + std::get<1>(pred[0]))) << '\n';
    }
    print_connections(region);
}

void test_some_series() {
    std::cerr << "Test some series\n";
    std::cout << "Prediction for series: ";
    std::vector<int> series{1, 2, 3, 2, 4};
    std::vector<int> series2{1, 5, 6, 3, 7};
    for(auto i : series){
        std::cout << i << ' ';
    }
    std::cout << "and ";
    for(auto i : series2){
        std::cout << i << ' ';
    }
    std::cout << '\n';
    size_t num_of_cols = 7;
    int cells_per_col = 4;
    std::vector<std::vector<std::vector<bool>>> sdrs(series.size(), std::vector<std::vector<bool>>(1, std::vector<bool>(num_of_cols)));
    std::vector<std::vector<std::vector<bool>>> sdrs2(series.size(), std::vector<std::vector<bool>>(1, std::vector<bool>(num_of_cols)));
    for (int i = 0; i < series.size(); ++i) {
        for (int j = 0; j < num_of_cols; ++j) {
            sdrs[i][0][j] = !(series[i] - j - 1);
            sdrs2[i][0][j] = !(series2[i] - j - 1);
        }
    }
    Region region(
            {1, num_of_cols},
            cells_per_col,
            1,
            1,
            0.4,
            0.5,
            0.1,
            0.1,
            0.05
    );
    for(int i = 0; i < 15; ++i){
        region.compute(sdrs);
        region.reset_predictions();
        region.compute(sdrs2);
        region.reset_predictions();
    }

    print_connections(region);
    region.compute(sdrs[0], false);
    auto predict_3 = region.prediction_for_several_steps(3);
    std::cout << "Prediction for 3 steps forward from 1:\n";
    for(auto [i, j, k] : predict_3){
        std::cout << j+1 << ' ';
    }
    std::cout << '\n';
}

void max_synapses_and_max_segments_limit_test(){
    /// Here I train untrainable pattern on purpose
    std::cerr << "Max synapses and max segments limit test\n";
    Region region(
            {1, 2},
            1,
            1,
            1,
            0.4,
            0.5,
            0.1,
            0.1,
            0.05,
            1,
            1
            );

    std::vector<bool> bit_array{0, 1, 1, 0};
    auto sdrs = make_sdrs(bit_array);
    for(int i = 0; i < 15; ++i){
        region.compute(sdrs);
    }
    std::cout << "Synapses:\n";
    print_connections(region, true);\
    std::cout << "As expected, they are with initial permanence, because they updates every computation\n";
}

int main() {
//    test_bit_sequence();
//    real_time_test();
//    test_some_series();
    max_synapses_and_max_segments_limit_test();
}
