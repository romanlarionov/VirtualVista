
#include <iostream>

#include "Application.h"
#include "Input.h"
#include "Shader.h"

namespace vv
{
  App::App() :
    first_run_(true),
    app_init_(false),
    global_time_(0)
  {
    window_width_ = 800;
    window_height_ = 600;
  }

  bool App::init()
  {
    if (!app_init_) // prevent multiple calls
    {
      if (!glfwInit())
      {
        std::cerr << "ERROR: GLFW failed to initialize.\n";
        return EXIT_FAILURE;
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
      glfwWindowHint(GLFW_SAMPLES, 4);

      window_ = glfwCreateWindow(window_width_, window_height_, "Virtual Vista", nullptr, nullptr); // Not fullscreen

      if (!window_)
      {
        std::cerr << "ERROR: Window context failed to initialize.\n";
        return false; // Maybe have a try catch here
      }

      glfwMakeContextCurrent(window_);

      glViewport(0, 0, window_width_, window_height_);

      // Needs to be called after window_ creation else seg fault.
      glewExperimental = GL_TRUE;
      glewInit();

      app_init_ = true;
    }

    return true;
  }

  void App::handleInput()
  {
    if (Input::instance()->keyIsPressed(GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(window_, GL_TRUE);

    if (Input::instance()->keyIsPressed(GLFW_KEY_W))
      std::cout << "W\n";

    if (Input::instance()->keyIsPressed(GLFW_KEY_W))
      std::cout << "B\n";
  }

  void App::run()
  {
    // create program
    std::string vert_path = "../src/shaders/vertex.glsl";
    std::string frag_path = "../src/shaders/fragment.glsl";
    Shader shader(vert_path, frag_path);

    std::string vert_path2 = "../src/shaders/vertex2.glsl";
    std::string frag_path2 = "../src/shaders/fragment2.glsl";
    Shader shader2(vert_path2, frag_path2);

    GLfloat vertices[] =
    {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f,  0.5f, 0.0f
    };

    GLfloat vertices2[] =
    {
      -1.0f, -0.5f, 0.0f,
      0.0f, -0.5f, 0.0f,
      -0.5f,  0.0f, 0.0f,
    };

    // create vertex array object that stores a single configuration of drawing specifications like
    // which attributes to use, how many VBOs to use, etc.
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // from here on, all configurations pertain to this VAO.

    // think of this like a data structure on the device, we're generating a new storage space for our data
    // that we want draw, and then shipping the data from the host to the device.
    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // inform the GPU how to understand and process the incoming data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0); // prevent any accidental mis-configurations

    GLuint VAO2 = 0;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2); // from here on, all configurations pertain to this VAO.

    // think of this like a data structure on the device, we're generating a new storage space for our data
    // that we want draw, and then shipping the data from the host to the device.
    GLuint VBO2 = 0;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // inform the GPU how to understand and process the incoming data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); // prevent any accidental mis-configurations

    // main loop
    while (!glfwWindowShouldClose(window_))
    {
      // collect input
      GLdouble curr_time = glfwGetTime();
      if (first_run_)
      {
        global_time_ = curr_time;
        first_run_ = false;
      }
      GLdouble delta_time = global_time_ - curr_time;
      global_time_ = curr_time;

      glfwPollEvents();
      //handleInput();
      std::cout << (glfwGetKey(window_, 87) == GLFW_PRESS) << "\n";

      // update
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // render
      shader.useProgram();
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);

      shader2.useProgram();
      glBindVertexArray(VAO2);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);

      glfwSwapBuffers(window_);
    }

    // clean up
    glDeleteVertexArrays(1, &VAO2);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(window_);
    glfwTerminate();
  }
} // namespace vv