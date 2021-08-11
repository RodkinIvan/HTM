#include "Cell.h"

bool Cell::update_predict() {
    predict = false;
    active_segments.clear();
    matching_segments.clear();
    for (auto& segment : lateral_segments) {
        size_t active_num = segment.active_synapses_num();
        bool segment_predict = active_num >= region->activation_threshold;
        predict |= segment_predict;
        if (segment_predict) {
            active_segments.push_back(&segment);
        }
        size_t active_potential_num = segment.active_potential_num();
        if (active_potential_num >= region->min_threshold) {
            matching_segments.push_back(&segment);
        }
    }
    return predict;
}

