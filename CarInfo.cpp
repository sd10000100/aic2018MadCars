#include "CarInfo.h"
#include "Constants.h"

CarInfo::CarInfo(){

}

void CarInfo::InitNewMatch(json datas)
{
    // cerr << "Init" <<endl;
    //squared_wheels = datas["squared_wheels"];
    is_squared_wheels = !datas["squared_wheels"].is_null();
    car_body_mass =datas["car_body_mass"];
    if (car_body_mass < MASS_TRESHOLD){
        type = !is_squared_wheels ? BUGGY : SQUARE_WHEELS_BUGGY;
    }
    else {
        type = !is_squared_wheels ? BUS : OTHER;
    }
    // cerr << "End Init" <<endl;
}

void CarInfo::Update(json datas) {
    //cerr << "Update" <<endl;
    car_angle = datas[1];

    // cerr << rad_to_grad(car_angle) <<endl;
    // cerr << datas[4] <<endl;
    x_ahead_wheel_car = datas[4][0];
    y_ahead_wheel_car = datas[4][1];

    x_back_wheel_car = datas[3][0];
    y_back_wheel_car = datas[3][1];

    is_left = datas[2];

    if (is_left) {
        car_angle = -car_angle;
    }
    // cerr << "End Update" <<endl;
    // vector = new Vect2D(new Point(x_back_wheel_car,y_back_wheel_car), new Point(x_ahead_wheel_car,y_ahead_wheel_car));
}
