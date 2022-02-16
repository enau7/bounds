#pragma once

class Triangle{
    private:
        double points[3][2];

        bool intersects(int n, double point[2]);

    public:
        bool contains(double point[2]);
        bool contains(double x, double y){double point[2] = {x,y}; return contains(point);}

        void set(double coords[3][2]);
        void set(double x1, double y1, double x2, double y2, double x3, double y3){double coords[3][2] = {{x1,y1},{x2,y2},{x3,y3}}; set(coords);}

        Triangle(){};
        Triangle(double coords[3][2]){set(coords);};
        Triangle(double x1, double y1, double x2, double y2, double x3, double y3){set(x1,y1,x2,y2,x3,y3);};
        
};