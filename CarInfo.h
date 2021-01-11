//
// Created by badru on 01.09.2018.
//


#ifndef CPP_MADCARS_CAR_H
#include "../nlohmann/json.hpp"
using namespace nlohmann;
#define CPP_MADCARS_CAR_H

#endif //CPP_MADCARS_CAR_H

//
// Created by badru on 01.09.2018.
struct CarInfo{
    int type; //1 - Buggy, 2 - Bus, 3 - SquareWheelsBuggy, 4 - other
    bool is_squared_wheels;

//    Vect2D *vector;

    //initial new game datas
    double car_body_mass;
    int external_id;// - внешний id машины
    int squared_wheels ; //- признак квадратных колес 1 //Для машины с квадратными колесами еще приходит
    CarInfo();
    void InitNewMatch(json datas);

    //array button_poly;// - полигон кнопки // [[40, 42], [40.0, 43.0], [78.0, 43.0], [78.0, 42.0]]
    //array car_body_poly ;//- полигон машины [[0, 6], [0, 25], [33, 42], [85, 42], [150, 20], [150, 0], [20, 0]]
    //array rear_wheel_position ;//- положение заднего колеса в координатах относительно кузова машины [29, -5]
    //array rear_wheel_joint ;//- положение жесткого соединения заднего колеса [0, 0]
    //array rear_wheel_damp_position ;//- положение пружины заднего колеса [29, 20]
    //array front_wheel_position ;//- положение переднего колеса в координатах относительно кузова машины [122, -5]
    //array front_wheel_joint ;//- положение жесткого соединения переднего колеса
    //array front_wheel_damp_position ;//- положение пружины переднего колеса [122, 20]

//    double rear_wheel_mass ;//- масса заднего колеса 50
//    double rear_wheel_friction ;//- трение заднего колеса 1
//    double rear_wheel_elasticity ;//- эластичность заднего колеса 0.8
//    double car_body_friction ;//- трение кузова машины 0.9
//    double car_body_elasticity ;//- эластичность кузова машины 0.5
//    double max_speed ;//- максимальная угловая скорость колес 70
//    double max_angular_speed ;//- максимальная угловая скорость в воздухе (данный параметр больше не используется и скоро будет удален) 2
//    double torque ;//- крутящий момент кузова машины в воздухе 14000000
//    int drive;//- привод машины (передний, задний, полный) 2
//    double rear_wheel_radius ;//- радиус заднего колеса 12
//    double front_wheel_damp_length ;//- длина пружины переднего колеса 25
//    double front_wheel_damp_stiffness ;//- жесткость пружины переднего колеса 60000.0,
//    double front_wheel_damp_damping ;//- затухание пружины переднего колеса 900.0
//    double front_wheel_friction ;//- трение переднего колеса 1
//    double front_wheel_elasticity ;//- эластичность переднего колеса 0.8
//    double rear_wheel_damp_length ;// длина пружины заднего колеса 25
//    double rear_wheel_damp_stiffness ;//- жесткость пружины заднего колеса 50000.0,
//    double rear_wheel_damp_damping ;//- затухание пружины заднего колеса 3000.0
//    double front_wheel_radius ;//- радиус переднего колеса 12
//    double front_wheel_mass ;//- масса переднего колеса  5


    void Update(json datas);
    //updated datas
    double x_bottom_left_car;//0 x_нижнего_левого_угла_машины [[300.0, 2
    double y_bottom_left_car;//0 y_нижнего_левого_угла_машины   59.3127098610653],
    double car_angle;//1 угол машины                                     5.306690297069982e-18,
    int is_left; //2 1 | -1 (слева или справа находится машина),
    double x_back_wheel_car;//3 x_заднего_колеса_машины [338.0
    double y_back_wheel_car;//3 y_заднего_колеса_машины 254.31270986106534
    double back_wheel_car_angle; //4 угол_заднего_колеса_машины 5.3066778659190025e-18],
    double x_ahead_wheel_car;//5 x_переднего_колеса_машины [425.0
    double y_ahead_wheel_car;//5 y_переднего_колеса_машины 254.31270986106534
    double ahead_wheel_car_angle; //6 угол_переднего_колеса_машины 5.306690297069982e-18]

};

