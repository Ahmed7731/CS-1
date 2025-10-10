/*
Faculty of Computing and AI Cairo University (FCAI-CU)
CS213 - Object Oriented Programming Assignment #1
-TEAM DETAILS:
Ahmed Mansour Khalaf (20240055) (S3)
Mohamed Mahmoud Ahmed (No ID) (Transfer Student)
Yousef Mohamed Abdelhameed (20240709) (All-A)
-WORK DIVISION:
Ahmed Mansour Khalaf (20240055): Menu+Filter5+8+9
Mohamed Mahmoud Ahmed (No ID): Filter4+6+11+12
Yousef Mohamed Abdelhameed (20240709): Filter1+2+3+7+10
-BONUS FILTERS:
Ahmed Mansour Khalaf (20240055): Filter 13
Yousef Mohamed Abdelhameed (20240709): Filter 16
-Shared doc: https://docs.google.com/document/d/1uvxse6stpkpei_wYETE1MZdnvvAEyDyBX86jwP0Ypcg/edit?usp=sharing
-Explaining video on drive: https://drive.google.com/file/d/1gsGo035YuTu7qQzVJsfNAHneLIWwtf5k/view?usp=drive_link
*/
#include <iostream>
#include <cmath>
#include <vector>
#include "Image_Class.h"
using namespace std;

