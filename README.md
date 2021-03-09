# ConfigFiles Library
 This library handles loading and saving config values to individual files.  While a seperate files for each value wastes storage and is overkill, it is simple and lightweight. 
 
 The library has a read function for ints and floats but the write function is currently only for ints. Writing floats is not implimented in Arduino so they need to be first converted to strings. The best approach, if you need to write floats, is to convert them to strings first (in your program) and then use the writestr function. Then you have control over how many decimal places are written. 
 
 Also, included are functions to write and read strings (char arrays). The read function reads up to maxValueLen (default 20) or EOF, which ever comes first. The write function will write a string (char array) of whatever length is given but it must be null terminated! I am not doing much error control or checking with these functions so you have to be careful of what you are doing.

 If someone has suggestions about how to improve this library, I am happy for input.

## Updates
* 
William Cable\
Bill.Cable@awi.de\
Permafrost Research\
Alfred Wegener Institute Helmholtz Centre for Polar and Marine Research\
Telegrafenberg A45\
14473 Potsdam\