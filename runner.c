#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cooking.h"
#include <stdlib.h>

int main(int argc , char * argv[]){

struct book * myBook = newBook();
struct recipe * myRecipe = newRecipe("pizza" , 1);
struct pantry * myPantry = newPantry();
struct ingredient * myIngred = newIngredient("cheese" , 5);
struct pantry * add_ing = storeIngredient(myPantry , myIngred , 2);
if(add_ing != NULL)
	printf("%d",add_ing->quantity);

addIngredient(myRecipe , myIngred , 2);
addIngredient(myRecipe , myIngred , 2);
addRecipe(myBook , myRecipe);
addRecipe(myBook , myRecipe);
free(myBook);
free(myRecipe);
free(myPantry);
free(myIngred);
}
