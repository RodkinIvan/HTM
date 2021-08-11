#pragma once

#include "Region.h"
#include "Segment.h"

struct Synapse;

struct Cell {
public:
    Region* region;

    /// the state in a current time step
    bool active = false;

    /// the state in a previous time step
    bool prev_active = false;

    ///the predict in a current time step
    bool predict = false;

    std::vector<Segment> lateral_segments;
    std::vector<Segment*> active_segments;
    std::vector<Segment*> matching_segments;

    explicit Cell(Region* region) : region(region) {};


    bool update_predict();
};