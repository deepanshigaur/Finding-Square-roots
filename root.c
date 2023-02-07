#include <stdio.h>
#include <stdlib.h> // for atof
#include <math.h> // for sqrtf

float root(float a);
float calcError(float a,float g);
int floatEqual(float a, float b);

int main(int argc,char *argv[]) {

	if (argc!=2) {
		printf("Invoke as %s <n>\n",argv[0]);
		return 1;
	}

	float a=atof(argv[1]);
	float r=root(a);
	float sr=sqrtf(a);
	printf("root(%g)=%g error=%g\n",a,r,calcError(a,r));
	printf("sqrtf(%g)=%g error=%g\n",a,sr,calcError(a,sr));
	return 0;
}



float root(float a) {
	// TODO: replace the following return statement with code to calculate
	//    a square root of "a", using the Newton-Raphson method.
	// First check for negative. If so, return negative not-a-number
	// Next, create an initial guess, half of a.
	// Then loop until either you get floating point equality of a and your answer squared or
	//    the next iteration is floating point equal to the previous
	//    Calculate the next iteration using the Newton Raphson method.
	return NAN; // Until this is implemented, return "Not a Number"
}

int floatEqual(float a, float b) {
	// From "The art of computer programming" by Knuth Vol 2 p. 218
	// Ref: https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
	float epsilon=1.0e-6;
   return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

float calcError(float a,float g) { 	return fabs(a-(g*g)); }