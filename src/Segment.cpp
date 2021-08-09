#include "Segment.h"

size_t Segment::active_synapses_num() const {
    size_t num_active_synapses = 0;
    for(const auto& cell : presynaptic_cells){
        num_active_synapses += ((cell.second > region->connected_permanence) and cell.first->active);
    }
    return num_active_synapses;
}

size_t Segment::active_potential_num() const {
    size_t num_active_synapses = 0;
    for(const auto& cell : presynaptic_cells){
        num_active_synapses += cell.first->active;
    }
    return num_active_synapses;
}
