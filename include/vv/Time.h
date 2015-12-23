
#ifndef VIRTUALVISTA_TIME_H
#define VIRTUALVISTA_TIME_H

namespace vv
{
  class Time 
  {
    friend class Application;

  public:
    static double current(); /* in milliseconds */
    static double delta();
    static size_t frameCount();
    static int frameRate();

  private:
    static double delta_time_; /* delta time between frames */
    static size_t frame_num_;  /* total number of elapsed frames */
    static int frame_rate_;    /* current frames per second */
  };
}

#endif // VIRTUALVISTA_TIME_H