void Resize(Image& img, int new_width, int new_height) {
    int old_width = img.width;
    int old_height = img.height;
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
}
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
        cout << "\n----------------------------------------------------------------------------------------\n";
        cout << "\n---- Menu ----\n";
        cout << "1. Load a new image\n";
        cout << "2. Apply Gray Filter\n";                 // Filter 1
        cout << "3. Apply Black and White Filter\n";      // Filter 2
        cout << "4. Apply Invert Colors Filter\n";        // Filter 3 
        cout << "5. Flip the image\n";                    // Filter 5
        cout << "6. Rotate the image\n";                  // Filter 6
        cout << "7. Resize the image\n";                  // Filter 11
        cout << "8. Darken the image by 50%\n";           // Filter 7
        cout << "9. Lighten the image by 50%\n";          // Filter 7
        cout << "10. Crop the image\n";                   // Filter 8
        cout << "11. Adding frame to the image\n";        // Filter 9
        cout << "12. Detect image edges\n";               // Filter 10
        cout << "13. Apply blur filter\n";                // Filter 12
        cout << "14. Merge two images\n";                 // Filter 4
        cout << "15. Apply sunlight filter\n";            // Filter 13
        cout << "16. Apply purple filter\n";              // Filter 16
        cout << "17. Save the image\n";
        cout << "18. Exit\n";
        cout << "Choose option: ";
        int choice;
        cin >> choice;
        cout << "\n";
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
            cout << "Enter your choice: ";
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
            cout << "Choose rotation angle:\n";
            cout << "1. 90 degree\n";
            cout << "2. 180 degree\n";
            cout << "3. 270 degree\n";
            cout << "Enter your choice: ";
            cin >> angle;
            if (angle == 1) {
                Image newImage(img.height, img.width);
                for (int i = 0; i < img.height; i++) {
                    for (int j = 0; j < img.width; j++) {
                        for (int k = 0; k < 3; k++) {
                            newImage(i, j, k) = img(j, img.height - 1 - i, k);
                        }
                    }
                }
                img = newImage;
                cout << "Image rotated by 90 degrees.\n";
            }
            else if (angle == 2) {
                Image newImage(img.width, img.height);
                for (int i = 0; i < img.width; i++) {
                    for (int j = 0; j < img.height; j++) {
                        for (int k = 0; k < 3; k++) {
                            newImage(i, j, k) = img(img.width - 1 - i, img.height - 1 - j, k);
                        }
                    }
                }
                img = newImage;
                cout << "Image rotated by 180 degrees.\n";
            }
            else if (angle == 3) {
                Image newImage(img.height, img.width);
                for (int i = 0; i < img.height; i++) {
                    for (int j = 0; j < img.width; j++) {
                        for (int k = 0; k < 3; k++) {
                            newImage(i, j, k) = img(img.width - 1 - j, i, k);
                        }
                    }
                }
                img = newImage;
                cout << "Image rotated by 270 degrees.\n";
            }
            break;
        }
        case 7: {
            int choice;
            cout << "Choose resize method:\n";
            cout << "1. Enter Dimensions\n";
            cout << "2. Enter Ratio\n";
            cout << "Enter your choice: ";
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
                    cout << "Invalid Choice.\n";
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
            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {
                    for (int k = 0; k < img.channels; ++k) {
                        int value = img(i, j, k);
                        value = value * 0.5;
                        img(i, j, k) = value;
                    }
                }
            }
            cout << "Image is darkened by 50%.\n";
            break;
        }
        case 9: {
            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {
                    for (int k = 0; k < img.channels; ++k) {
                        int value = img(i, j, k);
                        value = value * 1.5;
                        value = min(255, value);
                        img(i, j, k) = value;
                    }
                }
            }
            cout << "Image is lightened by 50%.\n";
            break;
        }
        case 10: {
            int x, y, newW, newH;
            cout << "Enter starting point (x,y):\n";
            cin >> x >> y;
            cout << "Enter the new dimensions to crop (W , H):\n";
            cin >> newW >> newH;

            if (x < 0 || y < 0 || newW <= 0 || newH <= 0 ||
                x + newW > img.width || y + newH > img.height) {
                cout << "Invalid crop area.\n";
                break;
            }
            Image cropped(newW, newH);

            for (int i = 0; i < newW; i++) {
                for (int j = 0; j < newH; j++) {
                    for (int k = 0; k < img.channels; k++) {
                        cropped(i, j, k) = img(i + x, j + y, k);
                    }
                }
            }

            img = cropped;
            cout << "Image cropped to " << newW << "x" << newH << " from point (" << x << " , " << y << ").\n";

            break;
        }
        case 11: {
            int thickness;
            cout << "Enter frame thickness: ";
            cin >> thickness;

            if (thickness <= 0) {
                cout << "Invalid thickness.\n";
                break;
            }
            int r = 255, g = 255, b = 255;
            cout << "Choose the colour of the frame:\n";
            cout << "1. White\n";
            cout << "2. Black\n";
            cout << "3. Red\n";
            cout << "4. Green\n";
            cout << "5. Blue\n";
            cout << "Enter your choice: ";
            int Choice;
            cin >> Choice;

            switch (Choice) {
            case 1:
                r = g = b = 255;
                break;
            case 2:
                r = g = b = 0;
                break;
            case 3:
                r = 255; g = 0; b = 0;
                break;
            case 4:
                r = 0; g = 255; b = 0;
                break;
            case 5:
                r = 0; g = 0; b = 255;
                break;
            default:
                cout << "Invalid color choice.\n";
                break;
            }
            for (int i = 0; i < img.width; i++) {
                for (int j = 0; j < img.height; j++) {
                    if (i < thickness || i >= img.width - thickness || j < thickness || j >= img.height - thickness) {
                        img(i, j, 0) = r;
                        img(i, j, 1) = g;
                        img(i, j, 2) = b;
                    }
                }
            }
            cout << "Frame added.\n";
            break;
        }
        case 12: {
            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {
                    unsigned int avg = 0;
                    for (int c = 0; c < 3; ++c) {
                        avg += img(i, j, c);
                    }
                    avg /= 3;
                    for (int c = 0; c < 3; ++c) {
                        img(i, j, c) = avg;
                    }
                }
            }
            Image edge(img.width, img.height);
            for (int x = 1; x < img.width - 1; ++x) {
                for (int y = 1; y < img.height - 1; ++y) {

                    int gx = 0, gy = 0;

                    gx = -img(x - 1, y - 1, 0) + img(x + 1, y - 1, 0)
                        - 2 * img(x - 1, y, 0) + 2 * img(x + 1, y, 0)
                        - img(x - 1, y + 1, 0) + img(x + 1, y + 1, 0);

                    gy = -img(x - 1, y - 1, 0) - 2 * img(x, y - 1, 0) - img(x + 1, y - 1, 0)
                        + img(x - 1, y + 1, 0) + 2 * img(x, y + 1, 0) + img(x + 1, y + 1, 0);


                    int magnitude = sqrt(gx * gx + gy * gy);

                    magnitude = min(255, magnitude);
                    magnitude = 255 - magnitude;
                    for (int c = 0; c < 3; ++c) {
                        edge(x, y, c) = magnitude;
                    }
                }
            }
            img = edge;
            cout << "Image edges detected.";
            break;
        }
        case 13: {
            Image New(img.width, img.height);
            vector<vector<vector<long long>>> prefix(img.width + 1, vector<vector<long long>>(img.height + 1, vector<long long>(3, 0)));
            for (int i = 1; i <= img.width; i++) { // 2d-prefix , rows
                for (int j = 1; j <= img.height; j++) {
                    for (int c = 0; c < 3; c++) {
                        prefix[i][j][c] = img(i - 1, j - 1, c) + prefix[i][j - 1][c];
                    }
                }
            }
            for (int j = 1; j <= img.height; j++) { // columns
                for (int i = 1; i <= img.width; i++) {
                    for (int c = 0; c < 3; c++) {
                        prefix[i][j][c] += prefix[i - 1][j][c];
                    }
                }
            }
            int radius = 25;
            // Kernel Convolution  51 * 51
            // box blur
            int w1, w2, h1, h2;
            for (int x = 0; x < img.width; x++) {
                for (int y = 0; y < img.height; y++) {
                    if (x - radius < 0) w1 = 0;
                    else w1 = x - radius;
                    if (y - radius < 0) h1 = 0;
                    else h1 = y - radius;
                    if (x + radius >= img.width) w2 = img.width - 1;
                    else w2 = x + radius;
                    if (y + radius >= img.height) h2 = img.height - 1;
                    else h2 = y + radius;
                    w1++; h1++; w2++; h2++; // perfix 1-based
                    int area = (w2 - w1 + 1) * (h2 - h1 + 1);
                    for (int c = 0; c < 3; c++) {
                        long long sum = prefix[w2][h2][c] - (prefix[w1 - 1][h2][c] - prefix[w1 - 1][h1 - 1][c]) - prefix[w2][h1 - 1][c];
                        New(x, y, c) = sum / area;
                    }
                }
            }
            img = New;
            cout << "Blur filter applied.\n";
            break;
        }
        case 14: {
            string image_name;
            Image img_1;
            cout << "Load second image\n";
            cout << "Enter new image name: ";
            cin >> image_name;
            if (img_1.loadNewImage(image_name)) {
                cout << "New image loaded.\n";
            }
            else {
                cout << "Failed to load new image.\n";
                break;
            }
            int choice;
            cout << "Choose method:\n";
            cout << "1. Resize and merge\n";
            cout << "2. Merge overlap\n";
            cout << "Enter your choice: ";
            cin >> choice;
            int New_width, New_height;
            if (choice == 1) {
                int tutorial;
                cout << "Choose an option:\n";
                cout << "1. Resize the smaller image\n";
                cout << "2. Resize both images To the biggest W & H\n";
                cout << "Enter your choice: ";
                cin >> tutorial;
                if (tutorial == 1) {
                    int photo_one = img.height * img.width;
                    int photo_two = img_1.height * img_1.width;
                    if (photo_one > photo_two) {
                        Resize(img_1, img.width, img.height);
                    }
                    else if (photo_one < photo_two) {
                        Resize(img, img_1.width, img_1.height);
                    }
                    New_width = img.width, New_height = img.height;
                }
                else if (tutorial == 2) {
                    int Biggest_width = max(img.width, img_1.width);
                    int Biggest_height = max(img.height, img_1.height);
                    Resize(img, Biggest_width, Biggest_height);
                    Resize(img_1, Biggest_width, Biggest_height);
                    New_width = Biggest_width, New_height = Biggest_height;
                }
            }
            else if (choice == 2) {
                int smaller_width = min(img.width, img_1.width);
                int smaller_height = min(img.height, img_1.height);
                New_width = smaller_width, New_height = smaller_height;
            }
            Image answer(New_width, New_height);
            for (int i = 0; i < New_width; i++) {
                for (int j = 0; j < New_height; j++) {
                    for (int k = 0; k < 3; k++) {
                        answer(i, j, k) = (img(i, j, k) + img_1(i, j, k)) / 2;
                    }
                }
            }
            img = answer;
            cout << "The two images merged successfully.\n";
            break;
        }
        case 15: {
            for (int y = 0; y < img.height; y++) {
                for (int x = 0; x < img.width; x++) {
                    img(x, y, 0) = min(255, img(x, y, 0) + 40);
                    img(x, y, 1) = min(255, img(x, y, 1) + 40);
                    img(x, y, 2) = max(0, img(x, y, 2) - 20);
                }
            }
            cout << "Sunlight filter applied.\n";
            break;
        }
        case 16: {
            for (int i = 0; i < img.width; ++i) {
                for (int j = 0; j < img.height; ++j) {
                    for (int k = 0; k < img.channels; ++k) {
                        int r = img(i, j, 0);
                        int g = img(i, j, 1);
                        int b = img(i, j, 2);
                        r = min(255, int(r * 1.01));
                        b = min(255, int(b * 1.08));
                        g = max(0, int(g * 0.9));
                        img(i, j, 0) = r;
                        img(i, j, 1) = g;
                        img(i, j, 2) = b;
                    }
                }
            }
            cout << "Purple filter applied.";
            break;
        }
        case 17: {
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
        case 18: {
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
            cout << "ERROR!\n";
        }
    }
    cout << "Program exited.\n";
    return 0;
}
