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

void Segment::replace_the_weakest_synapse(Cell* cell, double permanence) {
    if(presynaptic_cells.empty()){
        std::cerr << "Attempt to replace synapse in empty segment" << '\n';
        return;
    }
    double min_permanence = presynaptic_cells[0].second;
    auto the_weakest_presynaptic_cell = presynaptic_cells[0];
    for(auto& presynaptic_cell : presynaptic_cells){
        if(presynaptic_cell.second < min_permanence){
            min_permanence = presynaptic_cell.second;
            the_weakest_presynaptic_cell = presynaptic_cell;
        }
    }
    the_weakest_presynaptic_cell.first = cell;
    the_weakest_presynaptic_cell.second = permanence;
}
