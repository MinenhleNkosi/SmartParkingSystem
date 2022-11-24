#include<stdio.h>
#include<string.h>
struct PCP{
char vehicle_no[10];
};
struct CPW{
char vehicle_no[10];
};
struct CPWS{
char vehicle_no[10];
};


struct customer_details{
char vehicle_no[10];
char categ_parking[4];
float timein;
float timeout;
float parking_card_amount_balance;
};
struct customer_details customers[75];
struct PCP pcp_cust[25];
struct CPW cpw_cust[25];
struct CPWS cpws_cust[25];
static int count=0,count_pcp=0,count_cpw=0,count_cpws=0;
void display_categ()
{
    int i;
printf("***************************WELCOME TO CAR PARKING ZONE*********************");
printf("\n          PCP CATEGORY          CPW CATEGORY          CPWS CATEGORY\n");
    for(i=0;i<25;++i)
    {
        printf("SLOT %d    ",i+1);
        printf(" %s   \t\t%s   \t\t%s",pcp_cust[i].vehicle_no,cpw_cust[i].vehicle_no,cpws_cust[i].vehicle_no);
        printf("\n");
    }
}
void display_customer()
{
 int i;char name[10];
printf("***************************WELCOME TO CUSTOMER DETAILS*********************\n");
printf("Please Enter the vehicle no\n");
scanf("%s",name);
for(i=0;i<75;++i)
{
    if(strcmp(customers[i].vehicle_no,name)==0)
    {
        printf("VEHICLE_NO     PARKED_IN    TIME_IN    TIME_OUT    SPECIAL_CARD_BAL\n");
        printf("%s\t\t%s\t  %f\t%f\t%f\n",customers[i].vehicle_no,customers[i].categ_parking,customers[i].timein,customers[i].timeout,customers[i].parking_card_amount_balance);
        break;
    }
}
if(i==75)
    printf("No such vehicle no\n");
   printf("\n\n");
}
void do_time_in()
{
    if(count<75){
    int i;char name[10];
printf("Please enter vehicle no\n");
           scanf("%s",name);
for(i=0;i<75;++i)
{
    if(strcmp(customers[i].vehicle_no,name)==0)
       break;
}
        if(i==75)
        {
            strcpy(customers[count].vehicle_no,name);
           printf("Please enter the category to park (PCP/CPW/CPWS)\n");
           scanf("%s",name);
           if(strcmp(name,"PCP")==0)
           {
               if(count_pcp==25)
                printf("Sorry no availability in this category\n");
               else{
                    strcpy(customers[count].categ_parking,name);
                   strcpy(pcp_cust[count_pcp].vehicle_no,customers[count].vehicle_no);
                   count_pcp++;
                 }
           }
           else if(strcmp(name,"CPW")==0)
           {
                if(count_cpw==25)
                printf("Sorry no availability in this category\n");
               else{
                    strcpy(customers[count].categ_parking,name);
                strcpy(cpw_cust[count_cpw].vehicle_no,customers[count].vehicle_no);
                count_cpw++;
               }
           }
           else
           {
                 if(count_cpws==25)
                 printf("Sorry no availability in this category\n");
                 else{
                        strcpy(customers[count].categ_parking,name);
                 strcpy(cpws_cust[count_cpws].vehicle_no,customers[count].vehicle_no);
                 count_cpws++;
               }
           }
           printf("Please enter the time in\n");
           scanf("%f",&customers[count].timein);
             customers[count].parking_card_amount_balance=15000;
             ++count;


        }
        else
            printf("This vehicle no already exists\n\n\n");
    }
    else
        printf("Sorry the whole customer details list is full\n\n");
}
void do_time_out()
{
 int i,j;char name[10];
printf("Please enter vehicle no\n");
           scanf("%s",name);
for(i=0;i<75;++i)
{
    if(strcmp(customers[i].vehicle_no,name)==0)
       break;
}
        if(i!=75)
        {
            printf("Please enter time out \n");
            scanf("%f",&customers[i].timeout);


            if(strcmp(customers[i].categ_parking,"PCP")==0)
            {


                if((int)(customers[i].timeout-customers[i].timein)<=2)
                    customers[i].parking_card_amount_balance-=40;
                else
                {
                    customers[i].timein+=2;
                    customers[i].parking_card_amount_balance=customers[i].parking_card_amount_balance-((customers[i].timeout-customers[i].timein)*25)-40;
                }


                printf("Charges applied is %f\n\n",15000-customers[i].parking_card_amount_balance);


                    for(j=0;j<count_pcp;++j)
                    {
                        if(strcmp(customers[i].vehicle_no,pcp_cust[j].vehicle_no)==0)
                        {
                            for(;j<count_pcp;++j)
                            strcpy(pcp_cust[j].vehicle_no,pcp_cust[j+1].vehicle_no);
                            break;
                        }
                    }


                    strcpy(pcp_cust[count_pcp].vehicle_no,"     ");
                    count_pcp--;
            }
            else if(strcmp(customers[i].categ_parking,"CPW")==0)
            {
                if((int)(customers[i].timeout-customers[i].timein)<=2)
                    customers[i].parking_card_amount_balance-=40;
                else
                {
                    customers[i].timein+=2;
                    customers[i].parking_card_amount_balance=customers[i].parking_card_amount_balance-((customers[i].timeout-customers[i].timein)*25)-40-200;
                }


                printf("Charges applied is %f\n\n",15000-customers[i].parking_card_amount_balance);




                       for(j=0;j<count_cpw;++j)
                    {
                        if(strcmp(customers[i].vehicle_no,cpw_cust[j].vehicle_no)==0)
                        {
                            for(;j<count_cpw;++j)
                            strcpy(cpw_cust[j].vehicle_no,cpw_cust[j+1].vehicle_no);
                            break;
                        }
                    }


                    strcpy(cpw_cust[count_cpw].vehicle_no,"     ");
                    count_cpw--;
            }
            else
                {
                    if((int)(customers[i].timeout-customers[i].timein)<=2)
                    customers[i].parking_card_amount_balance-=60;
                    else
                    {
                        customers[i].timein+=2;
                        customers[i].parking_card_amount_balance=customers[i].parking_card_amount_balance-((customers[i].timeout-customers[i].timein)*40)-60-200;
                    }


                printf("Charges applied is %f\n\n",15000-customers[i].parking_card_amount_balance);


                        for(j=0;j<count_cpws;++j)
                    {
                        if(strcmp(customers[i].vehicle_no,cpws_cust[j].vehicle_no)==0)
                        {
                            for(;j<count_cpws;++j)
                            strcpy(cpws_cust[j].vehicle_no,cpws_cust[j+1].vehicle_no);
                            break;
                        }
                    }


                    strcpy(cpws_cust[count_cpws].vehicle_no,"     ");
                    count_cpws--;
                }
        }
        else
            printf("No such vehicle no exists\n\n\n");
}
int main()
{
  int choice;
   printf("WELCOME TO TEXT BASED CAR PARKING\n");
   do{
        printf("1. Do time in for a particular car\n");
        printf("2. Do time out for a particular car\n");
        printf("3. Display all cars in their respective categories\n");
        printf("4. Display Particular Customer Details\n");
        printf("5. Exit\n");
        printf("Please enter the number of your choice\n");
        scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            do_time_in();
            break;
        case 2:
               do_time_out();
               break;
        case 3:
            display_categ();
            break;
        case 4:
            display_customer();
            break;
        case 5:
            break;
        default:
            printf("Invalid Choice\n");
    }
   }while(choice!=5);
   printf("\nGood Bye !!! Have a nice day ...\n");


    return 0;
}                                          
                
