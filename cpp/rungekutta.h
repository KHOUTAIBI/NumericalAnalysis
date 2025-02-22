#pragma once
#ifndef RUNGEKUTTA_H

#define RUNGEKUTTA_H

#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

VectorXd rungekutta(std::function<float(float,float)> f, float step, float y_0, float t_0, float T);

#endif