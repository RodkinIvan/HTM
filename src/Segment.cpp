#include "Segment.h"

size_t Segment::active_synapses_num() const {
    size_t num_active_synapses = 0;
    for (const auto& cell : presynaptic_cells) {
        /// using connected permanence of the presynaptic cell region. May cause some problems if use multilayer lateral segments
        num_active_synapses += ((cell.second > cell.first->region->connected_permanence) and cell.first->active);
    }
    return num_active_synapses;
}

size_t Segment::active_potential_num() const {
    size_t num_active_synapses = 0;
    for (const auto& cell : presynaptic_cells) {
        num_active_synapses += cell.first->active;
    }
    return num_active_synapses;
}

size_t Segment::prev_active_potential_num() const {
    size_t num_active_synapses = 0;
    for (const auto& cell : presynaptic_cells) {
        num_active_synapses += cell.first->prev_active;
    }
    return num_active_synapses;
}
