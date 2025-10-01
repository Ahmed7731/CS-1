#include "image_class.h"
//Filter gray
int main() {
    Image img("messi-world-cup.jpg");
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int average = 0;
            for (int k = 0; k < img.channels; ++k) {
                average += img(i, j, k);
            }
            average = average / img.channels;
            for (int k = 0; k < 3; ++k) {
                img(i, j, k) = average;
            }
        }
    }
    img.saveImage("img_gray.png");
    return 0;
}
//Filter Black and White
int main(){
    Image img("messi-world-cup.jpg");
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int average = 0;
            for (int k = 0; k < img.channels; ++k) {
                average += img(i, j, k);
            }
            average = average / img.channels;
            int res=(average>127)?255:0;
            for (int k = 0; k < 3; ++k) {
                img(i, j, k) = res;
            }
        }
    }
    img.saveImage("img_black-white.png");
    return 0;
}
//filter inverse image
int main(){
    Image img("messi-world-cup.jpg");
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                int oldValue=img(i,j,k);
                int newValue=255-img(i,j,k);
                img(i,j,k)=newValue;
            }
        }
    }
    img.saveImage("img_inverse.png");
    return 0;
}
