

#include <stdio.h>
#include <stdlib.h>
#include <string.h

typedef struct _category {
    int category_code;
    char category_name[17];
}category;

typedef struct _product {
    int itemcode;
    int numitems;
    float itemprice;
    float totalsales;
    char itemname[17];
    struct _product *next;
}product;

category* categories[8] = {NULL};
product* all_products_by_categories[8] = {NULL};
product* customer_products_by_categories[8] = { NULL };
int new_customer = 1;

void intialize_product_struct(product* prd);
void update_customer_product_struct_and_add_sales(product* customer_prd);
void insert_item_into_customer_list_and_add_total_sales(int itemcode, int numitems);
void insert_item_into_list(int itemcode, const char* itemname, float itemprice);
void insertCodename();
void dailytransactions();
void print_customer_receipt_format(product *new_product);
void category_inventory_format();
void deallocate_list();





product* find_product_by_itemcode(int itemcode)
{
    int category_number = itemcode / 100 - 1;
    product* product_with_proper_itemcode = all_products_by_categories[category_number];

    while (product_with_proper_itemcode->itemcode != itemcode)
    {
        product_with_proper_itemcode = product_with_proper_itemcode->next;
    }
    // now we should have product_with_proper_itemcode pointing to the right structure
    return product_with_proper_itemcode;
}
//void insert_item_into_list(product* pntr_to_list, product item_to_insert);
void intialize_product_struct(product* prd) {




        printf("\n");
        prd->itemcode = 0;
        prd->numitems = 0;
        prd->itemprice = 0.0;
        prd->totalsales = 0;
        strcpy(prd->itemname, sizeof(prd->itemname)"itemname");
        prd->next = NULL;




}
void update_customer_product_struct_and_add_sales(product* customer_prd)
{
    // receive struct with only itemcode and numitems known;
    // populate it with the rest known info by taking it from all_products_by_categories

    // find the right product by itemcode which customer purchased
    product* database_prd = find_product_by_itemcode(customer_prd->itemcode);

    // copy data into customer's record
    //customer_prd->itemcode - already have
    //customer_prd->numitems - already have
    customer_prd->itemprice = database_prd->itemprice;
    strcpy(customer_prd->itemname, sizeof(customer_prd->itemname), database_prd->itemname);
    customer_prd->totalsales = customer_prd->itemprice*customer_prd->numitems;
    customer_prd->next = NULL;

    // add sale to the all_products_by_categories array through corresponding pointer database_prd
    database_prd->numitems = database_prd->numitems + customer_prd->numitems;
    database_prd->totalsales = database_prd->totalsales + customer_prd->totalsales;





}

void insert_item_into_list(int itemcode, const char* itemname, float itemprice)
{
    // create and instert new product structure into the   *all_products_by_categories[8]

    // find category number from itemcode
    int category_number = itemcode / 100 - 1;

    // create new record for the new item; it will be a new node on the list of products
    product *new_product = (product *) malloc(sizeof(product));
    intialize_product_struct(new_product);
    new_product->itemcode = itemcode;
    new_product->itemprice = itemprice;
    strcpy(new_product->itemname,new_product->itemname), itemname);

    product* pntr_to_last_item_in_list = all_products_by_categories[category_number];
    if (pntr_to_last_item_in_list != NULL)
    {
        //find last item in list
        while (pntr_to_last_item_in_list->next != NULL)
        {
            pntr_to_last_item_in_list = pntr_to_last_item_in_list->next;
        }
        // now pntr_to_last_item_in_list points to the last element in the list;
        // assign its pointer to the newly created product structure
        pntr_to_last_item_in_list->next = new_product;
    }
    else // insert first item in the array at given index
    {
        // assign pointer to the newly created product structiure
        all_products_by_categories[category_number] = new_product;
        int y = 1;
    }

}

void insert_item_into_customer_list_and_add_total_sales(int itemcode, int numitems)
{
    //check if customer_products_by_categories array is empty
    if(new_customer == 0 )
    for(int i = 0; i < 8; i++)
    {
        if(customer_products_by_categories[i] != NULL) {
            deallocate_list(customer_products_by_categories[i]);
            customer_products_by_categories[i] = NULL;
        }
    }

    // create and insert new product struct into the *customer_products_by_categories[8]

    // create new record for the new item; it will be a new node on the list of products
    product *new_product = (product *)malloc(sizeof(product));
    new_product->itemcode = itemcode;
    new_product->numitems = numitems;
    update_customer_product_struct_and_add_sales(new_product);

    // find category number from itemcode
    int category_number = itemcode / 100 - 1;

    product* pntr_to_item_with_smaller_itemcode = customer_products_by_categories[category_number];
    product* hold;
    if (pntr_to_item_with_smaller_itemcode != NULL)
    {
        // see if itemcode is smaller than first item on the list
        if (itemcode < pntr_to_item_with_smaller_itemcode->itemcode)
        {
            hold = customer_products_by_categories[category_number];
            customer_products_by_categories[category_number] = new_product;
            new_product->next = hold;
        }

        else {
            //find item in the list with bigger itemnumber and insert before it (to keep items sorted)

            while (pntr_to_item_with_smaller_itemcode->next != NULL && pntr_to_item_with_smaller_itemcode->next->itemcode < itemcode)
            {
                pntr_to_item_with_smaller_itemcode = pntr_to_item_with_smaller_itemcode->next;
            }

            // now pntr_to_item_with_smaller_itemcode points to the element before the one with bigger itemcode
            // assign its pointer to the newly created product structure
            hold = pntr_to_item_with_smaller_itemcode->next;
            pntr_to_item_with_smaller_itemcode->next = new_product;
            new_product->next = hold;
        }
    }
    else // insert first item in the array at given index
    {
        // assign pointer to the newly created product structure
        customer_products_by_categories[category_number] = new_product;
        int y = 1;
    }


}


