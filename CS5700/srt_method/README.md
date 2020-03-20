#CS 5700 Project : Srt Division Algorithm

1. Project Usage:

To run this program, use the following command.
-	make
-	./srt [Dividend] [Divisor]
-	see the output

Existing Problem:
	When the user input binary number, you have to add the portion of block in SRT_method.cpp(line.48).
	Otherwise it will throw an error. Otherwise, it works.
	
	There is an error associated with the problem above, when I input .19 .5, when I convert Hexa to binary, then 
	I would have to erase the portion of block in SRT_method.cpp(line.48)
	
  When the input string is long, it tends to have some problem with my conditional statement, which it checks each bit of normalized B and AQ.
        Then add strings. --> But this could be my compiler error(I tried to fix it, but it does not work well).
        But with the test data, I was accomplished to get some values by calculating by hands.

2. Project Description:
        Given two inputs [Dividend] [Divisor], using division algorithm called, Srt division algorithm can be done.
        1. Correct the inputs if the value of Dvidend is higher than the divisor.
        2. Adjust the AQ
        3. Normalize B and get a compliments Number
        4. Then Operate the srt algorithm.

