#include <iostream>
#include <eigen3/Eigen/Dense>


using namespace Eigen;


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


float f(float t, float y){
    return std::cos(t);   
}

int main(int argc, const char * argv[]){
    VectorXd y = euler(f,0.01,0,0,10);
    std::cout << y << '\n';
}