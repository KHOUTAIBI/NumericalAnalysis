#include <eigen3/Eigen/Dense>

// Initial conditions
using namespace Eigen;

const float Atmosphere_Initial = 750;
const float CarbonateRock_Initial = 100000000;   
const float DeepOcean_Initial = 38000;
const float FossilFuel_Initial = 7500;
const float Plant_Initial = 560;
const float Soil_Initial = 1500;
const float SurfaceOcean_Initial = 890;
const float VegLandArea_percent_Initial = 100;


// Initial Values
VectorXf x0 {{Atmosphere_Initial,
               CarbonateRock_Initial,
               DeepOcean_Initial,
               FossilFuel_Initial,
               Plant_Initial,
               Soil_Initial,
               SurfaceOcean_Initial,
               VegLandArea_percent_Initial
            }};


// Constants
const float Alk = 2.222446077610055;
const float Kao = .278;
const float SurfOcVol = .0362;
const float Deforestation = 1.0;

// Helper functions
float AtmCO2(float Atmosphere){
    return Atmosphere * (280/Atmosphere_Initial);
}

float GlobalTemp(float AtmCO2){
    return 15 + ((AtmCO2-280) * .01);
}

float CO2Effect(float AtmCO2){
    return 1.5 * ((AtmCO2) - 40) / ((AtmCO2) + 80);
}

float WaterTemp(float GlobalTemp){
    return 273+GlobalTemp;
}

float TempEffect(float GlobalTemp){
    return ((60 - GlobalTemp) * (GlobalTemp + 15)) / ( pow(((60 + 15) / 2),(2)))/.96;
}

float SurfCConc(float SurfaceOcean){
    return (SurfaceOcean/12000)/SurfOcVol;
}

float Kcarb(float WaterTemp){
    return .000575+(.000006*(WaterTemp-278));
}

float KCO2(float WaterTemp){
    return .035+(.0019*(WaterTemp-278));
}

float HCO3(float Kcarb,float SurfCConc){
    return(SurfCConc-(sqrt(pow(SurfCConc,2)-Alk*(2*SurfCConc-Alk)*(1-4*Kcarb))))/(1-4*Kcarb);
}

float CO3(float HCO3){
    return (Alk-HCO3)/2;
}

float pCO2Oc(float KCO2,float HCO3, float CO3){
    return 280*KCO2*(pow(HCO3,2)/CO3);
}


// Fossil fuels
const Matrix<float,11,2> FossFuelData = (Eigen::Matrix<float, 11, 2>() << 
1850.0, 0.00,
1875.0, 0.30,
1900.0, 0.60,
1925.0, 1.35,
1950.0, 2.85,
1975.0, 4.95,
2000.0, 7.20,
2025.0, 10.05,
2050.0, 14.85,
2075.0, 20.70,
2100.0, 30.00).finished();


// funcitons to use
float FossilFuelsCombustion(float t){
    int i = 0;
    if (t >= FossFuelData(FossFuelData.rows() - 1, 0)){
        return FossFuelData(FossFuelData.rows() - 1, 1);
    }
    while (i + 1 < FossFuelData.rows() && t >= FossFuelData(i, 0)){
        i = i + 1;
    }
    if (i == 0){
        return FossFuelData(0, 1);
    }
    else{
        return FossFuelData(i-1, 1) + (t - FossFuelData(i-1, 0)) / 
               (FossFuelData(i, 0) - FossFuelData(i-1, 0)) * 
               (FossFuelData(i, 1) - FossFuelData(i-1, 1));
    }
}
                        

VectorXf derivative(float t,VectorXf x){

    float Atmosphere = x(0);
    float CarbonateRock = x(1);
    float DeepOcean = x(2);
    float FossilFuelCarbon = x(3);
    float Plants = x(4);
    float Soils = x(5);
    float SurfaceOcean = x(6);
    float VegLandArea_percent = x(7);

    float PlantResp = (Plants * (55/Plant_Initial)) + Deforestation/2;
    float Litterfall = (Plants* (55/Plant_Initial))+(Deforestation/2);
    float SoilResp = Soils * (55/Soil_Initial);
    float Volcanoes = 0.1;
    float AtmCO2_ = AtmCO2(Atmosphere);
    float GlobalTemp_ = GlobalTemp(AtmCO2_);
    float WaterTemp_ = WaterTemp(GlobalTemp_);
    float Photosynthesis = 110 * CO2Effect(AtmCO2_) * (VegLandArea_percent/100) * TempEffect(GlobalTemp_);
    float HCO3_ = HCO3(Kcarb(WaterTemp_), SurfCConc(SurfaceOcean));
    float pCO2Oc_ = pCO2Oc(KCO2(WaterTemp_), HCO3_, CO3(HCO3_));
    float AtmOcExchange = Kao*(AtmCO2_-pCO2Oc_);
    float FossilFuelsCombustion_;
    
    if (x(3) > 0){
        FossilFuelsCombustion_ = FossilFuelsCombustion(t);
    }

    else{
        FossilFuelsCombustion_ = 0;
    }

    float dAtmosphere_dt = (PlantResp + SoilResp + Volcanoes + FossilFuelsCombustion_
                          - Photosynthesis - AtmOcExchange);

    float Sedimentation = DeepOcean * (0.1/DeepOcean_Initial);
    float dCarbonateRock_dt = Sedimentation - Volcanoes;

    float Downwelling = SurfaceOcean*(90.1/SurfaceOcean_Initial);
    float Upwelling = DeepOcean * (90/DeepOcean_Initial);
    float dDeepOcean_dt= Downwelling - Sedimentation - Upwelling;

    float dFossilFuelCarbon_dt = - FossilFuelsCombustion_;

    float dPlants_dt = Photosynthesis - PlantResp - Litterfall;

    float dSoils_dt = Litterfall - SoilResp;

    float dSurfaceOcean_dt = Upwelling + AtmOcExchange - Downwelling;

    float Development = (Deforestation/Plant_Initial * 0.2) * 100;
    float dVegLandArea_percent_dt = - Development;

    VectorXf derivative{{
        dAtmosphere_dt,
        dCarbonateRock_dt,
        dDeepOcean_dt,
        dFossilFuelCarbon_dt,
        dPlants_dt,
        dSoils_dt,
        dSurfaceOcean_dt,
        dVegLandArea_percent_dt
    }};


    return derivative;
}

