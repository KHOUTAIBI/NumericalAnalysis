Atmosphere(t) = Atmosphere(t - dt) + (PlantResp + SoilResp + Volcanoes + FossilFuelsCombustion - Photosynthesis - AtmOcExchange) * dt
    INIT Atmosphere = Atmosphere_Initial
    INFLOWS:
        PlantResp = (Plants * (55/INIT(Plants))) + Deforestation/2
        SoilResp = Soils * (55/INIT(Soils))
        Volcanoes = 0.1
        FossilFuelsCombustion = GRAPH(TIME)
        (50.0, 0.00), (75.0, 0.30), (100.0, 0.60), (125.0, 1.35), (150.0, 2.85), (175.0, 4.95), (200.0, 7.20), (225.0, 10.05), (250.0, 14.85), (275.0, 20.70), (300.0, 30.00)
    OUTFLOWS:
        Photosynthesis = 110 * CO2Effect * (VegLandArea_%/100) * TempEffect
        AtmOcExchange = Kao*(AtmCO2-pCO2Oc)
CarbonateRock(t) = CarbonateRock(t - dt) + (Sedimentation - Volcanoes) * dt
    INIT CarbonateRock = CarbonateRock_Initial
    INFLOWS:
        Sedimentation = DeepOcean * (0.1/INIT(DeepOcean))
    OUTFLOWS:
        Volcanoes = 0.1
DeepOcean(t) = DeepOcean(t - dt) + (Downwelling - Sedimentation - Upwelling) * dt
    INIT DeepOcean = DeepOcean_Initial
    INFLOWS:
        Downwelling = SurfaceOcean*(90.1/INIT(SurfaceOcean))
    OUTFLOWS:
        Sedimentation = DeepOcean * (0.1/INIT(DeepOcean))
        Upwelling = DeepOcean * (90/INIT(DeepOcean))
FossilFuelCarbon(t) = FossilFuelCarbon(t - dt) + ( - FossilFuelsCombustion) * dt
    INIT FossilFuelCarbon = FossilFuel_Initial
    OUTFLOWS:
        FossilFuelsCombustion = GRAPH(TIME)
        (50.0, 0.00), (75.0, 0.30), (100.0, 0.60), (125.0, 1.35), (150.0, 2.85), (175.0, 4.95), (200.0, 7.20), (225.0, 10.05), (250.0, 14.85), (275.0, 20.70), (300.0, 30.00)

Plants(t) = Plants(t - dt) + (Photosynthesis - PlantResp - Litterfall) * dt
    INIT Plants = Plant_Initial
    INFLOWS:
        Photosynthesis = 110 * CO2Effect * (VegLandArea_%/100) * TempEffect
    OUTFLOWS:
        PlantResp = (Plants * (55/INIT(Plants))) + Deforestation/2
        Litterfall = (Plants* (55/INIT(Plants)))+(Deforestation/2)
Soils(t) = Soils(t - dt) + (Litterfall - SoilResp) * dt
    INIT Soils = Soil_Initial
    INFLOWS:
        Litterfall = (Plants* (55/INIT(Plants)))+(Deforestation/2)
    OUTFLOWS:
        SoilResp = Soils * (55/INIT(Soils))
SurfaceOcean(t) = SurfaceOcean(t - dt) + (Upwelling + AtmOcExchange - Downwelling) * dt
    INIT SurfaceOcean = SurfaceOcean_Initial
    INFLOWS:
        Upwelling = DeepOcean * (90/INIT(DeepOcean))
        AtmOcExchange = Kao*(AtmCO2-pCO2Oc)
    OUTFLOWS:
        Downwelling = SurfaceOcean*(90.1/INIT(SurfaceOcean))
VegLandArea_%(t) = VegLandArea_%(t - dt) + ( - Development) * dt
    INIT VegLandArea_% = 100
    UNITS: PercentofOriginal
    OUTFLOWS:
        Development = (Deforestation/INIT(Plants) * 0.2) * 100
            UNITS: percentoforiginal/yr

Alk = 2.222446077610055
AtmCO2 = Atmosphere * (280/INIT(Atmosphere))
Atmosphere_Initial = 750
CarbonateRock_Initial = 100000000
CO2Effect = 1.5 * ((AtmCO2) - 40) / ((AtmCO2) + 80)
CO3 = (Alk-HCO3)/2
DeepOcean_Initial = 38000
Deforestation = 0
FossilFuel_Initial = 7500
GlobalTemp = 15 + ((AtmCO2-280) * .01)
HCO3 = (SurfCConc-(SQRT(SurfCConc^2-Alk*(2*SurfCConc-Alk)*(1-4*Kcarb))))/(1-4*Kcarb)
Kao = .278
Kcarb = .000575+(.000006*(WaterTemp-278))
KCO2 = .035+(.0019*(WaterTemp-278))
pCO2Oc = 280*KCO2*(HCO3^2/CO3)
Plant_Initial = 560
Soil_Initial = 1500
SurfaceOcean_Initial = 890
SurfCConc = (SurfaceOcean/12000)/SurfOcVol
SurfOcVol = .0362
TempEffect = ((60 - GlobalTemp) * (GlobalTemp + 15)) / (((60 + 15) / 2) ^ (2))/.96
WaterTemp = 273+GlobalTemp