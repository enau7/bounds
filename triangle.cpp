#include "triangle.h"
#include <iostream>
using namespace std;

void Triangle::set(double coords[3][2]){
    for (int k = 0; k < 3; k++){
        for (int j = 0; j < 2; j++){
            points[k][j] = coords[k][j];
        }
    }
}

bool Triangle::intersects(int n, double point[2]){
    
    // Line AB represented as a1x + b1y = c1
    double a1 = points[(n+2) % 3][1] - points[(n+1) % 3][1];
    double b1 = points[(n+1) % 3][0] - points[(n+2) % 3][0];
    double c1 = a1*(points[(n+1) % 3][0]) + b1*(points[(n+1) % 3][1]);
  
    // Line CD represented as a2x + b2y = c2
    double a2 = point[1] - points[n][1];
    double b2 = points[n][0] - point[0];
    double c2 = a2*(points[n][0])+ b2*(points[n][1]);
  
    double determinant = a1*b2 - a2*b1;
  
    if (determinant == 0)
    {
        // The lines are parallel
        return false;
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        // cout << x << ", " << y << " det: " << determinant << endl;
        // cout << "Pn: " << points[n][0] << ", " << points[n][1] << endl;
        // cout << "P: " << point[0] << ", " << point[1] << endl;

        double error = 1e-10;
        int count = 0;

        if ((((x - error) < points[n][0]) && ((x - error) < point[0])) ||
            (((x + error) > points[n][0]) && ((x + error) > point[0]))) {
                count++;
        };
        
        if ((((y - error) < points[n][1]) && ((y - error) < point[1])) ||
            (((y + error) > points[n][1]) && ((y + error) > point[1]))) {
                count++;
        };
        if (count == 2) {return false;};
        return true;
    }
}

bool Triangle::contains(double point[2]){
    bool prod = 1;
    for (int k = 0; k < 3; k++){
        prod = prod * !intersects(k,point);
        // cout << "prod: " << prod << endl;
    }
    return prod;
}