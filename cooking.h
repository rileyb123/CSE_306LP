#ifndef COOKING_H
#define COOKING_H

#include <stdbool.h>

struct book{
struct recipe * rec;
struct book * next_rec;
};

struct recipe{
struct ingredient * ing;
int serving;
int quantity;
char * name;
struct recipe * next_ing;
};

struct pantry{
struct ingredient * ing;
int quantity;
struct pantry * next_pan;
};

struct ingredient{
char * name;
int calPerGram;
};


struct book * newBook();


struct recipe * newRecipe(char * name, int servings);



struct ingredient * newIngredient(char * name, int caloriesPerGram);


struct pantry * newPantry();

void addRecipe(struct book * bo, struct recipe * r);

void addIngredient(struct recipe * r, struct ingredient * in, int quantity);

struct pantry * storeIngredient(struct pantry * pan, struct ingredient * in, int quantity);

struct book * canMakeAny(struct pantry * pan,struct book * bo);


struct book ** canMakeAll(struct pantry * pan ,struct book * bo);


struct book * withinCalorieLimit(struct pantry * pan ,struct book * bo,int limit);

#endif
