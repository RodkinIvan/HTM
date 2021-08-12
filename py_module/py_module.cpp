#include "../src/Region.h"

#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

namespace py = boost::python;
namespace np = boost::python::numpy;



using array = py::list;
template<typename T>
using iterator = py::stl_input_iterator<T>;


/// std::vector to python list converter
template<typename T>
struct vector_to_list {
    static PyObject* convert(const std::vector<T>& vec) {
        auto l = boost::python::list();
        for (auto& i : vec) {
            l.append(i);
        }
        return l.ptr();
    }
};


template<typename T>
inline
std::vector<T> to_std_vector(const array& iterable) {
    return std::vector<T>(iterator<T>(iterable),
                          iterator<T>());

}

template<typename T>
inline
std::vector<std::vector<T>> to_2d_vector(const array& iterable) {
    std::vector<std::vector<T>> ans;
    for (auto iter = iterator<array>(iterable);
         iter != iterator<array>(); ++iter) {
        ans.push_back(to_std_vector<T>(*iter));
    }
    return ans;
}

struct temporal_memory_wrapper : Region {
    void compute(py::list& _plate, bool learn) {
        Region::compute(to_2d_vector<bool>(_plate), learn);
    }

    explicit temporal_memory_wrapper(
            const py::tuple& column_dimensions,
            size_t cells_per_column = 32,
            size_t min_threshold = 10,
            size_t activation_threshold = 13,
            double initial_permanence = 0.21,
            double connected_permanence = 0.5,
            double permanence_increment = 0.1,
            double permanence_decrement = 0.1,
            double predicted_segment_decrement = 0.0,
            size_t max_segments_per_cell = 255,
            size_t max_synapses_per_segment = 255
    ) :
            Region(
                    to_std_vector<size_t>(py::list(column_dimensions)),
                    cells_per_column,
                    min_threshold,
                    activation_threshold,
                    initial_permanence,
                    connected_permanence,
                    permanence_increment,
                    permanence_decrement,
                    predicted_segment_decrement,
                    max_segments_per_cell,
                    max_synapses_per_segment
            ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions
    ) : Region(
            to_std_vector<size_t>(column_dimensions)
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column,
            size_t min_threshold
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column,
            min_threshold
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column,
            size_t min_threshold,
            size_t activation_threshold
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column,
            min_threshold,
            activation_threshold
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column,
            size_t min_threshold,
            size_t activation_threshold,
            double initial_permanence
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column,
            min_threshold,
            activation_threshold,
            initial_permanence
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column,
            size_t min_threshold,
            size_t activation_threshold,
            double initial_permanence,
            double connected_permanence
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column,
            min_threshold,
            activation_threshold,
            initial_permanence,
            connected_permanence
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column,
            size_t min_threshold,
            size_t activation_threshold,
            double initial_permanence,
            double connected_permanence,
            double permanence_increment
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column,
            min_threshold,
            activation_threshold,
            initial_permanence,
            connected_permanence,
            permanence_increment
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column,
            size_t min_threshold,
            size_t activation_threshold,
            double initial_permanence,
            double connected_permanence,
            double permanence_increment,
            double permanence_decrement
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column,
            min_threshold,
            activation_threshold,
            initial_permanence,
            connected_permanence,
            permanence_increment,
            permanence_decrement
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column,
            size_t min_threshold,
            size_t activation_threshold,
            double initial_permanence,
            double connected_permanence,
            double permanence_increment,
            double permanence_decrement,
            double predicted_segment_decrement
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column,
            min_threshold,
            activation_threshold,
            initial_permanence,
            connected_permanence,
            permanence_increment,
            permanence_decrement,
            predicted_segment_decrement
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column,
            size_t min_threshold,
            size_t activation_threshold,
            double initial_permanence,
            double connected_permanence,
            double permanence_increment,
            double permanence_decrement,
            double predicted_segment_decrement,
            size_t max_segments_per_cell
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column,
            min_threshold,
            activation_threshold,
            initial_permanence,
            connected_permanence,
            permanence_increment,
            permanence_decrement,
            predicted_segment_decrement,
            max_segments_per_cell
    ) {}

    explicit temporal_memory_wrapper(
            const py::list& column_dimensions,
            size_t cells_per_column,
            size_t min_threshold,
            size_t activation_threshold,
            double initial_permanence,
            double connected_permanence,
            double permanence_increment,
            double permanence_decrement,
            double predicted_segment_decrement,
            size_t max_segments_per_cell,
            size_t max_synapses_per_segment
    ) : Region(
            to_std_vector<size_t>(column_dimensions),
            cells_per_column,
            min_threshold,
            activation_threshold,
            initial_permanence,
            connected_permanence,
            permanence_increment,
            permanence_decrement,
            predicted_segment_decrement,
            max_segments_per_cell,
            max_synapses_per_segment
    ) {}
};

BOOST_PYTHON_MODULE (HTM) {
    py::to_python_converter<std::vector<int>, vector_to_list<int>>();

    py::class_<temporal_memory_wrapper>("temporal_memory", py::init<py::tuple>())

            /// %#>!?&*$ default arguments
            .def(py::init<py::tuple, int, int, int, double, double, double, double, double, int, int>())
            .def(py::init<py::tuple, int>())
            .def(py::init<py::tuple, int, int>())
            .def(py::init<py::tuple, int, int, int>())
            .def(py::init<py::tuple, int, int, int, double>())
            .def(py::init<py::tuple, int, int, int, double, double>())
            .def(py::init<py::tuple, int, int, int, double, double, double>())
            .def(py::init<py::tuple, int, int, int, double, double, double, double>())
            .def(py::init<py::tuple, int, int, int, double, double, double, double, double>())
            .def(py::init<py::tuple, int, int, int, double, double, double, double, double, int>())
            .def("compute", &temporal_memory_wrapper::compute);
//            .def("predict", &clf_wrapper::predict);
}