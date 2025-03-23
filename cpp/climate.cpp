#include "carbone.h"
#include "euler.h"

using namespace matplot;

int main(int argc, char * argv[]){
    printf("Initializing the algorithm and plot");
    float step = 0.1;
    float T = 750;
    float t_0 = 1850;
    int number_steps = static_cast<int>(T/step);

    VectorXd t = ArrayXd::LinSpaced(number_steps + 1, t_0, t_0+T);
    MatrixXf y = euler_higher_diemension(derivative,step,x0,t_0,T);


    std::vector<double> x_time(t.data(), t.data() + t.size());
    std::vector<double> y_Atmosphere(y.col(0).data(), y.col(0).data() + y.col(0).size());
    std::vector<double> y_DeepOcean(y.col(2).data(), y.col(2).data() + y.col(2).size());
    std::vector<double> y_FossilFuel(y.col(3).data(), y.col(3).data() + y.col(3).size());
    std::vector<double> y_Plants(y.col(4).data(), y.col(4).data() + y.col(4).size());
    std::vector<double> y_Soils(y.col(5).data(), y.col(5).data() + y.col(5).size());

    hold(on);
    plot(x_time,y_Atmosphere);
    plot(x_time,y_DeepOcean);
    plot(x_time,y_FossilFuel);
    plot(x_time,y_Plants);
    plot(x_time,y_Soils);
    show();

}