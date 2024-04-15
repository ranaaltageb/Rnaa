//Assignment 3 make filters
//Name: Afraa Mohammed Abufatima
// ID: 20230721
//filters 1 and 7
//section 8


#include "image_class.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace std;

// Function to darken the image.
void darkenImage(Image& image) {
    for (int x = 0; x < image.width; ++x) {
        for (int y = 0; y < image.height; ++y) {
            for (int a = 0; a < 3; ++a) {
                // Reduce each color channel by 50% (make it darker)
                image(x, y, a) *= 0.5;
            }
        }
    }
}

// Function to lighten the image
void lightenImage(Image& image) {
    for (int x = 0; x < image.width; ++x) {
        for (int y = 0; y < image.height; ++y) {
            for (int a = 0; a < 3; ++a) {
                // Increase each color channel by 50% (make it lighter)
                int newValue = image(x, y, a) * 1.5; 
                if (newValue > 255)
                    newValue = 255;
                image(x, y, a) = newValue;
            }
        }
    }
}

void grayScale() {
    string filename;
    cout << "Please enter the name of the colored image to convert to grayscale: ";
    cin >> filename;

    // Load the colored image
    Image image(filename);

    // Iterate through each pixel of the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0; // Initialize average value

            // Calculate the average of pixel values across all channels
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value to convert to grayscale
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = avg;
            }
        }
    }

    // Save the grayscale image
    string newFilename;
    cout << "Please enter the name of the new image to save (with extension .jpg, .bmp, .png, .tga): ";
    cin >> newFilename;
    // Save the modified image
    image.saveImage(newFilename);
    system(newFilename.c_str()); // Open the saved image
}




//invert _ rana
void Invert (){
    string filename;
    cout << "Please enter the filename of the colored image to invert: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Invert each color channel value
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }

    cout << "Please enter the filename to save the new inverted image (with extension .jpg, .bmp, .png, .tga): ";
    cin >> filename;

    image.saveImage(filename);
}



// Merge - afraa

void resizeImage(Image& image, int width, int height) {
    // Create a new image with the desired dimensions
    Image resizedImage(width, height);

    // Calculate scaling factors
    float scaleX = static_cast<float>(image.width) / width;
    float scaleY = static_cast<float>(image.height) / height;

    // Resize the image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                // Calculate source pixel coordinates
                int srcX = static_cast<int>(x * scaleX);
                int srcY = static_cast<int>(y * scaleY);

                // Copy pixel value from the source image
                resizedImage(x, y, c) = image(srcX, srcY, c);
            }
        }
    }

    // Replace the original image with the resized image
    image = resizedImage;
}

// Function to merge two images
void mergeImages(Image& imageOne, Image& imageTwo) {
    // Calculate dimensions of the merged image
    int maxWidth = max(imageOne.width, imageTwo.width);
    int maxHeight = max(imageOne.height, imageTwo.height);

    // Resize the smaller image to match the dimensions of the larger one
    if (imageOne.width < maxWidth || imageOne.height < maxHeight) {
        resizeImage(imageOne, maxWidth, maxHeight);
    }
    if (imageTwo.width < maxWidth || imageTwo.height < maxHeight) {
        resizeImage(imageTwo, maxWidth, maxHeight);
    }

    // Merge images
    for (int y = 0; y < maxHeight; ++y) {
        for (int x = 0; x < maxWidth; ++x) {
            for (int c = 0; c < imageOne.channels; ++c) {
                // Blend pixel values from both images using weighted averages
                float blendedValue = (imageOne(x, y, c) + imageTwo(x, y, c)) / 2.0f;
                imageOne(x, y, c) = static_cast<unsigned char>(blendedValue);
            }
        }
    }
}



void ResizeImage(Image& image, int width, int height) {

}
// Function to merge two images
void MergeImages(Image& imageOne, Image& imageTwo) {
    // Check if images have the same dimensions
    if (imageOne.width != imageTwo.width || imageOne.height != imageTwo.height) {
        cout << "ERORR!!, Images have different dimensions. Resizing image two..." << endl;

        // Resize overlay image to match dimensions of base image
        ResizeImage(imageTwo, imageOne.width, imageOne.height);
    }

    // Merge images
    for (int a = 0; a < imageOne.width; ++a) {
        for (int b = 0; b < imageOne.height; ++b) {
            for (int c = 0; c < imageOne.channels; ++c) {
                // Combine pixel values from both images (e.g., take an average)
                imageOne(a, b, c) = (imageOne(a, b, c) + imageTwo(a, b, c)) / 2;
            }
        }
    }
}


