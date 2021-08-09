#pragma once
#include "Cell.h"
struct Cell;

struct Segment{
    Region* region;

    std::vector<std::pair<Cell*, double>> presynaptic_cells;
    size_t active_synapses_num() const;
};