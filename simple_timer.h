#ifndef _SIMPLE_TIMER_H_
#define _SIMPLE_TIMER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

template <class T>

class SimpleTimer
{
  public:
    typedef enum {IDLE, RUNNING, EXPIRED} Status;
    typedef void (T::*CALLBACK_PTR)();

    SimpleTimer() : timer_(io__), strand_(io__), status_(IDLE), periodic_(false), seconds_(0), object_(0), handler_(0) {}
    ~SimpleTimer() {}

    void start(unsigned long seconds, T* obj, CALLBACK_PTR method)
    {
      object_ = obj;
      handler_ = method;
      periodic_ = false;
      seconds_ = seconds;

      if (status_ == RUNNING)
        timer_.cancel();

      arm_boost_timer();

      status_ = RUNNING;
    }

    void start_periodic(unsigned long seconds, T* obj, CALLBACK_PTR method)
    {
      object_ = obj;
      handler_ = method;
      periodic_ = true;
      seconds_ = seconds;

      if (status_ == RUNNING)
        timer_.cancel();

      arm_boost_timer();

      status_ = RUNNING;
    }

    void stop()
    {
      timer_.cancel();

      object_ = 0;
      handler_ = 0;

      status_ = IDLE;
    }

    void expired()
    {
      (object_->*(handler_))();

      if (periodic_)
      {
        arm_boost_timer();
      }
      else
      {
        status_ = EXPIRED;
      }
    }

    bool is_running()
    {
      return status_ == RUNNING;
    }

    static void init()
    {
      thread__ = boost::thread(start_io);
    }

    static void destroy()
    {
      stop_io();
    }

private:
    static boost::asio::io_service io__;
    static boost::thread thread__;

    boost::asio::deadline_timer timer_;
    boost::asio::strand strand_;
    Status status_;
    bool periodic_;
    unsigned long seconds_;
    T* object_;
    CALLBACK_PTR handler_;

    static bool halt_;

    inline void arm_boost_timer()
    {
      timer_.expires_from_now(boost::posix_time::seconds(seconds_));
      timer_.async_wait(strand_.wrap(boost::bind(&SimpleTimer::expired, this)));
    }

    static void start_io()
    {
      for (;;)
      {
        if (halt_)
          break;

        boost::asio::io_service::work work(io__);
        io__.run();
        io__.reset();
      }
    }

    static void stop_io()
    {
      halt_ = true;
    }

};

template <class T>
boost::asio::io_service SimpleTimer<T>::io__;
template <class T>
boost::thread SimpleTimer<T>::thread__;
template <class T>
bool SimpleTimer<T>::halt_ = false;

#endif

