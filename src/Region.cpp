#include "Region.h"

/// value -> value in [0, 1]
double clip(double val) {
    return std::min(1.0, std::max(0.0, val));
}


void Region::compute(const Region::plate& _plate, bool learn) {
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
                        if (presynaptic_cell.first->prev_active) {
                            presynaptic_cell.second = clip(presynaptic_cell.second + permanence_increment);
                        } else {
                            presynaptic_cell.second = clip(presynaptic_cell.second - permanence_decrement);
                        }
                        /// can be more efficient
                        size_t new_synapses_count = synapse_sample_size - segment->prev_active_potential_num();
                        grow_synapses(*segment, new_synapses_count);
                    }
                }
            }
        }
    }
}

void Region::burst_column(size_t x, size_t y, bool learn) {
    /// Here is the thing why this project exists!
    /// We DO NOT burst the column, only the winner winner_cell, if we are in a good mood >:(
    auto[winner_cell, learning_segment] = best_matching_segment(x, y);
    if (learning_segment != nullptr) {
        ///.. Here can be something
    } else {
        winner_cell = least_used_cell(x, y);
        if (learn)
            learning_segment = grow_new_segment(winner_cell);
    }
    winner_cell->active = true;
    winners.push_back(winner_cell);
    if (learn) {
        for (auto& presynaptic_cell : learning_segment->presynaptic_cells) {
            presynaptic_cell.second += presynaptic_cell.first->prev_active ? permanence_increment
                                                                           : -permanence_decrement;
            presynaptic_cell.second = clip(presynaptic_cell.second);
        }
        size_t new_synapse_count = synapse_sample_size - learning_segment->prev_active_potential_num();
        grow_synapses(*learning_segment, new_synapse_count);
        if (prev_winners.empty()) {
            winner_cell->lateral_segments.pop_back();
        }
    }

}

void Region::punish_predicted_column(size_t x, size_t y, bool learn) {
    if (learn) {
        for (auto& cell : cells[x][y]) {
            for (auto* segment : cell.matching_segments) {
                for (auto& presynaptic_cell : segment->presynaptic_cells) {
                    if (presynaptic_cell.first->prev_active) {
                        presynaptic_cell.second -= predicted_segment_decrement;
                    }
                }
            }
        }
    }
}


Region::Region(const std::vector<size_t>& column_dimensions, size_t cells_per_column, size_t min_threshold,
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
        cells(column_dimensions[0],
              matrix_2d<Cell>(column_dimensions[1], vector<Cell>(cells_per_column, Cell(this)))) {}

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
                cell.update_predict();
            }
        }
    }
    for (auto& matrix : cells) {
        for (auto& row : matrix) {
            for (auto& cell : row) {
                cell.prev_active = cell.active;
                cell.active = false;
            }
        }
    }
    /// may be not the most efficient way
    prev_winners = std::move(winners);
    winners.clear();
}

void Region::grow_synapses(Segment& segment, size_t new_synapses_count) {
    auto candidates = prev_winners;
    //// Here should be sampling, but I'm lazy
    size_t counter = 0;
    for (size_t i = 0; i < candidates.size() && counter < new_synapses_count; ++i) {
        bool already_connected = false;
        for (auto& presynaptic_cell : segment.presynaptic_cells) {
            if (presynaptic_cell.first == candidates[i]) {
                already_connected = true;
                break;
            }
        }
        if (!already_connected) {
            ++counter;
            segment.presynaptic_cells.emplace_back(candidates[i], initial_permanence);
        }
    }
}

std::tuple<Cell*, Segment*> Region::best_matching_segment(size_t x, size_t y) {
    Segment* best_segment = nullptr;
    Cell* best_cell = nullptr;
    size_t best_score = 0;
    for (auto& cell : cells[x][y]) {
        for (auto* segment : cell.matching_segments) {
            size_t prev_active_potential_num = segment->prev_active_potential_num();
            if (prev_active_potential_num > best_score) {
                best_score = prev_active_potential_num;
                best_segment = segment;
                best_cell = &cell;
            }
        }
    }
    return {best_cell, best_segment};
}

Cell* Region::least_used_cell(size_t x, size_t y) {
    size_t least_segments_num = 4294967295ull;
    Cell* best_cell = nullptr;
    for (auto& cell : cells[x][y]) {
        if (cell.lateral_segments.size() < least_segments_num) {
            best_cell = &cell;
            least_segments_num = cell.lateral_segments.size();
        }
    }
    return best_cell;
}

Segment* Region::grow_new_segment(Cell* cell) {
    cell->lateral_segments.emplace_back();
}