//open file
void insertCodename(){
    FILE *ff;
    char category_name[17];
    int category_code;
    float price;

    if ((ff = fopen("CodeNamePrice.dat", "r")) == NULL) {
        printf("Error! opening file");

        exit(1);
    }


    do {
        fscanf(ff, " %d\t%[^\t]%f ", &category_code, category_name, &price);
        insert_item_into_list(category_code, category_name,price);

        if(category_code < 101 || category_code > 888)
            continue;

        if(category_code == 0)
            continue;

        if(price == 0.0)
            continue;
        printf("%d %s %.2f", category_code, category_name, price);
        //printf("");

    }
    while(!feof(ff));

}

void dailytransactions() {

    FILE *ff;
    int barcode, numitems;

    if ((ff = fopen("DailyTransactions.dat", "r")) == NULL) {
        printf("could not open");


        exit(1);
    }
    printf("\n\n");

    do {

        fscanf(ff, " %d\t%d", &barcode, &numitems);
        insert_item_into_customer_list_and_add_total_sales(barcode,numitems);


        printf("%d %d", barcode, numitems);
        printf("\n");
    }while(!feof(ff));


print_customer_receipt_format(customer_products_by_categories);
     free_array_of_lists(customer_products_by_categories);

}
// print the customer receipt
void print_customer_receipt_format(customer_products_by_categories) {
    printf("customer receipt");
    printf("Code   Item   Name   Price   NumItem   Total Sales");
    while (product* all_products_by_categories != NULL) {
        printf("%3d%17s%.2f%1d%.2f", new_product->itemcode, new_product->itemname, new_product->itemprice,
               new_product->numitems, new_product->totalsales);
        product = product->next;
    }
}

void category_inventory_format(customer_products_by_categories){
    printf("category name\n");
    printf("category code");
    printf("Code    Item Name   NumItems    Total Sales")
    while(customer_products_by_categories != NULL)
    printf("%d %s %d %.2f,
           
    
}
           
           // call after every receipt is printed

                  
void free_array_of_lists(customer_products_by_categories){
   // call at the end of program

        void free_array_of_lists(product** arr)
        {
               // deallocate array of lists
            for (int i = 0; i < 8; i++)
            {
                if (arr[i])
                {
                       free_list_of_products(arr[i]);
                   }
               }
           }
    }
           
           
           
void free_list_of_products(product* lst)
{
   // deallocate one of pointers with list of products
   if (lst)
   {
       product* hold1 = lst;
       product* hold2 = hold1->next;
       do
       {
           free(hold1);
           hold1 = hold2;
           if (hold1 != NULL)
    {
               hold2 = hold1->next;
           }
       } while (hold1 != NULL);
   }
}

int main(void) {
    int c = 0;

    FILE *ff;
    char category_name[17];
    int category_code;

    if ((ff = fopen("CategoryName.dat", "r")) == NULL) {
        printf("could not open");

        exit(1);
    }
    do {

        fscanf(ff, " %d\t%[^\n] ", &category_code, category_name);


        printf("%d %s", category_code, category_name);
        printf("\n");
        //strcpy(hold->ctgryy_names, category_name);

    }
    while(!feof(ff));

    printf("\n");

    fclose(ff);



    insertCodename();
    dailytransactions();
    free_array_of_lists(all_products_by_categories);



/*
    do {
        category *hold = (category *) malloc(sizeof(category));
        fscanf(ff, " %d\t%[^\n] ", &category_code, category_name);
        printf("%d %s", category_code, category_name);

    }while(!feof(ff));
*/



        // two main global structures here:
        //product* all_products_by_categories[8] = { NULL }; contains all products the store sells; populated with multiple calls of insert_item_into_list()
        //product* customer_products_by_categories[8] = { NULL }; contains all products the curtomer bought; populated with multiple calls of insert_item_into_customer_list()


        insert_item_into_list(101, "Orange", 5.10);
        insert_item_into_list(102, "Banana",2.39);
        insert_item_into_list(103, "Apple", 2.39);
        insert_item_into_list(104, "Peach",4.10);
        insert_item_into_list(121, "Tomato",5.10);
        insert_item_into_list(122, "Potato",4.90);
        insert_item_into_list(203, "Sausage",3.10);
        insert_item_into_list(210, "Hotdog",2.10);

        insert_item_into_customer_list_and_add_total_sales(102, 2);
        insert_item_into_customer_list_and_add_total_sales(104, 4);
        insert_item_into_customer_list_and_add_total_sales(101, 5);
        insert_item_into_customer_list_and_add_total_sales(103, 8);
        insert_item_into_customer_list_and_add_total_sales(122, 8);
        insert_item_into_customer_list_and_add_total_sales(121, 8);

        int i = 1;






    }

/*
if(barcode < 101 || barcode > 888)
continue;

if(barcode == 0)
continue;

if(price == 0.0)
continue;
 */
