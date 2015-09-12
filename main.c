#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

#include "deps/lodepng/lodepng.h"

void keyboard_callback(GLFWwindow *window, int key, int scancode,
  int action, int mods);

int main(int argc, char const *argv[])
{
  GLFWwindow *window;

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  window = glfwCreateWindow(400, 400, "Example Lodepng", NULL, NULL);
  
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  unsigned int error;
  unsigned char *image;
  unsigned int width, height;

  const char *filename = argc > 1 ? argv[1] : "textures/Nav.png";

  error = lodepng_decode32_file(&image, &width, &height, filename);
  if (error)
    printf("Error %u: %s\n", error, lodepng_error_text(error));
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
    GL_RGBA, GL_UNSIGNED_BYTE, image);
  free(image);

  while (!glfwWindowShouldClose(window))
  {
    glfwSetKeyCallback(window, keyboard_callback);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 400, 400, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    glColor3ub(255, 235, 115);
    glBegin(GL_QUADS);
      glTexCoord2f(0, 0); glVertex2f(50,  50);
      glTexCoord2f(1, 0); glVertex2f(350,  50);
      glTexCoord2f(1, 1); glVertex2f(350, 350);
      glTexCoord2f(0, 1); glVertex2f(50, 350);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void keyboard_callback(GLFWwindow* window, int key, int scancode,
  int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}
