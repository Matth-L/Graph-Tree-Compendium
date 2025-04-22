#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "stb_image.h"
#include "stb_image_write.h"
#include "quadtree.h"

struct Pixel {
    unsigned char r, g, b;
};

// Surcharge de l'opérateur << pour afficher un Pixel (pour utiliser display)
std::ostream& operator<<(std::ostream& os, const Pixel& pixel) {
    os << "R: " << static_cast<int>(pixel.r)
       << " G: " << static_cast<int>(pixel.g)
       << " B: " << static_cast<int>(pixel.b);
    return os;
}

// Fonction pour calculer la couleur moyenne d'un ensemble de pixels
Pixel getAverageColor(const std::vector<Pixel>& pixels) {
    unsigned long r = 0, g = 0, b = 0;
    for (const auto& pixel : pixels) {
        r += pixel.r;
        g += pixel.g;
        b += pixel.b;
    }
    Pixel avg;
    avg.r = r / pixels.size();
    avg.g = g / pixels.size();
    avg.b = b / pixels.size();
    return avg;
}

// Fonction pour calculer la variance des couleurs par rapport à la couleur moyenne
double getVariance(const std::vector<Pixel>& pixels, const Pixel& avgColor) {
    double variance = 0.0;
    for (const auto& pixel : pixels) {
        variance += std::pow(pixel.r - avgColor.r, 2) + std::pow(pixel.g - avgColor.g, 2) + std::pow(pixel.b - avgColor.b, 2);
    }
    return variance / pixels.size();
}

// Fonction récursive pour construire le quadtree
QuadTree<Pixel>* buildQuadtree(const std::vector<Pixel>& pixels, int width, int height, double threshold) {
    if (pixels.empty()) return nullptr;

    Pixel avgColor = getAverageColor(pixels);
    double variance = getVariance(pixels, avgColor);

    if (variance <= threshold || width <= 1 || height <= 1) {
        return new QuadLeaf<Pixel>(avgColor);
    }

    QuadTree<Pixel>* sons[nQuadDir] = {nullptr, nullptr, nullptr, nullptr};
    int halfWidth = width / 2;
    int halfHeight = height / 2;

    std::vector<Pixel> topLeftPixels, topRightPixels, bottomLeftPixels, bottomRightPixels;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x < halfWidth && y < halfHeight) {
                topLeftPixels.push_back(pixels[y * width + x]);
            } else if (x >= halfWidth && y < halfHeight) {
                topRightPixels.push_back(pixels[y * width + x]);
            } else if (x < halfWidth && y >= halfHeight) {
                bottomLeftPixels.push_back(pixels[y * width + x]);
            } else {
                bottomRightPixels.push_back(pixels[y * width + x]);
            }
        }
    }

    sons[NW] = buildQuadtree(topLeftPixels, halfWidth, halfHeight, threshold);
    sons[NE] = buildQuadtree(topRightPixels, halfWidth, halfHeight, threshold);
    sons[SW] = buildQuadtree(bottomLeftPixels, halfWidth, halfHeight, threshold);
    sons[SE] = buildQuadtree(bottomRightPixels, halfWidth, halfHeight, threshold);

    return new QuadNode<Pixel>(sons);
}

// Fonction pour sérialiser un quadtree en format binaire
void serializeQuadTreeBinary(QuadTree<Pixel>* node, std::ofstream& out) {
    if (node->isLeaf()) {
        QuadLeaf<Pixel>* leaf = static_cast<QuadLeaf<Pixel>*>(node);
        char type = 'L';
        out.write(&type, sizeof(char));
        out.write(reinterpret_cast<const char*>(&leaf->value()), sizeof(Pixel));
    } else {
        QuadNode<Pixel>* internalNode = static_cast<QuadNode<Pixel>*>(node);
        char type = 'N';
        out.write(&type, sizeof(char));
        serializeQuadTreeBinary(internalNode->son(NW), out);
        serializeQuadTreeBinary(internalNode->son(NE), out);
        serializeQuadTreeBinary(internalNode->son(SW), out);
        serializeQuadTreeBinary(internalNode->son(SE), out);
    }
}

