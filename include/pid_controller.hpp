#include <rg_dynamics/rg_dynamics.hpp>
#include <rg_dynamics/types.hpp>

namespace rgd = rg::dynamics;

class PidController{
public:
    PidController(rgd::RobotPtr& robot, rgd::Vector& q_home, double dt,
                    double kp=80, double ki = 100, double kd = 10)
                    : robot_(robot),
                    q_home_(q_home),
                    dt_(dt),
                    kp_(kp),
                    ki_(ki),
                    kd_(kd)
                    {torque_limit_<< 500,500,300,100,100,100;};

    void GetControlGain();
    void SetControlGain(double kp, double ki, double kd);
    
    void UpdateDynamicParameters(rgd::Vector& q_curr);
    void Reset();

    rgd::Vector ComputeTorque(rgd::Vector& q_curr, rgd::Vector& q_goal);



private:
    //rg-dynamics robot handle
    rgd::RobotPtr robot_;

    // controller parameters
    rgd::Vector q_home_;
    int DOF = 6;
    double dt_;
    rgd::Vector torque_limit_ = rgd::Vector::Zero(DOF);

    // controller gain
    double kp_;
    double ki_;
    double kd_;
    rgd::Vector i_term = rgd::Vector::Zero(DOF);
    rgd::Vector last_error = rgd::Vector::Zero(DOF);

    // dynamic parameters
    rgd::Matrix M_= rgd::Matrix::Zero(DOF,DOF);
    rgd::Vector g_ = rgd::Vector::Zero(DOF);

};
