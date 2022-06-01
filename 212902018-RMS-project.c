#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};


struct node *head_menu = NULL,*tail_menu = NULL;

struct node *head_order = NULL,*tail_order = NULL;

struct node *head_sale;


// prototype function
void admin();
void displayList(struct node *head);
struct node* create_menu(struct node *head,int data, char foodname[25], float price);
int delete_menu();
struct node* delete(int data,struct node *head, struct node* tail);

void customer();
struct node* createcustomer_order(struct node *head,int data,int quantity);
int deleteorder();
void calculatetotsales();
struct node* totalsales(int data,int quantity);
struct node* deleteList(struct node* head);
void displaybill();


int main()
{
    int choice;

    head_menu = create_menu(head_menu,1,"Biriani",200);
    head_menu = create_menu(head_menu,2,"Soup",100);
    head_menu = create_menu(head_menu,3,"Noodles",50);
    head_menu = create_menu(head_menu,4,"Tea",20);
    head_menu = create_menu(head_menu,5,"Coffe",80);

    while(1)
    {
        mainmenu:
        printf("\n\t\t\t\t**************************************************************************\n");
        printf("\t\t\t\t\t\tWELCOME TO RESTAURANT MANAGEMENT SYSTEM\n");
        printf("\t\t\t\t**************************************************************************\n\n\n");
        printf("\t\t\t\t\t\t1. ADMIN  \n");
        printf("\t\t\t\t\t\t2. CUSTOMER \n");
        printf("\t\t\t\t\t\t3. Exit \n\n");

        printf("\t\t\t\t\t\tEnter Your Choice: ");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            admin();
            break;
        case 2:
            customer();
            break;
        case 3:
            printf("\n\n\t\t\t\t\t\t\t**********Thank you!!**********\n");
            exit(0);
            break;

        default:
            printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
            goto mainmenu;
        }
    }
}

struct node* create_menu(struct node *head,int data, char foodname[25], float price)
{
    struct node *newnode;
    newnode = (struct node*)malloc(sizeof(struct node));

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        head_menu = tail_menu = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = tail_menu;
        tail_menu = newnode;
    }

    return head_menu;
}


void admin()
{
    int choice;

    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");


    while(1)
    {
        printf("\n\t\t\t\t\t\t\t1. Total sales\n");
        printf("\t\t\t\t\t\t\t2. Add new items\n");
        printf("\t\t\t\t\t\t\t3. Delete items\n");
        printf("\t\t\t\t\t\t\t4. Display order menu\n");
        printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");

        printf("\t\t\t\t\t\t\t   Enter Your Choice: ");
        scanf("%d",&choice);

        if(choice==5)
            break;

        switch (choice)
        {
        case 1:
            displayList(head_sale);
            break;
        case 2:

            printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
            int num,flag = 0;
            char name[50];
            float price;
            scanf("%d",&num);

            struct node *temp = head_menu;

            while(temp!=NULL)
            {
                if(temp->data==num)
                {
                    printf("\n\t\t\t\t\t\tThis serial number is already exist!!\n\n");
                    flag = 1;
                    break;
                }
                temp = temp->next;
            }

            if(flag==1)
                break;

            printf("\t\t\t\t\t\t\tEnter food item name: ");
            scanf("%s",name);
            printf("\t\t\t\t\t\t\tEnter price: ");
            scanf("%f",&price);
            head_menu = create_menu(head_menu, num, name, price);
            printf("\n\t\t\t\t\t\t\tNew food item added !!\n\n");
            break;
        case 3:
            if(delete_menu())
            {
                printf("\n\t\t\t\t\t\tItem deleted!\n");
                displayList(head_menu);
            }
            else
                printf("\n\t\t\t\t\t\tIts not a serial number of an item !\n\n");

            break;
        case 4:
            printf("\n\t\t\t\t\t\t\t   ------ Order menu ------\n");
            displayList(head_menu);
            break;
        default:
            printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
            break;
        }
    }
}

