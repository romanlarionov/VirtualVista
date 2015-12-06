
#ifndef VIRTUALVISTA_RESOURCE_H
#define VIRTUALVISTA_RESOURCE_H

#include <string>

namespace vv
{
    class Resource
    {
    public:

        void destroy();
    private:
        std::string handle_;
        int use_count_;

    };
}

#endif // VIRTUALVISTA_RESOURCE_H