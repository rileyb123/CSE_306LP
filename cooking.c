#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "cooking.h"
#include <stdlib.h>



struct book * newBook(){

  struct book * bo = malloc(sizeof(struct book));
  if(bo == NULL)
    return NULL;
  bo->rec = malloc(sizeof(struct recipe));
  bo->next_rec = malloc(sizeof(struct recipe *));
  bo->rec = NULL;
  bo->next_rec = NULL;

return bo;
}


struct recipe * newRecipe(char * name, int servings){
  struct recipe * rec = malloc(sizeof(struct recipe));
  if(rec == NULL)
    return NULL;
  (*rec).serving = servings;
  (*rec).quantity = -1;
  rec->name  = malloc(sizeof(char)*32); //name cannot be longer than 32 currently
  strcpy(rec->name , name);
  rec->ing = malloc(sizeof(struct ingredient));
  rec->ing = NULL;
  rec->next_ing = malloc(sizeof(struct ingredient *));
  rec->next_ing = NULL;

  return rec;
}



struct ingredient * newIngredient(char * name, int caloriesPerGram){
  struct ingredient * in = malloc(sizeof(struct ingredient));
  if(in == NULL)
    return NULL;
  in->name  = malloc(sizeof(char)*32);
  strcpy(in->name , name);
  (*in).calPerGram = caloriesPerGram;

  return in;
}


struct pantry * newPantry(){
  struct pantry * pan = malloc(sizeof(struct pantry));
  if(pan == NULL)
    return NULL;
  pan->ing = malloc(sizeof(struct ingredient *));
  (*pan).quantity = -1; // -1 means this shelf in the pantry is free
  pan->next_pan = malloc(sizeof(struct ingredient *));

  return pan;
}


void addRecipe(struct book * bo, struct recipe * r){

  if(bo->rec == NULL){
    bo->rec = r;
  }
  else{
    struct book * tempr = bo->next_rec;
    struct book * prev_book = bo;
    while(tempr != NULL){
      prev_book = tempr;
      tempr = tempr->next_rec;
    }
    prev_book-> next_rec = newBook();
    prev_book = prev_book->next_rec;
    prev_book->rec = r;
  }


}


void addIngredient(struct recipe * r, struct ingredient * in, int quantity){

  if(r->ing == NULL){
    r->ing = in;
    (*r).quantity = quantity;
  }
  else{
    struct recipe * tempr = r->next_ing;
    struct recipe * prev_rec = r;
    while(tempr != NULL){
      prev_rec = tempr;
      tempr = tempr->next_ing;
    }
    tempr = newRecipe(r->name , (*r).serving);
    prev_rec->next_ing = tempr;
    (*tempr).quantity = quantity;
    (*tempr).ing = in;
  }


}

struct pantry * storeIngredient(struct pantry * pan, struct ingredient * in, int quantity){

return NULL;
}

struct book * canMakeAny(struct pantry * pan,struct book * bo){

return NULL;
}


struct book ** canMakeAll(struct pantry * pan ,struct book * bo){


return NULL;
}


struct book * withinCalorieLimit(struct pantry * pan ,struct book * bo,int limit){


return NULL;
}