// Fonction pour sauvegarder un quadtree en format binaire
void saveQuadTreeBinary(QuadTree<Pixel>* root, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (out.is_open()) {
        serializeQuadTreeBinary(root, out);
        out.close();
    } else {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

// Fonction pour désérialiser un quadtree en format binaire
QuadTree<Pixel>* deserializeQuadTreeBinary(std::ifstream& in) {
    char type;
    in.read(&type, sizeof(char));
    if (in.eof()) {
        return nullptr;
    }
    if (type == 'L') {
        Pixel pixel;
        in.read(reinterpret_cast<char*>(&pixel), sizeof(Pixel));
        return new QuadLeaf<Pixel>(pixel);
    } else if (type == 'N') {
        QuadTree<Pixel>* sons[nQuadDir];
        sons[NW] = deserializeQuadTreeBinary(in);
        sons[NE] = deserializeQuadTreeBinary(in);
        sons[SW] = deserializeQuadTreeBinary(in);
        sons[SE] = deserializeQuadTreeBinary(in);
        return new QuadNode<Pixel>(sons);
    }
    return nullptr;
}

// Fonction pour charger un quadtree en format binaire
QuadTree<Pixel>* loadQuadTreeBinary(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open()) {
        QuadTree<Pixel>* root = deserializeQuadTreeBinary(in);
        in.close();
        return root;
    } else {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
        return nullptr;
    }
}

// Fonction récursive pour reconstruire l'image à partir du quadtree
void reconstructImage(QuadTree<Pixel>* node, std::vector<Pixel>& image, int x, int y, int width, int height, int imgWidth, int imgHeight) {
    if (node->isLeaf()) {
        Pixel color = node->value();
        for (int i = y; i < y + height; ++i) {
            for (int j = x; j < x + width; ++j) {
                image[i * imgWidth + j] = color;
            }
        }
        return;
    }

    int halfWidth = width / 2;
    int halfHeight = height / 2;

    // Appel récursif pour chaque quadrant
    reconstructImage(node->son(NW), image, x, y, halfWidth, halfHeight, imgWidth, imgHeight);
    reconstructImage(node->son(NE), image, x + halfWidth, y, halfWidth, halfHeight, imgWidth, imgHeight);
    reconstructImage(node->son(SW), image, x, y + halfHeight, halfWidth, halfHeight, imgWidth, imgHeight);
    reconstructImage(node->son(SE), image, x + halfWidth, y + halfHeight, halfWidth, halfHeight, imgWidth, imgHeight);
}

// Fonction pour compresser une image
void compressImage(const char* inputPath, const char* outputPath, double threshold) {
    int width, height, channels;
    unsigned char* img = stbi_load(inputPath, &width, &height, &channels, 3);

    if (img == nullptr) {
        std::cout << "Error in loading the image" << std::endl;
        return;
    }

    std::vector<Pixel> pixels(width * height);
    for (int i = 0; i < width * height; ++i) {
        pixels[i] = {img[i * 3], img[i * 3 + 1], img[i * 3 + 2]};
    }

    QuadTree<Pixel>* root = buildQuadtree(pixels, width, height, threshold);

    saveQuadTreeBinary(root, outputPath);

    delete root;
    stbi_image_free(img);
}

// Fonction pour décompresser une image
void decompressImage(const char* inputPath, const char* outputPath) {
    int width = 1024;
    int height = 1024;

    QuadTree<Pixel>* root = loadQuadTreeBinary(inputPath);

    std::vector<Pixel> compressedImage(width * height);
    reconstructImage(root, compressedImage, 0, 0, width, height, width, height);

    // Convert compressedImage to a format suitable for stbi_write_png
    std::vector<unsigned char> outputImage(width * height * 3);
    for (int i = 0; i < width * height; ++i) {
        outputImage[i * 3] = compressedImage[i].r;
        outputImage[i * 3 + 1] = compressedImage[i].g;
        outputImage[i * 3 + 2] = compressedImage[i].b;
    }

    // Save the compressed image
    if (!stbi_write_png(outputPath, width, height, 3, outputImage.data(), width * 3)) {
        std::cout << "Error in saving the image" << std::endl;
    }

    delete root;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " -c <Path to image> <Threshold> <Output path>" << std::endl;
        std::cout << "       " << argv[0] << " -d <Path to quadtree file> <Output path>" << std::endl;
        return -1;
    }

    if (std::strcmp(argv[1], "-c") == 0) {
        if (argc != 5) {
            std::cout << "Usage: " << argv[0] << " -c <Path to image> <Threshold> <Output path>" << std::endl;
            return -1;
        }
        double threshold = std::stod(argv[3]);
        compressImage(argv[2], argv[4], threshold);
    } else if (std::strcmp(argv[1], "-d") == 0) {
        if (argc != 4) {
            std::cout << "Usage: " << argv[0] << " -d <Path to quadtree file> <Output path>" << std::endl;
            return -1;
        }
        decompressImage(argv[2], argv[3]);
    } else {
        std::cout << "Invalid option. Use -c to compress or -d to decompress." << std::endl;
        return -1;
    }

    return 0;
}
