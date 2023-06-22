#include <iostream>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class ImageRenderer {
public:
    ImageRenderer(const std::string& imagePath) : image(nullptr), imageWidth(0), imageHeight(0), imageChannels(0), spritePosX(900), spritePosY(500), dragging(false) {
        loadImage(imagePath);
    }

    ~ImageRenderer() {
        stbi_image_free(image);
    }

    void loadImage(const std::string& imagePath) {
        image = stbi_load(imagePath.c_str(), &imageWidth, &imageHeight, &imageChannels, 0);
        if (!image) {
            std::cout << "Error loading image" << std::endl;
            return;
        }
    }

    void render() {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(spritePosX, spritePosY, 0.0f);
        glRasterPos2f(-1, -1);
        glDrawPixels(imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, image);
        glutSwapBuffers();
    }

    void setSpritePosition(float x, float y) {
        spritePosX = x;
        spritePosY = y;
    }

    float getSpriteWidth() const {
        return imageWidth;
    }

    float getSpriteHeight() const {
        return imageHeight;
    }

    bool isCursorOverSprite(int cursorX, int cursorY) {
        return (cursorX >= spritePosX && cursorX <= spritePosX + imageWidth &&
                cursorY >= spritePosY && cursorY <= spritePosY + imageHeight);
    }

    void startDragging() {
        dragging = true;
    }

    void stopDragging() {
        dragging = false;
    }

    bool isDragging() const {
        return dragging;
    }

    void updateSpritePosition(int deltaX, int deltaY) {
        spritePosX += deltaX;
        spritePosY += deltaY;
    }

private:
    unsigned char* image;
    int imageWidth, imageHeight, imageChannels;
    float spritePosX, spritePosY;
    bool dragging;
};

ImageRenderer imageRenderer("image.png");
int prevCursorX, prevCursorY;

void display() {
    imageRenderer.render();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            if (imageRenderer.isCursorOverSprite(x, y)) {
                prevCursorX = x;
                prevCursorY = y;
                imageRenderer.setSpritePosition(x - imageRenderer.getSpriteWidth() / 2, y - imageRenderer.getSpriteHeight() / 2);
                glutPostRedisplay();
                imageRenderer.startDragging();
            }
        } else if (state == GLUT_UP) {
            imageRenderer.stopDragging();
        }
    }
}

void mouseMotion(int x, int y) {
    if (imageRenderer.isDragging()) {
        int deltaX = x - prevCursorX;
        int deltaY = y - prevCursorY;
        imageRenderer.updateSpritePosition(deltaX, deltaY);
        prevCursorX = x;
        prevCursorY = y;
        glutPostRedisplay();
    }
}
