
#ifndef VIRTUALVISTA_CAMERA_H
#define VIRTUALVISTA_CAMERA_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace vv
{
  class Camera
  {
  public:
    Camera();

    void update();

    void getViewMat(glm::mat4 &V);
    void getProjectionMat(glm::mat4 &P);
    void getMVPMat(glm::mat4 &MVP);

  private:
    double aspect_ratio_;
    double field_of_view_;
    double near_clip_;
    double far_clip_;

    float movement_speed_;
    float rotation_speed_;

    float pitch_angle_;
    float yaw_angle_;
    float max_pitch_angle_;
    float max_yaw_angle_;

    glm::vec3 position_vec_;  // global coordinate point
    glm::vec3 direction_vec_; // look at - position
    glm::vec3 look_at_vec_;   // position of observed point
    glm::vec3 up_vec_;        // global up direction

    glm::mat4 model_mat_;
    glm::mat4 view_mat_;
    glm::mat4 projection_mat_;
    glm::mat4 model_view_projection_mat_;

    void updatePosition();
    void updateOrientation();
  };
}

#endif // VIRTUALVISTA_CAMERA_H