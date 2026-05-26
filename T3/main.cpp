#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

struct Point{
    int x, y;
};

struct Polygon{
    std::vector< Point > points; 
};

std::istream& operator>>(std::istream& in, Point& point){
    char leftBr = 0;
    char semicolon = 0;
    char rightBr = 0;

    int x = 0;
    int y = 0;

    if(in >> leftBr >> x >> semicolon >> y >> rightBr){
        if(leftBr == '(' && semicolon == ';' && rightBr ==')'){
            point.x = x;
            point.y = y;
        }
        else{
            in.setstate(std::ios::failbit);
        }
    }
    return in;
}

std::istream& operator>>(std::istream& in, Polygon& poly){
    size_t n = 0;
    if(!(in >> n)){
        in.setstate(std::ios::failbit);
        return in;
    }

    std::vector< Point > points;
    points.reserve(n);

    std::copy_n(
        std::istream_iterator<Point>(in), 
        n,
        std::back_inserter(points)
    );

    if(!in || points.size() != n){
        in.setstate(std::ios::failbit);
        return in;
    }
    poly.points = std::move(points);
    return in;
}

std::vector<Polygon> readPolygons(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        std::cerr<<"Error: cannot open file: "<< filename << std::endl;
        return {};
    }

    std::vector<Polygon> result;
    std::string line;

    while(std::getline(file, line)){
        if(line.empty()) continue;
        std::istringstream iss(line);

        std::copy(
            std::istream_iterator<Polygon>(iss),
            std::istream_iterator<Polygon>(),
            std::back_inserter(result)
        );
    }

    return result;
}

bool isEvenVertexCount(const Polygon& p){
    return p.points.size() % 2 ==0;
}

bool isOddVertexCount(const Polygon& p){
    return p.points.size() % 2 !=0;
}



int main(int argc, char* argv[]){
    if(argc<2){
        std::cerr << "Error: file name missing\n";
        return 1;
    }

    std::string filename = argv[1];


}