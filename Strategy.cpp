#include <iostream>
#include <cmath>
#include "CarInfo.h"
//#include "Vect2D.cpp"
#include "../nlohmann/json.hpp"
#include "Constants.h"
#include <algorithm>

using namespace std;
using namespace nlohmann;

double rad_to_grad(double rad)
{
    return 180*rad/M_PI;
}

double grad_to_rad(double grad)
{
    return M_PI * grad/180;
}

json set_command(double angle, int current_tick,  string back_command, string ahead_command , CarInfo my_car_info, double fall_ind){
    json command;
    if(current_tick >= 45-fall_ind)
    {
        if (abs(rad_to_grad(my_car_info.car_angle)) == angle)
            command[COMMAND] =STOP;
        else if (abs(rad_to_grad(my_car_info.car_angle)) > angle)
            command[COMMAND] =back_command;
        else command[COMMAND] =ahead_command;
    }

    else command[COMMAND] =STOP;
    return command;
}

int main() {

    string input_string, input_type, init_params;
    string my_back, my_ahead;
    CarInfo car_info;
    CarInfo enemy_info;

    int ticks = 0;
    int type_of_map = 0;
    bool is_opponent_over_me = false;
    while (true) {
        json mapInfo;
        json command;
        getline(cin, input_string);
        auto state = json::parse(input_string);

        input_type = state["type"].get<std::string>();

        if (input_type == NEW_MATCH) {
            ticks = 0;
            is_opponent_over_me = false;
            //cerr << input_string <<endl;
            type_of_map = state["params"]["proto_map"]["segments"].size();
            car_info.InitNewMatch(state["params"]["proto_car"]);
            enemy_info.InitNewMatch(state["params"]["proto_car"]);
            mapInfo = state["params"]["proto_map"]["segments"];
        } else if (input_type == "tick") {
            try{
//
                //cerr << ticks <<endl;
                car_info.Update(state["params"]["my_car"]);
                enemy_info.Update(state["params"]["enemy_car"]);
                if(car_info.is_left == 1)
                {
                    my_back = LEFT;
                    my_ahead = RIGHT;
                }
                else
                {
                    my_back = RIGHT;
                    my_ahead = LEFT;
                }

                if(type_of_map==PILL_MAP)
                {
                    double angletemp = ((double)ticks+70)/70;
                    if(car_info.type == BUS){
                        // Final
                        if(ticks<45)
                            command[COMMAND] = STOP;
                        else if (ticks>=45 && ticks<103)
                            command[COMMAND] = my_back;
                        else if (ticks>=103 && ticks<131)
                            command[COMMAND] = STOP;
                        else if (ticks>=131 && ticks<166)
                            command[COMMAND] = my_back;
                        else if (ticks>=166 && ticks<180)
                            command[COMMAND] = my_ahead;
                        else if (ticks>=180 && ticks<200)
                            command[COMMAND] = STOP;
                        else if (ticks>=200 && ticks<220)
                            command[COMMAND] = my_ahead;
                        else {
                            car_info.car_angle = grad_to_rad(
                                    360 - car_info.is_left * rad_to_grad(car_info.car_angle));
                            command = set_command(90, ticks,  my_back, my_ahead, car_info,40);
                        }
                    }
                    else if (car_info.type == BUGGY )
                    {

                        double angle = 15*angletemp>45? 45 : 15*angletemp;
                        if(abs(enemy_info.x_ahead_wheel_car - car_info.x_back_wheel_car)<
                                abs(car_info.x_ahead_wheel_car - car_info.x_back_wheel_car))
                        {
                            if (car_info.is_left==1)
                                angle = enemy_info.x_ahead_wheel_car>car_info.x_ahead_wheel_car+10? 75 : 10;
                            else
                                angle = enemy_info.x_ahead_wheel_car>car_info.x_ahead_wheel_car+10? 10 : 75;
                        }

                        if (car_info.is_left==-1 && car_info.x_ahead_wheel_car<300)
                        {
                            angle = ((450-car_info.x_ahead_wheel_car)/300)*90;
                        }
                        if (car_info.is_left==-1)
                        {
                            if (car_info.x_ahead_wheel_car<300)
                                angle = ((450-car_info.x_ahead_wheel_car)/300)*90;
                            else if(car_info.x_ahead_wheel_car>750)
                                angle = ((550-car_info.x_ahead_wheel_car)/(-400))*90;
                           // cerr<< (angle)<<endl;
                        }
                        else {
                            if (car_info.x_ahead_wheel_car<300)
                                angle = ((450-car_info.x_ahead_wheel_car)/(300))*90;
                            else if(car_info.x_ahead_wheel_car>750)
                                angle = ((450-car_info.x_ahead_wheel_car)/(-700))*90;
                            //cerr<< (angle)<<endl;
                        }
                        command = set_command(angle, ticks,  my_back, my_ahead, car_info,0);

                    }
                    else {
                        command = set_command(25*angletemp>45? 45 : 25*angletemp  , ticks,  my_back, my_ahead, car_info,0);
                    }
                }
                else if (type_of_map==PILL_CARCASS_MAP)
                {

                    command[COMMAND] = STOP;
                    if(car_info.type == BUGGY) {
                        double angletemp = ((double)ticks+70)/70;
                        double angle = 15*angletemp>45? 45 : 15*angletemp;
                        if(abs(enemy_info.x_ahead_wheel_car - car_info.x_back_wheel_car)<
                           abs(car_info.x_ahead_wheel_car - car_info.x_back_wheel_car))
                        {
                            if (car_info.is_left==1)
                                angle = enemy_info.x_ahead_wheel_car>car_info.x_ahead_wheel_car+10? 75 : 10;
                            else
                                angle = enemy_info.x_ahead_wheel_car>car_info.x_ahead_wheel_car+10? 10 : 75;
                        }

                        if (car_info.is_left==-1 && car_info.x_ahead_wheel_car<300)
                        {
                            angle = ((450-car_info.x_ahead_wheel_car)/300)*90;
                        }
                        if (car_info.is_left==-1)
                        {
                            if (car_info.x_ahead_wheel_car<300)
                                angle = ((450-car_info.x_ahead_wheel_car)/300)*90;
                            else if(car_info.x_ahead_wheel_car>750)
                                angle = ((550-car_info.x_ahead_wheel_car)/(-400))*90;
                            // cerr<< (angle)<<endl;
                        }
                        else {
                            if (car_info.x_ahead_wheel_car<300)
                                angle = ((450-car_info.x_ahead_wheel_car)/(300))*90;
                            else if(car_info.x_ahead_wheel_car>750)
                                angle = ((450-car_info.x_ahead_wheel_car)/(-700))*90;
                            //cerr<< (angle)<<endl;
                        }
                        command = set_command(angle, ticks,  my_back, my_ahead, car_info,0);
                    }
                    else if(car_info.type == BUS){
                        if (ticks < 50)
                            command[COMMAND] = STOP;
                        else if (ticks >= 50 && ticks < 160)
                            command[COMMAND] = my_back;
                        else if(ticks>=160 && ticks<240)
                            command[COMMAND] = STOP;
                        else if(ticks>=240 && ticks<300)
                            command[COMMAND] = my_ahead;
                        else if(ticks>=300 && ticks<320)
                            command[COMMAND] = my_back;
                        else
                        {
                            car_info.car_angle = grad_to_rad(
                                    360 - car_info.is_left * rad_to_grad(car_info.car_angle));
                            command = set_command(70, ticks, my_back, my_ahead, car_info, 0);
                        }
                    }
                    else
                    {
                        if(ticks<=45)
                            command[COMMAND] = STOP;
                        else if(ticks>45 && ticks<120)
                            command[COMMAND] = my_back;
                        else if(ticks>=120 && ticks<200)
                            command[COMMAND] = STOP;
                        else{
                            car_info.car_angle = grad_to_rad(
                                    360 - car_info.is_left * rad_to_grad(car_info.car_angle));
                            if((car_info.is_left==1 && car_info.x_ahead_wheel_car<640) ||
                                (car_info.is_left==-1 && car_info.x_ahead_wheel_car>500))
                                command = set_command(35, ticks, my_back, my_ahead, car_info, 0);
                            else
                                command[COMMAND] = STOP;
                        }
                    }
                }
                else if (type_of_map==ISLAND_MAP) {
                   // double angletemp = ((double)ticks+150)/150;
                    if (car_info.type==BUGGY)
                    {
//                        int temp_treshold = car_info.is_left? 15 : 25;
//                        double angle =rad_to_grad(enemy_info.car_angle)>temp_treshold ? rad_to_grad(enemy_info.car_angle) : temp_treshold;
//                        if (angle >75) angle = 75;
//                        command = set_command(angle-5, ticks,  my_back, my_ahead, car_info,3);
                        double angletemp = ((double)ticks+70)/70;
                        double angle = 15*angletemp>45? 45 : 15*angletemp;
//                        command = set_command(35*angletemp>85? 85 : 35*angletemp, ticks,  my_back, my_ahead, car_info,0);

                        if(abs(enemy_info.x_ahead_wheel_car - car_info.x_back_wheel_car)<
                           abs(car_info.x_ahead_wheel_car - car_info.x_back_wheel_car))
                        {
                            if (car_info.is_left==1)
                                angle = enemy_info.x_ahead_wheel_car>car_info.x_ahead_wheel_car+10? 75 : 10;
                            else
                                angle = enemy_info.x_ahead_wheel_car>car_info.x_ahead_wheel_car+10? 10 : 75;
                        }
                        command = set_command(angle, ticks,  my_back, my_ahead, car_info,0);
                    }
                    else
                    if(car_info.type == BUS){
                        if (ticks<40)
                            command = set_command(85, ticks,  my_back, my_ahead, car_info,40);
                        else if (ticks>=40 && ticks<60)
                            command[COMMAND] = STOP;
                        else
                            command = set_command(65, ticks,  my_back, my_ahead, car_info,30);
                    }
                    else {
                        if((car_info.is_left==1 && car_info.x_ahead_wheel_car<900) ||
                           (car_info.is_left==-1 && car_info.x_ahead_wheel_car>200))
                            command = set_command(25, ticks, my_back, my_ahead, car_info, 0);
                        else command[COMMAND] = STOP;
                        //command = set_command(35, ticks, my_back, my_ahead, car_info, 30);
                    }

                }
                else if (type_of_map==PILL_HILL_MAP) {

                    if (car_info.type == BUGGY) {
                        int temp_ticks = 0;//100?
                        if (ticks < 50) {
                            command[COMMAND] = STOP;
                        } else if (ticks >= temp_ticks + 50 and ticks < temp_ticks + 120)
                            command[COMMAND] = my_back;
                        else if (ticks >= temp_ticks + 100 and ticks < temp_ticks + 130)
                            command[COMMAND] = my_ahead;
                        else if (ticks >= temp_ticks + 130 and ticks < temp_ticks + 160)
                            command[COMMAND] = STOP;
                        else if (ticks >= temp_ticks + 160 and ticks < temp_ticks + 190)
                            command = set_command(25, ticks, my_back, my_ahead, car_info, 0);
                        else if (car_info.type == BUGGY)
                            command = set_command(75, ticks, my_back, my_ahead, car_info, 0);
                    } else if (car_info.type == BUS) {
                        int temp_ticks = 200;//100?
                        if (ticks < temp_ticks) {
                            command[COMMAND] = STOP;
                        } else if (ticks < temp_ticks + 150)
                            command[COMMAND] = STOP;
                        else if (ticks >= temp_ticks + 150 && ticks < temp_ticks + 260)
                            command[COMMAND] = my_back;
                        else if (ticks >= temp_ticks + 260 && ticks < temp_ticks + 340)
                            command[COMMAND] = STOP;
//                        else if (ticks >= temp_ticks + 340 && ticks < temp_ticks + 405)
//                            command[COMMAND] = my_ahead;
//                        else if (ticks >= temp_ticks + 405 && ticks < temp_ticks + 480)
//                            command[COMMAND] = STOP;
                        else {
                            car_info.car_angle = grad_to_rad(
                                    360 - car_info.is_left * rad_to_grad(car_info.car_angle));
                            //cerr<<rad_to_grad(car_info.car_angle)<<endl;
                            set_command(65, ticks, my_back, my_ahead, car_info, 0);
                        }
                        // command[COMMAND] = ticks % 2 == 0 ? my_back : my_ahead;
                    } else {
                        command = set_command(65, ticks, my_back, my_ahead, car_info, 0);
                    }
                }
                else if (type_of_map==PILL_HUBBLE_MAP)
                {
                    double angletemp = ((double)ticks+101)/100;

                    if(car_info.x_ahead_wheel_car<enemy_info.x_ahead_wheel_car+50
                    and car_info.x_ahead_wheel_car>enemy_info.x_ahead_wheel_car-50
                    and enemy_info.y_ahead_wheel_car - car_info.y_ahead_wheel_car>100

                            )
                    {is_opponent_over_me = true;}
                    if(car_info.type == BUS) {
                        int temp_ticks = 0;
                        if (ticks < temp_ticks+30)
                            command[COMMAND] = STOP;
                        else if (ticks >= temp_ticks+30 && ticks < temp_ticks+155)
                            command[COMMAND] = my_back;
                        else if (ticks >= temp_ticks+155 && ticks < temp_ticks+250)
                        {
                            //cerr<< rad_to_grad(car_info.car_angle) << " = angle"<<endl;
                            command[COMMAND] = STOP;

                        } else if(ticks >= temp_ticks+250 && ticks < temp_ticks+285)
                        {
                            command[COMMAND] = my_ahead;
                        }
                        else if(is_opponent_over_me==false){
                            //cerr << 360 - car_info.is_left * rad_to_grad(car_info.car_angle) << " = angle" << endl;
                            car_info.car_angle = grad_to_rad(
                                    360 - car_info.is_left * rad_to_grad(car_info.car_angle));

                            command = set_command(75, ticks, my_back, my_ahead, car_info, 0);
                        }
                        else{
                            car_info.car_angle = grad_to_rad(
                                    360 - car_info.is_left * rad_to_grad(car_info.car_angle));
                            command = set_command(55, ticks, my_back, my_ahead, car_info, 0);
                        }
                    }
                    else if (car_info.type == BUGGY)
                    {
//                        if(ticks<100)
//                        {
//                            command = set_command(25 , ticks,  my_ahead, my_back, car_info,0);
//                        }
//                        else{
                            double angletemp2 = ((double)ticks+71)/70;
                            command = set_command(65/angletemp2>25?65/angletemp2:25 , ticks,  my_back, my_ahead, car_info,9);
                            if (ticks>650)
                                command = set_command(25 , ticks,   my_ahead,my_back, car_info,0);
                        //}
                    }
                    else command = set_command(65/angletemp>35?65/angletemp:35  , ticks,  my_back, my_ahead, car_info,0);
                    //TODO: стоит задуматься о возвращении
                }
                else
                {
                    if (car_info.type == BUS)
                    {
                        if( ticks>0 && ticks < 50)
                            command[COMMAND] = my_ahead;
                        else
                            command = set_command(80,ticks,  my_back, my_ahead, car_info,0);
                    }
                    else if (car_info.type == BUGGY){
                        if( ticks>0 && ticks < 20)
                            command[COMMAND] = my_ahead;
                        else if( ticks>=20 && ticks < 30)
                            command[COMMAND] = STOP;
                        else
                            command = set_command(40,ticks,  my_back, my_ahead, car_info,0);
                    }
                    else
                    {
                        if( ticks>0 && ticks < 50)
                            command[COMMAND] = my_ahead;
                        else
                            command = set_command(80,ticks,  my_back, my_ahead, car_info,0);
                    }
                }
                command["debug"] = command[COMMAND];
                cout << command.dump() <<endl;
            }
            catch(...) {
                command[COMMAND] = STOP;
                command["debug"] = "Something went wrong";
                cout << command.dump() << endl;
            }
        } else {
            break;
        }
        ticks++;
    }

    return 0;
}