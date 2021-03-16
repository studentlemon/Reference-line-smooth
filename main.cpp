#include <QCoreApplication>
#include "osqp_problem.h"
#include <math.h>
#include <iostream>
#include <array>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <limits>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include "smoothosqpproblem.h"


using namespace  std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout<<"OSQP RUNNING..."<<std::endl;


    ofstream mycout;
    time_t nowtime = time(NULL);
     struct tm *p;
     p = gmtime(&nowtime);
     char filename[256] = {0};
     char timeinfo[256] = {0};
     sprintf(timeinfo,"%d-%d-%d %d-%02d-osqp-traj",1900+p->tm_year,1+p->tm_mon,p->tm_mday,8+p->tm_hour,p->tm_min);
     mycout.open(timeinfo);


    std::vector<std::pair<double, double>> raw_point2d;
    std::vector<double> bounds;
    std::vector<double> opt_x;
    std::vector<double> opt_y;

//    for (int i = 0 ;i < 25; ++i) {

//        raw_point2d.push_back(std::make_pair(i*1.0,-25.0+i));
//    }

//    for (int i = 25 ;i < 50; ++i) {
//        raw_point2d.push_back(std::make_pair(i*1.0,0.0));
//    }

    for (int i = 0 ;i < 50; ++i) {
        raw_point2d.push_back(std::make_pair(i*1.0, 0.0));
    }

    bounds.push_back(0.1);

    for (int i = 0; i < 48; ++i) {
        bounds.push_back(50.0);
    }

    bounds.push_back(0.1);

//    //Now we are using default variables in osqp solver
//    double weight_fem_pos_deviation = 1e10;
//    double weight_path_length = 1.0;
//    double weight_ref_deviation = 1.0;
//    double weight_curvature_constraint_slack_var = 10.0;
//    double curvature_constraint = 0.08;
//    int sqp_sub_max_iter = 20;
//    int sqp_pen_max_iter = 10;
//    double sqp_ctol = 0.08;
//    int max_iter = 500;
//    double time_limit = 0.0;
//    bool verbose = false;
//    bool scaled_termination = true;
//    bool warm_start = true;

     FemPosDeviationSqpOsqpInterface solver;
     solver.set_ref_points(raw_point2d);
     solver.set_bounds_around_refs(bounds);

     if (!solver.Solve()) {
       std::cout<<"failture"<<std::endl;
     }

     std::vector<std::pair<double, double>> opt_xy = solver.opt_xy();

     // TODO(Jinyun): unify output data container
     opt_x.resize(opt_xy.size());
     opt_y.resize(opt_xy.size());
     for (size_t i = 0; i < opt_xy.size(); ++i) {
       opt_x[i] = opt_xy[i].first;
       opt_y[i] = opt_xy[i].second;
     }


     std::cout<<"xxx::"<<std::endl;
     for (int i = 0; i<opt_x.size(); ++i) {
         std::cout<<opt_x[i]<<std::endl;
     }


     std::cout<<"yyy::"<<std::endl;
     for (int i = 0; i<opt_y.size(); ++i) {
         std::cout<<opt_y[i]<<std::endl;
     }

//    if(prob->Optimize(1000)){
//      std::cout<<"Optimize successful!!"<<std::endl;

//      for (int i = 0; i < prob->x_.size(); ++i)
//      {
//          mycout<<"x: "<<prob->x_.at(i)<<" dx: "<<prob->dx_.at(i)<<" ddx: "<<prob->ddx_.at(i)<<" left_edge: "<<bound_info.boundary_.at(i).second<<" right_edge: "<<bound_info.boundary_.at(i).first<<std::endl;
//      }

//    }else{
//      std::cout<<"Optimize failed!!"<<std::endl;
//    }
    std::cout<<"OSQP END!!!"<<std::endl;

    return a.exec();
}
