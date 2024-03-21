#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>

#include <rg_dynamics/rg_dynamics.hpp>
#include <rg_dynamics/types.hpp>

#include "include/pid_controller.hpp"

namespace py = pybind11;
namespace rgd = rg::dynamics;

PYBIND11_MODULE(controller_py, m){

    py::class_<PidController> controller(m, "controller_py");
    
    controller.def(py::init<rgd::RobotPtr&, rgd::Vector&,double,double,double,double>());

    controller.def("get_control_gain", &PidController::GetControlGain);
    controller.def("set_control_gain", &PidController::SetControlGain);
    controller.def("reset", &PidController::Reset);

    controller.def("compute_torque", &PidController::ComputeTorque);
}
