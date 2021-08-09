#include "Cell.h"

bool Cell::update_predict() {
    active_segments.clear();
    for (auto& segment : lateralSegments) {
        bool segment_predict = segment.active_synapses_num() > region->activation_threshold;
        predict |= segment_predict;
        if (segment_predict) {
            active_segments.push_back(&segment);
        }
    }
    return predict;
}
