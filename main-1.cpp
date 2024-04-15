#include "Image_Class.h"
#include <iostream>
#include <string>
using namespace std;

void addframe() {
  string filename;
  char choice;
  cout << "Do you want to create a simple frame? (Y/N) ";
  cin >> choice;
  if (tolower(choice) == 'y') {
    cout << "Enter the filename for the frame: ";
    cin >> filename;
    Image image(filename);
    int frameThickness = image.width / 10;
    Image frame(image.width + 2 * frameThickness,
                image.height + 2 * frameThickness);
    for (int i = 0; i < frame.width; ++i) {
      for (int j = 0; j < frame.height; ++j) {
        for (int k = 0; k < frame.channels; ++k) {
          frame(i, j, k) = 0;
        }
      }
    }
    for (int i = frameThickness; i < frameThickness + image.width; ++i) {
      for (int j = frameThickness; j < frameThickness + image.height; ++j) {
        for (int k = 0; k < frame.channels; ++k) {
          frame(i, j, k) = image(i - frameThickness, j - frameThickness, k);
        }
      }
    }
    cout << "Frame created successfully!" << endl;

    cout << "please enter the save name" << endl;
    cin >> filename;
    frame.saveImage(filename);
    cout << "image saved successfully!" << endl;
  } else if (tolower(choice) == 'n') {
    cout << "No frame created." << endl;
  } else {
    cout << "Invalid choice." << endl;
  }
}

int main() {
  addframe();
  return 0;
}
