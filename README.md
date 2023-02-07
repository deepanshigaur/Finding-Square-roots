# Lab 03 - Finding Square Roots

## Lab Goals

Today, we are going to work on using floating point numbers. The most important thing to remember about floating point numbers is that floating point numbers are almost always not exact numbers, but approximations. Floating point arithmetic also uses approximations, so that every operation introduces a little more error. The result is that we have to use some special techniques when using floating point numbers.

To demonstrate, we will be calculating the square root of a floating point number.

### Background: The Newton-Raphson Method

 We will calculate the square root using the Newton-Raphson method. (See the Wikipedia page on [Newton's method](https://en.wikipedia.org/wiki/Newton%27s_method) for more detail.) There is a C library function to calculate the square root of a number (sqrtf), so we would typically just use the library function, but we are doing this exercise to learn about floating point arithmetic.

The Newton-Raphson method (also called the "Newton method") is a general method that says that if you have a function, *f(x)* and you can take the derivative of that function, *f'(x)*, then you can calculate a value for *x* by starting with an initial guess, and improving that guess using the formula *x[t+1] = x[t] - f(x[t])/f'(x[t])*. As long as the initial guess is reasonably close to a solution, then repeated invocations of this formula will get you closer and closer to the correct answer.

We apply this method to the problem of calculating a square root by defining *f(x)=x\*x - a*. If *x* is the square root of *a*, then *f(x)=0*. Using calculus, the derivative of *f(x)* is *f'(x)=2x*. Plugging these formulas into the Newton-Raphson method, and using a more C-like notation instead of a pure mathematical notation, the result is:

`x_next = x - ((x*x)-a)/(2*x)`

We can apply this formula repeatedly until either we have a reasonably close approximation of the square root, or until the formula produces approximately the same answer as the previous iteration.

### Background: Floating Point "Equality"

The Newton-Raphson method for calculating square roots requires two comparisons of floating point numbers - one to see if the square root is close to correct, and the other to see if the method is increasing accuracy at all. Both of these comparisons need to be able to determine what it means for two floating point numbers to be "reasonably close" to each other.

It turns out that defining "reasonably close" is pretty complicated! First, reasonably close depends on how you are going to use the result. For instance, if you are calculating the square root in order to make a child's bookcase, then it is perfectly reasonable to calculate to within 0.01% of your full measurement. If you are calculating the square root to determine the angle of a rocket going to the moon, you need something much more precise.

The traditional way to determine "reasonably close" is to select some small number, called *epsilon*, and say that if two numbers are within *epsilon* of each other, they are reasonably close. In code, given *a* and *b*, we can check to see if `fabs(a-b)<epsilon`. (The `fabs` function is the C library floating point absolute value function.) But that means we have to know what *epsilon* should be, and you might want a different *epsilon* for very large numbers than for very small numbers.

The alternative that we are going to use is a definition from the great Computer Scientist and CalTech professor, [Donald Knuth](https://en.wikipedia.org/wiki/Donald_Knuth). In Volume 2 of Knuth's seminal **The Art of Computer Programming**, Knuth proposes scaling epsilon by the smaller of *a* or *b*. In C this becomes:

`fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon)`

(Notice we get to use our ternary ?/: operator here.)

## Provided Code

There are three files in this repository already, as follows:

### root.c

The root.c file contains all the code required for this lab. It has four functions:

- **main** The main function reads the command line argument as a floating point number, and then passes that to your `root` function as well as the C library `sqrtf` function. It then prints out the results, and what the error is between the square of the calculated square root and the original number.

- **root** This is the function you need to implement for this lab, using the Newton-Raphson method as defined above.

- **calcError** Returns the absolute value of the difference between the original number and the square root of that number squared.

- **floatEqual** Determines if two numbers are "approximately equal", using Knuth's method described above.

### Makefile

I have provided a Makefile that defines Make variables for the C compiler (CC) and C flags (CFLAGS) to be used for this assignment (and this course.) Note that since our code uses the sqrtf function from the math library, and since the math library is not always automatically included by the compiler, I also added a Make variable for load libraries (LDLIBS).

I have included several explicit make rules:

- `test` : has a dependency on the root executable file, and runs the root executable, passing in some command line arguments.
- `gdb` : Runs gdb on the root executable with argument "2"
- `clean` : removes all the extra files created by the Makefile (the root executable file)

There is an implicit rule for `root` that uses the CC, CFLAGS, and LDLIBS make variables.

## Doing the Assignment

1. Clone the repository on a UNIX machine. See [How to Use GitHub](https://www.cs.binghamton.edu/~tbartens/HowTo/Using_GitHub) for details on cloning, etc.
2. Read through the existing code as well as the explanations in this README file to understand the infrastructure. You can try compiling and running the code, but until you code the root function the results will be bogus.
3. Edit the root.c file to complete the root function. You will need to figure out how to calculate the square root by repeatedly invoking the Newton-Raphson method defined above. You are not allowed to use the C library functions to directly calculate the square root - you must use the Newton-Raphson method, iterating through guesses until you get a good enough answer.
4. Build and test the result using the make command. If you code the root function correctly, the results of the root function should be almost exactly the same as the results from the sqrtf function. If your code is not working correctly, try using gdb to stop your code where it is failing, and step through the code a line at a time to see what is going wrong. See [How to Use GDB](http://www.cs.binghamton.edu/~tbartens/HowTo/Using_gdb) for more on debugging with gdb.
5. Once your code is working, commit and push your results into your master git repository, and get the hash code using `git rev-parse HEAD`. Paste that hash code into the submission area for lab02 in Brightspace.

## Hints and Suggestions

1. It is very easy to get into endless loops in this lab. When coded correctly, the Newton-Raphson method zooms in on the square root very quickly. If your code is taking more than a second or two, you are probably in an endless loop. Use "Ctrl-C" to interrupt your code, and try again with gdb to find the bug that is causing the loop.
2. Since we aren't dealing with complex numbers, if the "a" argument to the root function is a negative number, the root function should return the floating point representation of negative "Not a Number" or "-NaN". There is a macro defined in the math.h library called `NAN` that contains the floating point representation of "Not a Number", and it can be preceded by a minus sign to make negative NaN.
3. There are some very sophisticated techniques to make an initial guess for the Newton-Raphson method to calculate square roots. The better the initial guess, the faster the method converges on the right answer. However, for our purposes, it's much easier just to set the initial guess to `a/2.0`. That's not perfect (often too high), but still enough to work quite well, and it's simple.
4. The C compiler usually provides automatic access to the standard C library function implementations. However, on some platforms, the C compiler does not automatically include the library functions described in the math.h include file. We are using math.h for the sqrtf function in this program. Therefore, I have added the flag "-lm" to the LDFLAGS make variable. On most platforms, this -lm flag is not required, but on some platforms, the root program won't link edit correctly without the -lm flag.

## Lab Grading

This lab is worth 10 points. You will get the full 10 points if the TA's can download your repository using the git hash code from Brightspace onto a computer science machine, and run `make test`, and get the correct results. Your code will also be tested with a different set of arguments to make sure it works with any arguments. You will receive the following deductions:

- -5 if compiling root.c causes a compile error.
- -2 if compiling root.c causes a compiler warning
- -4 if the results do not print correctly.
- -1 if the Brightspace submission occurs after your lab period (A 5 or 10 minute grace period is allowed.)
- -1 if your repository contains any binary executable files.
- -2 for every 24 hours (or part of 24 hours) after the submission date.
