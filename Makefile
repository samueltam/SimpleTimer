simple_timer_test: simple_timer_test.cc simple_timer.h
	g++ -lboost_date_time -lboost_system -lboost_thread -o simple_timer_test simple_timer_test.cc
