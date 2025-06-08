#include "rungekutta.h"

VectorXf rungekutta(std::function<float(float,float)> f, float step, float y_0, float t_0, float T){
    
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

std::pair<VectorXf, MatrixXf> rungekutta_higher_dimension(std::function<VectorXf(float, VectorXf)> f, float step, VectorXf y_0, float t_0, float T) {
    
    int number_steps = static_cast<int>(T / step);
    VectorXf t = ArrayXf::LinSpaced(number_steps + 1, t_0, t_0 + T).matrix(); 

    MatrixXf y(number_steps + 1, y_0.size());
    y.row(0) = y_0.transpose();

    for (int j = 0; j < number_steps; j++) {
        VectorXf yj = y.row(j).transpose();
        VectorXf p_n_1 = f(t(j), yj);

        float t_n_2 = t(j) + 0.5f * step;
        VectorXf y_n_2 = yj + 0.5f * step * p_n_1;
        VectorXf p_n_2 = f(t_n_2, y_n_2);

        float t_n_3 = t(j) + 0.5f * step;
        VectorXf y_n_3 = yj + 0.5f * step * p_n_2;
        VectorXf p_n_3 = f(t_n_3, y_n_3);

        float t_n_4 = t(j) + step;
        VectorXf y_n_4 = yj + step * p_n_3;
        VectorXf p_n_4 = f(t_n_4, y_n_4);

        y.row(j + 1) = (yj + (step / 6.0f) * (p_n_1 + 2.0f * p_n_2 + 2.0f * p_n_3 + p_n_4)).transpose();
    }

    return std::make_pair(t, y);  
}

float f(float t, float y){
    return 2 - std::exp(-4 * t) - 2*y;   
}
