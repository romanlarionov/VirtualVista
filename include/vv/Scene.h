
#ifndef VIRTUALVISTA_SCENE_H
#define VIRTUALVISTA_SCENE_H

#include <set>

#include "Light.h"
#include "Model.h"
#include "Camera.h"

namespace vv
{
    class Scene
    {
        friend class Light;
        friend class Model;
        friend class Camera;

    public:
        Scene();
        ~Scene();

        void manage(Light *light);
        void manage(Model *model);
        void manage(Camera *camera);

        void stopManaging(Light *light);
        void stopManaging(Model *model);
        void stopManaging(Camera *camera);

    private:
        Camera *camera_;
        // todo: check if set is best way to store
        std::set<Light *> lights_;
        std::set<Model *> models_;

    };
}

#endif // VIRTUALVISTA_SCENE_H