//flip - afraa

void Flip (){
    string filename;
    cout << "Please enter the filename of the colored image to flip: ";
    cin >> filename;

    Image image(filename);

    cout << "Please choose the flip operation:\n";
    cout << "1. Horizontal Flip\n";
    cout << "2. Vertical Flip\n";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: 
            for (int i = 0; i < image.width / 2; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        // Swap pixels horizontally
                        swap(image(i, j, k), image(image.width - 1 - i, j, k));
                    }
                }
            }
            break;
        case 2: 
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height / 2; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        swap(image(i, j, k), image(i, image.height - 1 - j, k));
                    }
                }
            }
            break;
        default:
            cout << "Invalid choice. Exiting.\n";
            
    }

    cout << "Please enter the filename to save the new flipped image (with extension .jpg, .bmp, .png, .tga): ";
    cin >> filename;

    image.saveImage(filename);
}

//black&white - afraa

void blackAndWhite(){
    string filename;
    cout << "Please enter the filename of the colored image to convert to black and white: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0; 

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); 
            }

            avg /= 3; 

            if (avg > 127) { 
                image(i, j, 0) = 255;
                image(i, j, 1) = 255;
                image(i, j, 2) = 255;
            } else {
                // Set all channels to black
                image(i, j, 0) = 0;
                image(i, j, 1) = 0;
                image(i, j, 2) = 0;
            }
        }
    }

    cout << "Please enter the filename to save the new black and white image (with extension .jpg, .bmp, .png, .tga): ";
    cin >> filename;

    image.saveImage(filename);

}


//Detect Image Edges - afraa

Image processImage(const string& filename) {
    // Load the input image
    Image image(filename); 

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0; 
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); 
            }
            avg /= 3; 
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }

    Image edges(image.width, image.height); 

    for (int i = 1; i < image.width - 1; ++i) {
        for (int j = 1; j < image.height - 1; ++j) {
            int gx = (image(i + 1, j - 1, 0) + 2 * image(i + 1, j, 0) + image(i + 1, j + 1, 0)) -
                     (image(i - 1, j - 1, 0) + 2 * image(i - 1, j, 0) + image(i - 1, j + 1, 0));
            int gy = (image(i - 1, j + 1, 0) + 2 * image(i, j + 1, 0) + image(i + 1, j + 1, 0)) -
                     (image(i - 1, j - 1, 0) + 2 * image(i, j - 1, 0) + image(i + 1, j - 1, 0));

            int magnitude = sqrt(gx * gx + gy * gy);

            magnitude = 255 - magnitude;

            if (magnitude < 100) {
                magnitude = magnitude / 2;
            }

            edges(i, j, 0) = magnitude;
            edges(i, j, 1) = magnitude;
            edges(i, j, 2) = magnitude;
        }
    }

    return edges;
}

//blur - afraa
void boxBlur(Image& img, unsigned int kernelSize) {
    if (kernelSize % 2 == 0) {
        cerr << "Invalid kernel size. Kernel size must be odd." << endl;
        return;
    }

    if (kernelSize < 3) {
        cerr << "Invalid kernel size. Kernel size must be at least 3." << endl;
        return;
    }

    unsigned int halfKernel = kernelSize / 2;
    unsigned int kernelArea = kernelSize * kernelSize;

    Image temp(img.width, img.height);

    for (unsigned int y = 0; y < img.height; ++y) {
        for (unsigned int x = 0; x < img.width; ++x) {
            unsigned int sumRed = 0;
            unsigned int sumGreen = 0;
            unsigned int sumBlue = 0;

            for (int ky = -halfKernel; ky <= static_cast<int>(halfKernel); ++ky) {
                for (int kx = -halfKernel; kx <= static_cast<int>(halfKernel); ++kx) {
                    int px = x + kx;
                    int py = y + ky;

                    if (px >= 0 && px < static_cast<int>(img.width) && py >= 0 && py < static_cast<int>(img.height)) {
                        sumRed += img(px, py, 0);
                        sumGreen += img(px, py, 1);
                        sumBlue += img(px, py, 2);
                    }
                }
            }

            unsigned int avgRed = sumRed / kernelArea;
            unsigned int avgGreen = sumGreen / kernelArea;
            unsigned int avgBlue = sumBlue / kernelArea;

            temp(x, y, 0) = avgRed;
            temp(x, y, 1) = avgGreen;
            temp(x, y, 2) = avgBlue;
        }
    }

    img = temp;
}




