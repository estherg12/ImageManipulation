# ImageManipulation
With DataStructures as Stacks, Queues and Lists
Implementation of different operations to bmp images:
1. Reversing
2. Flip
3. Flop
4. Darken
5. Sorting pixels

With the basic operation of data structures such as stacks, queues and list, without any libraries

The program will execute three phases.
1. The first phase will be in charge of image loading, data extraction and data
insertion in a data structure used to pass data the next phase. The name of the image will be requested to the user. The program will only accept.
  For helping with image read and write a simple library is provided. The image read will be stored in a memory block without structure where you can access to any element using pointer arithmetic. The function used for reading will produce as output the width and height of the image. Every pixel will use 3 bytes to store the RGB value (Reg, Green and Blue). To access any pixel values, you will use an existing method to retrieve it.
  As additional information, to calculate the memory position using the following formulas (considering rows from 0 to width-1, and columns from 0 to height-1):
     • Red value: ImagePointer + (row * width) + column 
     • Green value: ImagePointer + (row * width) + column +1
     • Blue value: ImagePointer + (row * width) + column +2
  A queue storing all pixels (without filtering) will be created and feed to the next phase.
  Every pixel object will contain color and position information.

2. The second phase will be in charge of asking to the user about a list of processing operations. In this phase, the program will ask for one operation to the user. Operations could be:
  R = reverse image pixels to get a negative image
  S = Sorting image pixels using the sum of all three components (RGB) and the original order as secondary criteria. The ordered pixels will start in the upper-left corner and follow to the right and down to the next line.
  H = Flipped image.
  V = Flopped image.
  D = Darken image.

  Operations will not be executed, only stored in a stack that will be the result of this phase. The phase ends when the user type “X” which is not a valid operation and will not be stored in the stack.

3. The third phase will be in charge of image data processing and output images generation.
In this phase, the operations stack is used to get the next operation to be applied to the image stored in the input queue.
For every operation, additional data structures should be required. The output of every operation will be a new image on disk with the name of the original image and the operation. i.e. with an input image “Im1.bmp” and operation “V” the output image will be named “Im1_V.bmp”.


