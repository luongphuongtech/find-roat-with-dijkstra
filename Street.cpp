#include<bits/stdc++.h>
#pragma once
using namespace std;
class Street  // lớp định nghĩa một con đường với các thuộc tính
{
 public:                               //   pair là một kiểu dữ liệu, nó cho phép lưu trữ hai giá trị cùng một lúc
    pair<char, pair<char, double>> name; //   pair<'A', pair<'B', 2.5>> = con đường bat dau tai A và ket thuc tai B => AB=2.5;
    int maxspeed; // Toc do cho phep
    int numLanes; // So lan xe
    
    Street(pair<char, pair<char, double>> name, int maxspeed, int numLanes) // Hàm khởi tạo
    {
        this->name = name; 
        this->maxspeed = maxspeed;
        this->numLanes = numLanes;
    }
    int Check(); // Hàm kiểm tra loại đường
    void Print(); // Hàm in thông tin đường
};
    int Street::Check()
    {
        if (Street::maxspeed <= 40) return 1; // 1 tương ứng với đường phổ thông
        if (Street::maxspeed > 40 && maxspeed <= 80) return 2; // 2 tương ứng với đường quốc lộ
        if (Street::maxspeed > 80) return 3; // 3 tương ứng với đường cao tốc
    }
    void Street::Print() 
    {
        cout << "     Street names: " << Street::name.first <<name.second.first << endl;
        cout << "     Street length: " << Street::name.second.second << "Km" << endl;
        cout << "     Maximum speed allowed: " << Street::maxspeed << "(km/h)" << endl;
        cout << "     Number of motor vehicle lanes: " << Street::numLanes << endl;
        
        switch (Check())
        {
            case 1:
                cout << "     Street Type: General " << endl;
                break;
            case 2:
                cout << "     Street Type: National Highway" << endl;
                break;
            case 3:
                cout << "     Street Type: Expressway" << endl;
                cout << "     Attention: Only for cars" << endl;
                break;
            default:
                break;
        }
    }