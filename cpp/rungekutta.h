#pragma once
#ifndef RUNGEKUTTA_H

#define RUNGEKUTTA_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include "matplotlibcpp.h"

using namespace Eigen;
namespace plt = matplotlibcpp;

VectorXf rungekutta(std::function<float(float,float)> f, float step, float y_0, float t_0, float T);
std::pair<VectorXf, MatrixXf> rungekutta_higher_dimension(std::function<VectorXf(float, VectorXf)> f, float step, VectorXf y_0, float t_0, float T);

#endif