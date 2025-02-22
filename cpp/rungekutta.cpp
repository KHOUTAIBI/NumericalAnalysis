#include "rungekutta.h"

VectorXd rungekutta(std::function<float(float,float)> f, float step, float y_0, float t_0, float T){
    
    int number_steps = static_cast<int>(T/step);
    VectorXd t = ArrayXd::LinSpaced(number_steps + 1,t_0,t_0+T);
    VectorXd y(number_steps + 1);
    y(0) = y_0;

    for (int j =0; j < number_steps; j++){

        float p_n_1 = f(t(j),y(j));
        float t_n_2 = t(j) + 1/2 * step;
        float y_n_2 = y(j) + 1/2 * step * p_n_1;
        float p_n_2 = f(t_n_2, y_n_2);

        float t_n_3 = t_n_2;
        float y_n_3 = y(j) + 1/2 * step * p_n_2;
        float p_n_3 = f(t_n_3,y_n_3);

        float t_n_4 = t(j) + step;
        float y_n_4 = y(j) + step * p_n_3;
        float p_n_4 = f(t_n_4, y_n_4);
        
        y(j+1) = y(j) + step * (1/6 * p_n_1 + 2/6 * p_n_2 + 2/6 * p_n_3 + 1/6 * p_n_4);

    }

    return y;
} 


float f(float t, float y){
    return std::exp(-t);   
}

int main(int argc, const char * argv[]){
    VectorXd y = rungekutta(f,0.01,1,0,10);
    std::cout << y << '\n';
}