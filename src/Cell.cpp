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

Segment* Cell::empty_worst_segment() {
    size_t min_active_potential = region->max_synapses_per_segment;
    Segment* worst_segment = nullptr;
    for(auto& segment : lateral_segments){
        size_t active_potential = segment.prev_active_potential_num();
        if(active_potential <= min_active_potential){
            min_active_potential = active_potential;
            worst_segment = &segment;
        }
    }
    worst_segment->presynaptic_cells.clear();
    return worst_segment;
}

