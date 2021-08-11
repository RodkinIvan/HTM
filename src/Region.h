#pragma once

#include <vector>
#include <tuple>
#include "Cell.h"
struct Cell;
struct Segment;

class Region {
public:
    template<typename T>
    using matrix_3d = std::vector<std::vector<std::vector<T>>>;

    template<typename T>
    using matrix_2d = std::vector<std::vector<T>>;

    template<typename T>
    using vector = std::vector<T>;

    using plate = std::vector<std::vector<bool>>;
private:

    /// All the cells in the region
    matrix_3d<Cell> cells;

    /// winner-cells from the current step
    std::vector<Cell*> winners;

    /// winner-cells from the previous step
    std::vector<Cell*> prev_winners;

    /// checks if the column predicted by previous activationW
    bool is_predicted_col(size_t x, size_t y);

    /// trivial
    void activate_predicted_column(size_t x, size_t y, bool learn);

    /// actually, doesn't burst the column and activates only winner cell
    void burst_column(size_t x, size_t y, bool learn);

    /// if the column was predicted, but not actually activated by input
    void punish_predicted_column(size_t x, size_t y, bool learn);

    /// grows synapses to previous winners
    void grow_synapses(Segment& segment, size_t new_synapses_count);

    /// returns the best segment (with maximum amount of active potential synapses) with the cell, which it connected to
    std::tuple<Cell*, Segment*> best_matching_segment(size_t x, size_t y);

    /// returns the cell with least number of lateral segments
    Cell* least_used_cell(size_t x, size_t y);

    static Segment* grow_new_segment(Cell* cell);

    /// makes cell.prev_active = cell.active and cell.active = false for all cells and makes prev_winners = winners and winners.clear()
    /// and makes prediction
    void step();
public:

    /// configuration data
    std::vector<size_t> column_dimensions;
    size_t cells_per_column = 32;
    size_t min_threshold = 1;
    size_t activation_threshold = 2;
    double initial_permanence = 0.21;
    double connected_permanence = 0.5;
    double permanence_increment = 0.1;
    double permanence_decrement = 0.1;
    double predicted_segment_decrement = 0.0;
    size_t max_segments_per_cell = 255;
    size_t max_synapses_per_segment = 255;

    size_t synapse_sample_size = 1;

    explicit Region(
            const std::vector<size_t>& column_dimensions,
            size_t cells_per_column            = 32,
            size_t min_threshold               = 10,
            size_t activation_threshold        = 13,
            double initial_permanence          = 0.21,
            double connected_permanence        = 0.5,
            double permanence_increment        = 0.1,
            double permanenceDecrement         = 0.1,
            double predicted_segment_decrement = 0.0,
            size_t max_segments_per_cell       = 255,
            size_t max_synapses_per_segment    = 255
    );

    /// steps of TM algorithm for one SDR and several
    void compute(const plate& _plate, bool learn);
    void compute(const std::vector<plate>& data, bool learn = true);

    std::tuple<size_t, size_t, size_t> get_coordinates(const Cell* cell) const;

    std::vector<std::tuple<size_t, size_t, size_t>> get_predicted_cells_coordinates() const;

    friend void print_predicted_cells(const Region& region);
    friend void print_connections(const Region& region);
};

