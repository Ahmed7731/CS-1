/*
CS213 - Object Oriented Programming Assignment #1
-TEAM DETAILS:
Ahmed Mansour Khalaf (20240055)
Mohamed Mahmoud Ahmed (Doesn't have ID yet)
Yousef Mohamed Abdelhameed (20240709)
-WORK DIVISION:
Ahmed Mansour Khalaf (20240055): Menu+Filter5
Mohamed Mahmoud Ahmed (Doesn't have ID yet): Filter6+11
Yousef Mohamed Abdelhameed (20240709): Filter1+2+3
-SECTION: Registration hasn’t opened yet, but we will register for sections S5–S6. INSHALLAH
*/
#include <iostream>
#include "Image_Class.h"
using namespace std;

int main() {
    Image img;
    string fname;
    bool running = true;

    cout << "Enter image file name to load: ";
    cin >> fname;
    if (!img.loadNewImage(fname)) {
        cout << "Failed to load image.\n";
        return 1;
    }

    while (running) {
        cout << "\n---- Menu ----\n";
        cout << "1. Load a new image\n";
        cout << "2. Apply Gray Filter\n";
        cout << "3. Apply Black and White Filter\n";
        cout << "4. Apply Invert Colors Filter\n";
        cout << "5. Flip the image\n";
        cout << "6. Rotate the image\n";
        cout << "7. Resize the image\n";
        cout << "8. Save the image\n";
        cout << "9. Exit\n";
        cout << "Choose option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string Ans;
            cout << "Do you want to save the current image before loading a new one? (yes/no): ";
            cin >> Ans;
            if (Ans == "yes") {
                cout << "Enter filename to save (with extension .jpeg/ .jpg/ .png/ .bmp): ";
                string FileName;
                cin >> FileName;
                if (img.saveImage(FileName)) {
                    cout << "Image saved as: " << FileName << endl;
                }
                else {
                    cout << "Failed to save image.\n";
                }
            }
            cout << "Enter new image filename: ";
            cin >> fname;
            if (img.loadNewImage(fname)) {
                cout << "New image loaded.\n";
            }
            else {
                cout << "Failed to load new image.\n";
            }
            break;
        }

        case 2: {
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
            cout << "Gray filter applied.\n";
            break;
        }

        case 3: {
            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {
                    unsigned int average = 0;
                    for (int k = 0; k < img.channels; ++k) {
                        average += img(i, j, k);
                    }
                    average = average / img.channels;
                    int res = (average > 127) ? 255 : 0;
                    for (int k = 0; k < 3; ++k) {
                        img(i, j, k) = res;
                    }
                }
            }
            cout << "Black and white filter applied.\n";
            break;
        }

        case 4: {
            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {
                    for (int k = 0; k < img.channels; ++k) {
                        int oldValue = img(i, j, k);
                        int newValue = 255 - img(i, j, k);
                        img(i, j, k) = newValue;
                    }
                }
            }
            cout << "Invert colors filter applied.\n";
            break;
        }
        case 5: {
            cout << "Flip Options:\n";
            cout << "1. Horizontal Flip\n";
            cout << "2. Vertical Flip\n";
            int flipChoice;
            cin >> flipChoice;

            if (flipChoice == 1) {

                for (int i = 0; i < img.width / 2; ++i) {
                    for (int j = 0; j < img.height; ++j) {
                        for (int k = 0; k < img.channels; ++k) {
                            unsigned char left = img(i, j, k);
                            unsigned char right = img(img.width - 1 - i, j, k);
                            img(i, j, k) = right;
                            img(img.width - 1 - i, j, k) = left;
                        }
                    }
                }
                cout << "Image flipped horizontally.\n";
            }
            else if (flipChoice == 2) {
                for (int i = 0; i < img.width; ++i) {
                    for (int j = 0; j < img.height / 2; ++j) {
                        for (int k = 0; k < img.channels; ++k) {
                            unsigned char top = img(i, j, k);
                            unsigned char bottom = img(i, img.height - 1 - j, k);
                            img(i, j, k) = bottom;
                            img(i, img.height - 1 - j, k) = top;
                        }
                    }
                }
                cout << "Image flipped vertically.\n";
            }
            else {
                cout << "Invalid flip option.\n";
            }
            break;
        }
        case 6: {
            int angle;
            cout << "Enter an angle: ";
            cin >> angle;
            if (angle == 90) {
                Image newImage(img.height, img.width);
                for (int i = 0; i < img.height; i++) {
                    for (int j = 0; j < img.width; j++) {
                        for (int k = 0; k < 3; k++) {
                            newImage(i, j, k) = img(j, img.height - 1 - i, k);
                        }
                    }
                }
                img = newImage;
            }
            else if (angle == 180) {
                Image newImage(img.width, img.height);
                for (int i = 0; i < img.width; i++) {
                    for (int j = 0; j < img.height; j++) {
                        for (int k = 0; k < 3; k++) {
                            newImage(i, j, k) = img(img.width - 1 - i, img.height - 1 - j, k);
                        }
                    }
                }
                img = newImage;
            }
            else if (angle == 270) {
                Image newImage(img.height, img.width);
                for (int i = 0; i < img.height; i++) {
                    for (int j = 0; j < img.width; j++) {
                        for (int k = 0; k < 3; k++) {
                            newImage(i, j, k) = img(img.width - 1 - j, i, k);
                        }
                    }
                }
                img = newImage;
            }
            break;
        }
        case 7: {
            int choice;
            cout << "Choose resize method:\n";
            cout << "1. Enter Dimensions\n";
            cout << "2. Enter Ratio\n";
            cin >> choice;
            int new_width = 0, new_height = 0;
            int old_width = img.width;
            int old_height = img.height;

            if (choice == 1) {
                cout << "Enter Dimensions:\n";
                cin >> new_width >> new_height;
                cout << "Image resized to: " << new_width << "x" << new_height << ".";
            }
            else if (choice == 2) {
                int ratio_width, ratio_height;
                cout << "Enter Ratio:\n";
                cin >> ratio_width >> ratio_height;

                cout << "1. Keep Width\n";
                cout << "2. Keep Height\n";
                int preserve;
                cin >> preserve;

                if (preserve == 1) {
                    new_width = old_width;
                    new_height = (old_width * ratio_height) / ratio_width;
                }
                else if (preserve == 2) {
                    new_height = old_height;
                    new_width = (old_height * ratio_width) / ratio_height;
                }
                else {
                    cout << "Invalid Choice.";
                    break;
                }
                cout << "Image resized to: " << new_width << "x" << new_height
                    << " (aspect ratio " << ratio_width << ":" << ratio_height << ").\n";
            }
            else {
                cout << "Invalid resize option.\n";
            }

            Image image1(new_width, new_height);
            float X = (float)old_width / new_width;
            float Y = (float)old_height / new_height;

            for (int i = 0; i < new_width; i++) {
                for (int j = 0; j < new_height; j++) {
                    float W = i * X;
                    float H = j * Y;
                    for (int k = 0; k < 3; k++) {
                        image1(i, j, k) = img((int)round(W), (int)round(H), k);
                    }
                }
            }
            img = image1;
            break;
        }
        case 8: {
            cout << "Enter filename to save (with extension .jpeg/ .jpg/ .png/ .bmp): ";
            cin >> fname;
            if (img.saveImage(fname)) {
                cout << "Image saved as: " << fname << endl;
            }
            else {
                cout << "Failed to save image.\n";
            }
            break;
        }
        case 9: {
            string ans;
            cout << "Save current image before exit? (yes/no): ";
            cin >> ans;
            if (ans == "yes") {
                cout << "Enter filename to save (with extension .jpeg/ .jpg/ .png/ .bmp): ";
                cin >> fname;
                if (img.saveImage(fname)) {
                    cout << "Image saved as: " << fname << endl;
                }
                else {
                    cout << "Failed to save image.\n";
                }
            }
            running = false;
            break;
        }

        default:
            cout << " ERROR.\n";
        }
    }
    cout << " Program exited.\n";
    return 0;
}