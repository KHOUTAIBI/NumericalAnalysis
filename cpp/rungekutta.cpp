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
        
        
        y(j+1) = y(j) + step * (1/6.f * p_n_1 + 2/6.f * p_n_2 + 2/6.f * p_n_3 + 1/6.f * p_n_4);
        
    }

    return y;
} 

MatrixXf rungekutta_higher_dimension(std::function<VectorXf(float,VectorXf)> f, float step, VectorXd y_0, float t_0, float T){
    
    int number_steps = static_cast<int>(T/step);
    VectorXf t = ArrayXd::LinSpaced(number_steps + 1,t_0,t_0+T);
    VectorXf y(number_steps + 1,y_0.size());
    y.row(0) = y_0.transpose();

    for (int j =0; j < number_steps; j++){

        VectorXf p_n_1 = f(t(j),y.row(j).transpose());
        float t_n_2 = t(j) + 1/2 * step;
        VectorXf y_n_2 = y.row(j).transpose() + 1/2 * step * p_n_1;
        VectorXf p_n_2 = f(t_n_2, y_n_2.transpose());

        float t_n_3 = t_n_2;
        VectorXf y_n_3 = y.row(j).transpose() + 1/2 * step * p_n_2.transpose();
        VectorXf p_n_3 = f(t_n_3,y_n_3.transpose());

        float t_n_4 = t(j) + step;
        VectorXf y_n_4 = y.row(j).transpose() + step * p_n_3.transpose();
        VectorXf p_n_4 = f(t_n_4, y_n_4.transpose());
        
        
        y.row(j+1) = y.row(j).transpose() + step * (1/6.f * p_n_1.transpose() + 2/6.f * p_n_2.transpose() + 2/6.f * p_n_3.transpose() + 1/6.f * p_n_4.transpose());
        
    }

    return y;
}


float f(float t, float y){
    return 2 - std::exp(-4 * t) - 2*y;   
}


// int main(int argc, const char * argv[]){
    
//     VectorXd y = rungekutta(f,0.1,1,0,10);

//     int number_steps = static_cast<int>(10/0.1);
//     VectorXd t = ArrayXd::LinSpaced(number_steps + 1,0,0+10);

//     std::vector<double> x_vec(t.data(), t.data() + t.size());
//     std::vector<double> y_vec(y.data(), y.data() + y.size());

//     plt::figure();
//     plt::title("Approximation using Runge-Kutta");
//     plt::plot(x_vec,y_vec);
//     plt::show();
// }