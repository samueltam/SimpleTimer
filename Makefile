simple_timer_test: simple_timer_test.cc simple_timer.h
	g++ -D_WIN32_WINNT=0x0501 -I/C/MinGW/msys/1.0/home/Samuel/boost_1_46_1 -o simple_timer_test simple_timer_test.cc /C/MinGW/msys/1.0/home/Samuel/boost_1_46_1/stage/lib/libboost_date_time-mgw46-1_46_1.dll.a /C/MinGW/msys/1.0/home/Samuel/boost_1_46_1/stage/lib/libboost_thread-mgw46-mt-1_46_1.dll.a /C/MinGW/msys/1.0/home/Samuel/boost_1_46_1/stage/lib/libboost_system-mgw46-1_46_1.dll.a -lws2_32  
