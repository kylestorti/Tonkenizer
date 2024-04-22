#include <iostream>
#include <fstream>
#include <string>

//Plain Commands
/*

rem = comments

The get, print, goto, and end statements correspond directly to the IML read, write,
branch, and halt instructions, respectively.
    o get only gets a single numeric variable
    o print can print either a single numeric variable or a numeric literal constant
    o Every line of code begins with a line number. Line numbers are strictly
        increasing in the program, but numbers may be skipped. goto transfers control to
        another line

if condition goto lineNumber = Evaluate a condition and transfer control to another line
if the condition is true. The condition compares a variable to another variable or a
numeric constant. Comparisons use = or >.

let = the assignment statement. Assigns a value to a variable. The value may a single
literal constant, a variable, or an arithmetic expression involving two values (each of
which may be literal constants or variables).
*/

int main() {
    std::string filename = "plainprogram.txt"; // The name of the file to read
    std::ifstream file(filename); // Create an input file stream object

    if (file.is_open()) { // Check if the file opened successfully
        char c; // A character variable to store each character read from the file
        while (file.get(c)) { // Read characters from the file one by one
            std::cout << c; // Print the character to the console. This is where we would have the logic to determine what each char means
        }
        file.close(); // Close the file
    } else {
        std::cout << "Unable to open file: " << filename << std::endl;
    }

    return 0;
}