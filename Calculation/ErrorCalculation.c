/*---------------------------------------------------------------------------*-
   ErrorCalculation ()
  -----------------------------------------------------------------------------
   Description: Calculate the error in% between 2 positive values ​​and limits the
				result at + - 100 

   formula: error [%] = ((measurement - setpoint) / setpoint) * 100

   Note 1: calculation impossible if the setpoint is 0 -> division by 0 !!
                the result will be:
                     0 if the measurement = 0
                     +100 if the measurement is> 0

   Note 2: calculation for the maximum values:
                  setpoint = 1 and measurement = 255 -> result = 25,400%
                  setpoint = 255 and measurement = 0 -> result = -100%
               
   Input:   setPoint, the set value 								   (0..255)
            measuredValue, the measured value                          (0..255) 

   Output: calculated error 									   (-100..+100)
-*---------------------------------------------------------------------------*/
char ErrorCalculation (unsigned char setPoint, unsigned char measuredValue)
{
	// Local variables
   int result;

   if (setPoint == 0)  // Setpoint case = 0
   {
      if  (measuredValue == 0)    // Same value so no error
      {
         result = 0;
      }
      else  // Infinite error -> result capped at +100
      {
         result = 100;
      }
   }
   else  // Other cases: setpoint <> 0
   {
      result = ((((int)measuredValue-setPoint) * 100) / setPoint);
      
      if (result > 100)  // Overflow test
      {
         result = 100;      // Sets the ceiling value
      }
   }

   return (result);

} // ErrorCalculation -------------------------------------------------------------