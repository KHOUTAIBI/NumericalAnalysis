#include "euler.h"

VectorXd euler(std::function<float(float,float)> f, float step, float y_0, float t_0, float T){
    
    int number_steps = static_cast<int>(T/step);
    VectorXd t = ArrayXd::LinSpaced(number_steps + 1,t_0,t_0+T);
    VectorXd y(number_steps + 1);
    y(0) = y_0;

    for (int j =0; j < number_steps; j++){
        y(j+1) = y(j) + step * f(t(j), y(j));

    }

    return y;
} 

MatrixXf euler_higher_diemension(std::function<VectorXf(float,VectorXf)> f, float step, VectorXf y_0, float t_0, float T){
    
    int number_steps = static_cast<int>(T/step);
    VectorXd t = ArrayXd::LinSpaced(number_steps + 1,t_0,t_0+T);
    MatrixXf y(number_steps + 1,y_0.size());
    y.row(0) = y_0.transpose();

    for (int j =0; j < number_steps; j++){
        y.row(j+1) = y.row(j).transpose() + step * f(t(j), y.row(j).transpose());

    }

    return y;
}


float f(float t, float y){
    return std::exp(-t);   
}

