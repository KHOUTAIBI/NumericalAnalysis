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


float f(float t, float y){
    return std::exp(-t);   
}

int main(int argc, const char * argv[]){
    
    VectorXd y = euler(f,0.1,0,0,10);

    int number_steps = static_cast<int>(10/0.1);
    VectorXd t = ArrayXd::LinSpaced(number_steps + 1,1,1+10);

    std::vector<float> x_vec(t.data(), t.data() + t.size());
    std::vector<float> y_vec(y.data(), y.data() + y.size());

    plt::figure();
    plt::title("Approximation using Euler Method");
    plt::plot(x_vec,y_vec);
    plt::show();


}