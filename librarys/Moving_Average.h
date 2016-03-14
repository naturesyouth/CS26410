/*
  Moving_Average.h - Library to provide a moving average function for any given float.
  Author: William Hogg Wih6@aber.ac.uk
  Date: first draft 20/2/16, most resent update 20/2/16.
*/

#ifndef Moving_Average_h
#define Moving_Average_h

#include "Arduino.h"

class Moving_Average
{
	public:
		Moving_Average(int range);
		void addValue(int add);
		int getAverage();

	private:
		int _values[];
		int _index;
};

#endif
 
