#include "hwlib.hpp"        

//this code is a simple example for the rotary encoder.
//it works a bit strange but it always gives the good values, unlike the versions that keep track of the old states
//they don't work good because after 0,0 the values turn around ( 1,0 to 0,1 ) and you will count up and count down
//at the same moment, and sometimes not if you are lucky...                                 

int main( void ){ 

   namespace target = hwlib::target;                          

   auto clk = target::pin_in( hwlib::target::pins::d7 );   				//one of the data pins called clk
   auto dt = target::pin_in( hwlib::target::pins::d6 );   				//one of the data pins called dt
   auto sw = target::pin_in( hwlib::target::pins::d5 );					//the push button on the rotary encoder

   hwlib::cout << "start..";											//useless startup sequence...
   hwlib::wait_ms(100); 												//just a little wait to make sure

   int counter = 0; 													//the counter that keeps track of the value the rotator gives us

   for(;;){           													//first loop to stay cheching if both pins are equal to 1
   	  hwlib::wait_ms(10);												//little wait				

   	  if(clk.read() == 1 && dt.read() == 1){							//checks if both pins are equal to 1 before checking the changes in the pins
   	  	for(;;){														//start a for loop that automatically will stop after both pins have become 0 (this is always the case, so we are not stuck in a infinity loop)

   	  		if(sw.read() == 0){											//checks if the button has been pressed
   	  		    counter = 0;											//changes the counter back to 0
   	  		}		
   	  		if(clk.read() == 0 && dt.read() == 1){						//checks if the pins are 0 and 1 after they have been both 1
   	  			counter--; 												//make the counter lower
   	  			hwlib::cout << "counter: " << counter << "\n";			//display the nwe counter value
   	  			break;													//get out of the loop, back to checking if both pins are 1
   	  		}else if(clk.read() == 1 && dt.read() == 0){				//checks if the pins are 1 and 0 after they have been both 1
   	  			counter++; 												//add 1 to the counter	
   	  			hwlib::cout << "counter: " << counter << "\n";			//display the counter
   	  			break;													//break out of the loop, back to checking if both pins are 1
   	  		}else if(clk.read() == 0 && dt.read() == 0){				//checks if both pins are 0 (this automatically happens if one of the pins has been changed)
   	  			break;													//break back to the other for loop
   	  		}					
   	  	}
   	}
   }

}