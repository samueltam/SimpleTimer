#include "simple_timer.h"

class SimpleTimerTest
{
  public:
    SimpleTimerTest() : _count(0) {}
    ~SimpleTimerTest() {}

    void test_single_shot() 
    {
      _count = 0;
      _timer.start(5, this, &SimpleTimerTest::expired_handler);
      sleep(6);

      if (_count != 1)
      {
        printf("test_single_short: failed. Timer didn't fired!\n");
      }
      else
      {
        printf("test_single_shot: succeeded. _count = %d\n", _count);
      }

      _timer.stop();
    }

    void test_periodic()
    {
      _count = 0;
      _timer.start_periodic(5, this, &SimpleTimerTest::expired_handler);
      sleep(16);

      if (_count != 3)
      {
        printf("test_periodic: failed. _count = %d!\n", _count);
      }
      else
      {
        printf("test_periodic: succeeded. _count = %d\n", _count);
      }

      _timer.stop();
    }

    void expired_handler()
    {
      _count++;
    }
  private:
    SimpleTimer<SimpleTimerTest> _timer;
    int _count;
};

int main(int argc, char* argv[])
{
  SimpleTimer<SimpleTimerTest>::init();

  SimpleTimerTest* test = new SimpleTimerTest();

  test->test_single_shot();
  test->test_periodic();

  SimpleTimer<SimpleTimerTest>::destroy();
}

