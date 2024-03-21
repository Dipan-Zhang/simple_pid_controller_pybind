#include "pid_controller.hpp"
#include <iostream>

void PidController::GetControlGain(){
    std::cout << "current control gain" << "kp: "   << kp_
                                        << ", ki: " <<ki_
                                        << ", kd: " <<kd_ 
                                        << std::endl;
}

void PidController::SetControlGain(double kp, double ki, double kd){
    kp_ = kp;
    ki_ = ki;
    kd_ = kd;
    std::cout << "control gain updated!" << "kp: " << kp_
                                         << ", ki: " << ki_
                                         << ", kd: " << kd_ 
                                         << std::endl;
}
void PidController::Reset(){
    i_term = rgd::Vector::Zero(DOF);
    last_error = rgd::Vector::Zero(DOF);
}

void PidController::UpdateDynamicParameters(rgd::Vector& q_curr){
    M_ = robot_->MassMatrix(q_curr);
    g_ = robot_->GravityVector(q_curr);
}

rgd::Vector PidController::ComputeTorque(rgd::Vector& q_curr, rgd::Vector& q_goal){

    rgd::Vector error = (q_goal - q_curr);
    rgd::Vector p_term =  error * kp_;
    rgd::Vector d_term = (error-last_error) / dt_ * kd_;
    i_term = i_term + error * ki_ *dt_;
    last_error = error;

    UpdateDynamicParameters(q_curr);

    rgd::Vector torque = p_term + i_term + d_term + g_;

    // limit computed torque w.r.t torque limit
    return torque.cwiseMin(torque_limit_).cwiseMax(-torque_limit_);
}