void displayList(struct node *head)
{
    struct node *temp = head;
    if(temp==NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tNo sales!!\n\n");
    }
    else
    {
        printf("\n");
        while(temp!=NULL)
        {
            if(temp->quantity==0)
                printf("\t\t\t\t\t\t\t%d\t%s\t\t%0.2f\n",temp->data,temp->foodname,temp->price);
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t\t%d\t\t%0.2f\n",temp->data,temp->foodname,temp->quantity,temp->price);
            }

            temp = temp->next;
        }
        printf("\n");
    }

}


int delete_menu()
{
    printf("\n\t\t\t\t\tEnter the item number which you want to delete: ");
    int num;
    scanf("%d",&num);

    struct node* temp=head_menu;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            head_menu = delete(num, head_menu, tail_menu);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

struct node* delete(int data,struct node *head, struct node* tail)
{
    if(head==NULL)
    {
        printf("\n\t\t\t\t\t\t\tDelete not possible || List is empty\n");
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}


void customer()
{
    int flag=0,j=1;
    char ch;

    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");

    while(1)
    {
        customermenu:
        printf("\n\t\t\t\t\t\t\t1. Place your order\n");
        printf("\t\t\t\t\t\t\t2. View your ordered items\n");
        printf("\t\t\t\t\t\t\t3. Delete an item from order\n");
        printf("\t\t\t\t\t\t\t4. Display final bill\n");
        printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
        printf("\t\t\t\t\t\t\t   Enter Your Choice: ");

        int option;
        scanf("%d",&option);

        if(option==5)
            break;

        switch (option)
        {
        case 1:
            displayList(head_menu);
            printf("\n\t\t\t\t\t\tEnter item number which you want to order: ");
            int n;
            scanf("%d",&n);
            printf("\t\t\t\t\t\tEnter quantity: ");
            int quantity;
            scanf("%d",&quantity);
            head_order = createcustomer_order(head_order, n, quantity);
            break;
        case 2:
            printf("\n\t\t\t\t\t\t\t ------ List of ordered items ------\n");
            displayList(head_order);
            break;
        case 3:
            if(deleteorder())
            {

                printf("\n\t\t\t\t\t\t Updated list of your ordered food items \n");
                displayList(head_order);
            }
            else
                printf("\n\t\t\t\t\t\tFood item number is wrong\n");
            break;
        case 4:
            calculatetotsales();
            printf("\n\t\t\t\t\t\t\t  ------ Final Bill ------\n");
            displaybill();
            head_order = deleteList(head_order);
            goto customermenu;
            break;

        default:
            printf("\n\t\t\t\t\t\tWrong Input !!\n");
            break;
        }

    }
}



struct node* createcustomer_order(struct node *head,int data,int quantity)
{
    struct node *newnode;
    newnode = (struct node*)malloc(sizeof(struct node));

    struct node *temp = head_menu;
    int flag = 0;

    while(temp!=NULL)
    {
        if(temp->data==data)
        {
            flag = 1;
            break;
        }
        temp = temp->next;
    }

    if(flag==1)
    {
        newnode->data = data;
        newnode->price = quantity *(temp->price);
        newnode->quantity = quantity;
        strcpy(newnode->foodname,temp->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp1 = head;

        if(temp1==NULL)
            head_order = tail_order = newnode;
        else
        {
            while(temp1->next!=NULL)
                temp1=temp1->next;

            temp1->next=newnode;
            newnode->prev = tail_order;
            tail_order = newnode;
        }


    }
    else
    {
        printf("\n\t\t\t\t\t\t\tThis item is not available\n");
    }
    return head_order;
}

int deleteorder()
{
    displayList(head_order);
    printf("\n\t\t\t\t\tEnter serial number which you want to delete: ");
    int num;
    scanf("%d",&num);

    struct node* temp=head_order;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            head_order = delete(num, head_order, tail_order);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}


void calculatetotsales()
{
    struct node *temp = head_order;
    while(temp!=NULL)
    {
        head_sale = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

struct node* totalsales(int data,int quantity)
{
    struct node *newnode;
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = head_menu;

    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity *(temp1->price);
    newnode->quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_sale;

    if(temp==NULL)
        head_sale = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_sale;
}



void displaybill()
{
    displayList(head_order);

    struct node *temp = head_order;

    float total_price = 0;

    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }

    printf("\t\t\t\t\t\t\tTotal price: %0.02f\n",total_price);

}

struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=NULL)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}


