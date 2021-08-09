#include "Region.h"

/// value -> value in [0, 1]
double clip(double val){
    return std::min(1.0, std::max(0.0, val));
}

void Region::compute(const Region::plate& _plate, bool learn) {
    winners.clear();
    for (size_t i = 0; i < column_dimensions[0]; ++i) {
        for (size_t j = 0; j < column_dimensions[1]; ++j) {
            if (_plate[i][j]) {
                if (is_predicted_col(i, j)) {
                    activate_predicted_column(i, j, learn);
                } else {
                    burst_column(i, j, learn);
                }
            } else {
                if (is_predicted_col(i, j)) {
                    punish_predicted_column(i, j, learn);
                }
            }
        }
    }
    step();
}

void Region::compute(const std::vector<plate>& data, bool learn) {
    for (const auto& _plate : data) {
        compute(_plate, learn);
    }
}

void Region::activate_predicted_column(size_t x, size_t y, bool learn) {
    for (auto& cell : cells[x][y]) {
        if (!cell.active_segments.empty()) {
            cell.active = true;
            winners.push_back(&cell);
            for (auto* segment : cell.active_segments) {
                if (learn) {
                    for (auto& presynaptic_cell : segment->presynaptic_cells) {
                        if (presynaptic_cell.first->prev_active){
                            presynaptic_cell.second = clip(presynaptic_cell.second + permanence_increment);
                        } else {
                            presynaptic_cell.second = clip(presynaptic_cell.second - permanence_decrement);
                        }
                    }
                }
            }
        }
    }
}

void Region::burst_column(size_t x, size_t y, bool learn) {

}

void Region::punish_predicted_column(size_t x, size_t y, bool learn) {

}


Region::Region(std::vector<size_t>& column_dimensions, size_t cells_per_column, size_t min_threshold,
               size_t activation_threshold, double initial_permanence, double connected_permanence,
               double permanence_increment, double permanence_decrement, double predicted_segment_decrement,
               size_t max_segments_per_cell, size_t max_synapses_per_segment) :
        column_dimensions(column_dimensions),
        cells_per_column(cells_per_column),
        min_threshold(min_threshold),
        activation_threshold(activation_threshold),
        initial_permanence(initial_permanence),
        connected_permanence(connected_permanence),
        permanence_increment(permanence_increment),
        permanence_decrement(permanence_decrement),
        predicted_segment_decrement(predicted_segment_decrement),
        max_segments_per_cell(max_segments_per_cell),
        max_synapses_per_segment(max_synapses_per_segment),
        cells(column_dimensions[0], matrix_2d<Cell>(column_dimensions[1], vector<Cell>(cells_per_column))) {}

bool Region::is_predicted_col(size_t x, size_t y) {
    bool predicted = false;
    for (auto& cell : cells[x][y]) {
        predicted |= cell.predict;
    }
    return predicted;
}

void Region::step() {
    for (auto& matrix : cells) {
        for (auto& row : matrix) {
            for (auto& cell : row) {
                cell.prev_active = cell.active;
                cell.active = false;
            }
        }
    }
}



