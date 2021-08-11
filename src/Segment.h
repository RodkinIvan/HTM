#pragma once
#include "Cell.h"
struct Cell;
class Region;

struct Segment{
    std::vector<std::pair<Cell*, double>> presynaptic_cells;
    size_t active_synapses_num() const;
    size_t active_potential_num() const;
    size_t prev_active_potential_num() const;
};