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
    void print_connections() const{
        Region::print_connections();
    }
};

BOOST_PYTHON_MODULE (HTM) {
    py::to_python_converter<std::vector<int>, vector_to_list<int>>();

    py::class_<temporal_memory_wrapper>("temporal_memory", py::init<py::tuple>())
            /// %#>!?&*$ default arguments
            .def(py::init<py::tuple, int>())
            .def(py::init<py::tuple, int, int>())
            .def(py::init<py::tuple, int, int, int>())
            .def(py::init<py::tuple, int, int, int, double>())
            .def(py::init<py::tuple, int, int, int, double, double>())
            .def(py::init<py::tuple, int, int, int, double, double, double>())
            .def(py::init<py::tuple, int, int, int, double, double, double, double>())
            .def(py::init<py::tuple, int, int, int, double, double, double, double, double>())
            .def(py::init<py::tuple, int, int, int, double, double, double, double, double, int>())
            .def(py::init<py::tuple, int, int, int, double, double, double, double, double, int, int>())
            .def("compute", &temporal_memory_wrapper::compute)
            .def("reset_predictions", &temporal_memory_wrapper::Region::reset_predictions)
            .def("get_anomaly", &temporal_memory_wrapper::Region::get_anomaly)
            .def("print_connections", &temporal_memory_wrapper::Region::print_connections)
            .def("print_connections", &temporal_memory_wrapper::print_connections);
}