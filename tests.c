#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "CUnit.h"
#include "Basic.h"
#include "cooking.h"
#include <stdlib.h>


void test01(void) {
struct book * myBook = newBook();
CU_ASSERT_PTR_NOT_NULL(myBook);
}

void test02(void) {
  char * name = "pizza";
  struct recipe * myRecipe = newRecipe(name , 1);
  CU_ASSERT_PTR_NOT_NULL(myRecipe);

  CU_ASSERT_STRING_EQUAL((*myRecipe).name , name);
  CU_ASSERT_EQUAL(((*myRecipe).serving) , 1);
}

void test03(void) {
  struct pantry * myPantry = newPantry();
  CU_ASSERT_PTR_NOT_NULL(myPantry);
}

void test04(void) {
  char * name = "flour";
  struct ingredient * myIngred = newIngredient(name , 5);
  CU_ASSERT_PTR_NOT_NULL(myIngred);
  CU_ASSERT_STRING_EQUAL((*myIngred).name , name);
  CU_ASSERT_EQUAL((*myIngred).calPerGram , 5);
}

void test05(void) {
  struct book * myBook = newBook();
  struct recipe  * myRecipe = newRecipe("pizza" , 1);
  addRecipe(myBook , myRecipe);
  struct recipe  * myRecipe2 = (*myBook).rec ;
  CU_ASSERT_STRING_EQUAL((*myRecipe2).name , (*myRecipe).name);
  CU_ASSERT_EQUAL((*myRecipe2).serving , (*myRecipe).serving);
}

void test06(void) {
  struct recipe * myRecipe = newRecipe("pizza" , 1);
  struct ingredient * in = newIngredient("flour" , 5);
  addIngredient(myRecipe , in , 2);
  struct ingredient * in2 = (*myRecipe).ing;
  CU_ASSERT_EQUAL((*myRecipe).quantity , 2 );
  CU_ASSERT_EQUAL((*in2).calPerGram , 5);
  CU_ASSERT_STRING_EQUAL((*in2).name , (*in).name);
}

void test07(void) {
  struct book * myBook = newBook();
  struct recipe  * myRecipe = newRecipe("pizza" , 1);
  struct recipe  * myRecipe2 = newRecipe("cake" , 2);
  addRecipe(myBook , myRecipe);
  addRecipe(myBook , myRecipe2 );
  struct book * next_rec = myBook->next_rec;
  struct recipe *rec = next_rec->rec;
  CU_ASSERT_STRING_EQUAL((*myRecipe2).name , (*rec).name);
  CU_ASSERT_EQUAL((*myRecipe2).serving , (*rec).serving);

}

void test08(void) {
  struct recipe * myRecipe = newRecipe("pizza" , 1);
  struct ingredient * in = newIngredient("flour" , 5);
  struct ingredient * inn = newIngredient("sauce" , 3);
  addIngredient(myRecipe , in , 2);
  addIngredient(myRecipe , inn , 2);
  struct ingredient * in2 = (*myRecipe).ing;
  struct recipe * r2 = myRecipe->next_ing;
  struct ingredient * in3 = (*r2).ing;
  CU_ASSERT_EQUAL((*myRecipe).quantity , 2 );
  CU_ASSERT_EQUAL((*in2).calPerGram , 5);
  CU_ASSERT_STRING_EQUAL((*in2).name , (*in).name);
  CU_ASSERT_EQUAL((*r2).quantity , 2 );
  CU_ASSERT_EQUAL((*in3).calPerGram , 3);
  CU_ASSERT_STRING_EQUAL((*in3).name , (*inn).name);
}

//Tests Past Here are very basic, just here to increase code coverage
void test09(void){
  struct ingredient * in = newIngredient("flour" , 5);
  struct pantry * myPantry = newPantry();
  struct pantry * added_pantry = storeIngredient(myPantry , in , 2);
  CU_ASSERT_PTR_NOT_NULL(added_pantry);
}

void test10(void){
  struct book * myBook = newBook();
  struct pantry * myPantry = newPantry();
  struct book * new_book = canMakeAny(myPantry , myBook);
  CU_ASSERT_PTR_NOT_NULL(new_book);
}

void test11(void){
  struct book * myBook = newBook();
  struct pantry * myPantry = newPantry();
  struct book ** new_book = canMakeAll(myPantry , myBook);
  CU_ASSERT_PTR_NOT_NULL(new_book);
}

void test12(void){
  struct book * myBook = newBook();
  struct pantry * myPantry = newPantry();
  struct book * new_book = withinCalorieLimit(myPantry , myBook, 500);
  CU_ASSERT_PTR_NOT_NULL(new_book);
}



/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry()) { return CU_get_error(); }

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_of_tests_with_valid_inputs", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to Suite */
   if (
          (NULL == CU_add_test(pSuite, "Test Creating Book", test01))
        ||(NULL == CU_add_test(pSuite, "Test Creating Recipe", test02))
        ||(NULL == CU_add_test(pSuite, "Test Creating Pantry", test03))
        ||(NULL == CU_add_test(pSuite, "Test Creating ingredient", test04))
        ||(NULL == CU_add_test(pSuite, "Test Adding Recipe", test05))
        ||(NULL == CU_add_test(pSuite, "Test Adding Ingredient", test06))
        ||(NULL == CU_add_test(pSuite, "Test Many Add Recipe", test07))
        ||(NULL == CU_add_test(pSuite, "Test Many Add Ingredient", test08))
        ||(NULL == CU_add_test(pSuite, "Simple storeIngredient Test", test09))
        ||(NULL == CU_add_test(pSuite, "Simple canMakeAny Test", test10))
        ||(NULL == CU_add_test(pSuite, "Simple canMakeAll Test", test11))
        ||(NULL == CU_add_test(pSuite, "Simple withinCalorieLimit Test", test12))
      )

   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using automated interface, with output to 'test-Results.xml' */
   // CU_set_output_filename("test");
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   //CU_automated_run_tests();

   CU_cleanup_registry();
   return CU_get_error();
}
