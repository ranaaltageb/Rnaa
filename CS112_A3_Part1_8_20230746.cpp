//Assignment 3 filters making
//Name: Rana Al-tayeb al-hag
// ID: 20230746
//filters 3 and 6
//section 8

#include "Image_Class.h"
#include <iostream>
#include "Image_Class.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void invertImage(Image& image) {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    Image i(filename);

    for (int l = 0; l < i.width; ++l) {
        for (int k = 0; k < i.height; ++k) {
            for (int j = 0; j < i.channels; ++j) {
                i(l, k, j) = 255 - i(l, k, j);
            }
        }
    }

    string new_filename;
    cout << "Enter new file name: ";
    cin >> new_filename;

    i.saveImage(new_filename);
}



// Function to check if a file exists
bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Function to rotate the image by 90 degrees clockwise

void rotateImage90(Image& img) {
    std::vector<std::vector<std::vector<unsigned char>>> rotatedPixels(img.width, std::vector<std::vector<unsigned char>>(img.height, std::vector<unsigned char>(3)));

    // Loop through each pixel in the original image and rotate it
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            // Rotate the pixel and store it in the rotated image
            rotatedPixels[i][j][0] = img.getPixel(j, img.width - i - 1, 0);
            rotatedPixels[i][j][1] = img.getPixel(j, img.width - i - 1, 1);
            rotatedPixels[i][j][2] = img.getPixel(j, img.width - i - 1, 2);
        }
    }

    // Update image dimensions and imageData with the rotated pixels
    img.width = rotatedPixels.size();
    img.height = rotatedPixels[0].size();
    img.imageData = reinterpret_cast<unsigned char*>(rotatedPixels.data());
}

// Function to rotate the image by 180 degrees
void rotateImage180(Image& img) {
    std::vector<std::vector<std::vector<unsigned char>>> rotatedPixels(img.height, std::vector<std::vector<unsigned char>>(img.width, std::vector<unsigned char>(3)));

    // Loop through each pixel in the original image and rotate it
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            // Rotate the pixel and store it in the rotated image
            rotatedPixels[j][i][0] = img.getPixel(img.width - i - 1, img.height - j - 1, 0);
            rotatedPixels[j][i][1] = img.getPixel(img.width - i - 1, img.height - j - 1, 1);
            rotatedPixels[j][i][2] = img.getPixel(img.width - i - 1, img.height - j - 1, 2);
        }
    }

    // Update imageData with the rotated pixels
    img.imageData = reinterpret_cast<unsigned char*>(rotatedPixels.data());
}

// Function to rotate the image by 270 degrees clockwise
void rotateImage270(Image& img) {
    std::vector<std::vector<std::vector<unsigned char>>> rotatedPixels(img.width, std::vector<std::vector<unsigned char>>(img.height, std::vector<unsigned char>(3)));

    // Loop through each pixel in the original image and rotate it
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            // Rotate the pixel and store it in the rotated image
            rotatedPixels[i][j][0] = img.getPixel(img.height - j - 1, i, 0);
            rotatedPixels[i][j][1] = img.getPixel(img.height - j - 1, i, 1);
            rotatedPixels[i][j][2] = img.getPixel(img.height - j - 1, i, 2);
        }
    }

    // Update image dimensions and imageData with the rotated pixels
    img.width = rotatedPixels.size();
    img.height = rotatedPixels[0].size();
    img.imageData = reinterpret_cast<unsigned char*>(rotatedPixels.data());
}

int main() {

    char choise;
    cin >> choise;
    if (choise == 'a'){
        Image image;
        invertImage(image);
    }
    if (choise == 'b'){
        std::cout << "Welcome! This program rotates an image by 90, 180, and 270 degrees." << std::endl;

        std::string dirPath = "additional_images/";
        std::string filename;

        std::cout << "Enter the filename of the image: ";
        std::cin >> filename;

        // Check if the image file exists
        if (!fileExists(dirPath + filename)) {
            std::cout << "Error: The specified file does not exist." << std::endl;
            return 1;
        }

        Image img(dirPath + filename);
    }
    return 0;
    }


