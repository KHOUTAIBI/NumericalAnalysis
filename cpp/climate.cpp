#include "carbone.h"
#include "euler.h"

namespace plt = matplotlibcpp;

int main(int argc, char * argv[]){
    float step = 0.1;
    float T = 750;
    float t_0 = 1850;
    int number_steps = static_cast<int>(T/step);

    VectorXd t = ArrayXd::LinSpaced(number_steps + 1, t_0, t_0+T);
    MatrixXf y = euler_higher_diemension(derivative,step,x0,t_0,T);
    
    std::vector<double> x_vec(t.data(), t.data() + t.size());
    std::vector<double> y_vec(y.col(3).data(), y.col(3).data() + y.col(3).size());
    std::cout << y_vec.size() << ',' <<x_vec.size() <<'\n';


    plt::figure();
    plt::title("Approximation using Euler");
    plt::plot(x_vec,y_vec);
    plt::show();

}