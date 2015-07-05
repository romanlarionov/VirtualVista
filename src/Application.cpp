
#include <iostream>
#include <glm/glm.hpp>

#include "Application.h"
#include "Input.h"
#include "Shader.h"

namespace vv
{
  App::App() :
    first_run_(true),
    first_input_(true),
    app_init_(false),
    last_x_(0),
    last_y_(0),
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
      glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
      glfwWindowHint(GLFW_SAMPLES, 4);

      window_ = glfwCreateWindow(window_width_, window_height_, "Virtual Vista", nullptr, nullptr); // Not fullscreen

      if (!window_)
      {
        std::cerr << "ERROR: Window context failed to initialize.\n";
        return false; // Maybe have a try catch here
      }

      glfwMakeContextCurrent(window_);
//      glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

      glViewport(0, 0, window_width_, window_height_);

      // Needs to be called after window_ creation else seg fault.
      glewExperimental = GL_TRUE;
      glewInit();

      app_init_ = true;
    }

    return true;
  }

  void App::handleInput(Camera* cam, double delta_time)
  {
    double movement_speed = 30 * delta_time;
    double rotation_speed = 0.35 * delta_time;

    // TODO: fix key input on linux
    if (Input::instance()->keyIsPressed(GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(window_, GL_TRUE);

    // Camera movements
    if (Input::instance()->keyIsPressed(GLFW_KEY_W))
      cam->move(GLFW_KEY_W, movement_speed);

    if (Input::instance()->keyIsPressed(GLFW_KEY_A))
      cam->move(GLFW_KEY_A, movement_speed);

    if (Input::instance()->keyIsPressed(GLFW_KEY_S))
      cam->move(GLFW_KEY_S, movement_speed);

    if (Input::instance()->keyIsPressed(GLFW_KEY_D))
      cam->move(GLFW_KEY_D, movement_speed);

    // Camera rotations
    double curr_x, curr_y;
    Input::instance()->getMouseValues(curr_x, curr_y);
    if (first_input_ && (curr_x != 0 && curr_y != 0))
    {
      last_x_ = curr_x;
      last_y_ = curr_y;
      first_input_ = false;
    }

    double delta_x = (curr_x - last_x_);
    double delta_y = (last_y_ - curr_y);
    last_x_ = curr_x;
    last_y_ = curr_y;

    cam->rotate(delta_x, delta_y, rotation_speed);
  }

  GLFWwindow* App::getWindow()
  {
    return window_;
  }

  void App::run()
  {
    // create program
    std::string vert_path = "../src/shaders/vertex.glsl";
    std::string frag_path = "../src/shaders/fragment.glsl";
    Shader shader(vert_path, frag_path);

    Camera camera(&shader);

    GLfloat vertices[] = {
      -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,

      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,

      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,

      -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f
    };

    glm::vec3 cube_positions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),
      glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    glEnable(GL_DEPTH_TEST);

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

    // main loop
    while (!glfwWindowShouldClose(window_))
    {
      // collect input
      double curr_time = glfwGetTime();
      if (first_run_)
      {
        global_time_ = curr_time;
        first_run_ = false;
      }
      double delta_time = curr_time - global_time_;
      global_time_ = curr_time;

      glfwPollEvents();
      handleInput(&camera, delta_time);
      camera.update();

      // update
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      shader.useProgram();

      // TODO: change later
      float aspect = window_width_ / window_height_;
      float fov = 45.0f;
      float near = 0.1f;
      float far = 1000.0f;

      glm::mat4 perspective_mat = glm::perspective(fov, aspect, near, far);
      camera.bindViewMatrix();

      GLint model_location = glGetUniformLocation(shader.getProgramId(), "model");
      GLint proj_location = glGetUniformLocation(shader.getProgramId(), "projection");

      glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(perspective_mat));

      // render
      glBindVertexArray(VAO);
      for (GLuint i = 0; i < 10; ++i)
      {
        glm::mat4 model;
        model = glm::translate(model, cube_positions[i]);
        GLfloat a = 20.0f * i;
        model = glm::rotate(model, a, glm::vec3(1.0f, 0.3f, 0.5f));
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
      }
      glBindVertexArray(0);

      glfwSwapBuffers(window_);
    }
    glDisable(GL_DEPTH_TEST);

    // clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(window_);
    glfwTerminate();
  }
} // namespace vv