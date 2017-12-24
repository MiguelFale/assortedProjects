//compiler directives seem to be mostly the same
//#include <iostream.h> remove .h
#include <iostream> //interesting

/* don't use 'using namespace std'
https://stackoverflow.com/a/1452738/5985805
*/
void bubblesort (int a[], int dim);


int main(int argc, char** argv)
{
	int a[9] = {9,7,5,1,2,3,6,4,8};
    //std::cout << "Hello World!\n";
    bubblesort(a,9);

    for(int i=0;i<9;i++) {
    	std::cout << a[i];
    	std::cout << " ";
    }
    
    return 0;
}

void bubblesort (int a[], int dim)
{
	int hold, i,j;

	for(j=0; j < dim; j++) {
		//swapped = false;
		for(i=1; i < dim; i++) {
			if(a[i-1] > a[i]) {
				hold = a[i-1];
				a[i-1] = a[i];
				a[i] = hold;
				//swapped = true;
			}
		}
	}
}
