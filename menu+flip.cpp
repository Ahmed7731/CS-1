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
        cout << "2. Flip the image\n";
        cout << "3. Save the image\n";
        cout << "4. Exit\n";
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
            cout << "Flip Options:\n";
            cout << "1. Horizontal flip\n";
            cout << "2. Vertical flip\n";
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
                cout << "Invalid flip option\n";
            }
            break;
        }

        case 3: {
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
        case 4: {
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