int main() {
    int choice;
    cout << "Enter 1 to apply dark and light filter, 2 to convert to grayscale: ";
    cin >> choice;

    if (choice == 1) {
        grayScale();
        
    } else if (choice == 2) {
        blackAndWhite();
    }

    if (choice == 3) {
        Invert();
    }

    if (choice == 4 ){
        cout << "Select merge option:" << endl;
        cout << "1. Resize both images to the largest size and merge." << endl;
        cout << "2. Merge the common area of the smaller width and the smaller height." << endl;
        
        int choise ;
        cin >> choise;
        if (choise == 1){
            string imageOneFilename;
            cout << "Enter the filename of the first image: ";
            cin >> imageOneFilename;
            Image imageOne(imageOneFilename);

            string imageTwoFilename;
            cout << "Enter the filename of the second image: ";
            cin >> imageTwoFilename;
            Image imageTwo(imageTwoFilename);

            mergeImages(imageOne, imageTwo);

            string filename;
            cout << "Please enter the name of the file to store the modified image" << endl;
            cout << "and specify the extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            imageOne.saveImage(filename);
            system(filename.c_str());

        }

        if (choise == 2){
                string imageOneFilename;
                cout << "Enter the filename of the first image: ";
                cin >> imageOneFilename;
                Image imageOne(imageOneFilename);

                string imageTwoFilename;
                cout << "Enter the filename of the second image: ";
                cin >> imageTwoFilename;
                Image imageTwo(imageTwoFilename);

                MergeImages(imageOne, imageTwo);

                string filename;
                cout << "Please enter the name of the file to store the modified image\n";
                cout << "and specify the extension (.jpg, .bmp, .png, .tga): ";
                cin >> filename;
                imageOne.saveImage(filename);
                system(filename.c_str());


        }
        
    }

    if (choice == 5){
        Flip();
    }

    if (choice == 6){

    }


    if (choice ==7){
        string filename;
        cout << "Please enter the name of the image file to apply the filter: ";
        cin >> filename;

        Image image(filename);

        // Ask user for operation choice
        char operation;
        cout << "Do you want to darken (d) or lighten (l) the image? ";
        cin >> operation;

        // Apply the selected operation
        if (operation == 'd') {
            darkenImage(image);
        } else if (operation == 'l') {
            lightenImage(image);
        } else {
            cout << "Invalid choice!!";
            return 1;
        }

        // Save the modified image
        string outputFilename;
        cout << "Please enter the name of the file to store the modified image (with extension .jpg, .bmp, .png, .tga): ";
        cin >> outputFilename;
        image.saveImage(outputFilename);
        system(outputFilename.c_str()); 
        
    }
    else if (choice == 8)
    {
        
    }

    else if(choice == 9){

    }
    
    else if(choice == 10){
        string filename;
        cout << "Please enter the image filename: ";
        cin >> filename;

        Image processedImage = processImage(filename);

        string outputFilename;
        cout << "Please enter the filename to save the processed image with detected edges (e.g., output.jpg): ";
        cin >> outputFilename;
        processedImage.saveImage(outputFilename); 

        cout << "The processed image with detected edges has been saved as " << outputFilename << endl;

    }


    else if(choice == 11){
        
    }


    else if(choice == 12){
        string filename;
        cout << "Enter the filename of the image you want to blur: ";
        getline(cin, filename);

        Image img;
        try {
            img.loadNewImage(filename);
        } catch (const std::invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
            return 1;
        }

        unsigned int kernelSize;
        cout << "Enter the kernel size (odd, >=3): ";
        cin >> kernelSize;

        boxBlur(img, kernelSize);

        string outputFilename;
        cout << "Enter the output filename ( with extension ): ";
        cin.ignore(); // Ignore the newline character left in the input buffer
        getline(cin, outputFilename);

        try {
            if (!img.saveImage(outputFilename)) {
                cerr << "Error: Failed to save blurred image." << endl;
                return 1;
            }
        } catch (const std::invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
            return 1;
        }

        cout << "Image blurred and saved successfully as " << outputFilename << endl;
    }

    else {
        cout << "Invalid choice!!";
        return 1;
    }

    return 0;
}
