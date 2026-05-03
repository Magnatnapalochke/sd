#include <iostream>
int plus(int x){
    return x+1;
}
int main(){
    int x = 0;
    while (x!=10){
        std::cout<<x<<"\n";
        plus(x);
    }
}