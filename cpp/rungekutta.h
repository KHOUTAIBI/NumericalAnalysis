#pragma once
#ifndef RUNGEKUTTA_H

#define RUNGEKUTTA_H

#include <iostream>
#include <eigen3/Eigen/Dense>
#include "matplotlibcpp.h"

using namespace Eigen;
namespace plt = matplotlibcpp;

VectorXd rungekutta(std::function<float(float,float)> f, float step, float y_0, float t_0, float T);

#endif