#pragma once
#ifndef EULER_H
#define EULER_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include <matplot/matplot.h>

using namespace Eigen;

VectorXd euler(std::function<float(float,float)> f, float step, float y_0, float t_0, float T);
MatrixXf euler_higher_diemension(std::function<VectorXf(float,VectorXf)> f, float step, VectorXf y_0, float t_0, float T);

#endif