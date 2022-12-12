#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct taxDetail
{
  char panNumber[11];
  char name[20];
  float grossSalary;
  float rentReceived;
  float business;
  float capitalGains;
  float bankInterest;
  float others;
  float totalIncome;
  float deduction1;
  float deduction2;
  float deduction3;
  float deduction4;
  float deduction5;
  float ptax;
  float deduction6;
  float totalDeduction;
  float taxableIncome;
  float tax;
  float monthlyTax;
  float due;
}emp;

char line[200];

float calculation()//function for calculation of tax
{
  float tax;
  if(emp.taxableIncome<=250000)
  tax = 0;
  else if((emp.taxableIncome>250000)&&(emp.taxableIncome<=500000))
  tax = 0;
  else if((emp.taxableIncome>50000)&&(emp.taxableIncome<=1000000))
  tax = 250000*0.05 + (emp.taxableIncome-500000)*0.2;
  else
  tax = 250000*0.05 + 500000*0.2 + (emp.taxableIncome-1000000)*0.3;
  
  return tax;
}

void payableTax()//function to calculate taxable income, due amount etc.
{
  emp.taxableIncome = emp.totalIncome - emp.totalDeduction - 50000;
  printf("standard deduction = Rs.50000\n");
  printf("Total Taxable Income = %0.2f\n",emp.taxableIncome);
  emp.tax = calculation();
  printf("Payable tax per year = %0.2f\n",emp.tax);
  printf("enter monthly tax = ");
  scanf(" %f",&emp.monthlyTax);
  emp.due = emp.tax - (12*emp.monthlyTax);
  printf("tax due = %0.2f\n",emp.due);
}

void deductions()//function to take various deductions as input
{
  printf("Enter the amount given u/s 80C\n");
  printf("(PF,PPF,LIC,Tution Fees,NSC,FD,HL Principal,Sukanya Samridhi)\n");
  scanf(" %f",&emp.deduction1);
  if(emp.deduction1>150000)
  emp.deduction1=150000;
  
  printf("Enter the amount given u/s 80D\n");
  printf("(Mediclaim)\n");
  scanf(" %f",&emp.deduction2);
  if(emp.deduction2>30000)
  emp.deduction1=30000;
  
  printf("Enter the amount given u/s 80E\n");
  printf("(Higher Studies Loan)\n");
  scanf(" %f",&emp.deduction3);
  
  printf("Enter the amount given u/s 80TTA/80TTB\n");
  scanf(" %f",&emp.deduction4);
  
  printf("Enter the amount given under\n");
  printf("(HRA,LTA/LTC,EA-Entertainment Allowance)\n");
  scanf(" %f",&emp.deduction5);

  printf("Enter the amount given as professional tax\n");
  scanf(" %f",&emp.ptax);
  printf("Enter the interest given on house loan u/s 24\n");
  scanf(" %f",&emp.deduction6);
  
  emp.totalDeduction = emp.deduction1+emp.deduction2+emp.deduction3+emp.deduction4+emp.deduction5+emp.ptax+emp.deduction6;
  printf("Your net deduction(excluding standard deduction) is= %0.2f\n",emp.totalDeduction);
  payableTax();
}

void sourcesOfIncome()//function to take various sources of income as input
{
  printf("Enter Gross Salary: ");
  scanf(" %f",&emp.grossSalary);
  printf("Enter Income(rent received) from House Property: ");
  scanf(" %f",&emp.rentReceived);
  printf("Enter Income from Business/Profession: ");
  scanf(" %f",&emp.business);
  printf("Enter Income from the Head Capital Gains: ");
  scanf(" %f",&emp.capitalGains);
  printf("Enter Income from Bank Interest: ");
  scanf(" %f",&emp.bankInterest);
  printf("Enter Income from other sources: ");
  scanf(" %f",&emp.others);
  
  emp.totalIncome = emp.grossSalary + emp.rentReceived + emp.business + emp.capitalGains + emp.bankInterest + emp.others;
  printf("Your Gross Total Income (GTI)= %0.2f\n",emp.totalIncome);
  deductions();
}

void printToFile(FILE *p)//function to print the input data and calculated data on the file
{
  fprintf(p,"%s,",emp.panNumber);
  fprintf(p,"%s,",emp.name);
  fprintf(p,"%0.2f,",emp.grossSalary);
  fprintf(p,"%0.2f,",emp.rentReceived);
  fprintf(p,"%0.2f,",emp.business);
  fprintf(p,"%0.2f,",emp.capitalGains);
  fprintf(p,"%0.2f,",emp.bankInterest);
  fprintf(p,"%0.2f,",emp.others);
  fprintf(p,"%0.2f,",emp.totalIncome);
  fprintf(p,"%0.2f,",emp.deduction1);
  fprintf(p,"%0.2f,",emp.deduction2);
  fprintf(p,"%0.2f,",emp.deduction3);
  fprintf(p,"%0.2f,",emp.deduction4);
  fprintf(p,"%0.2f,",emp.deduction5);
  fprintf(p,"%0.2f,",emp.ptax);
  fprintf(p,"%0.2f,",emp.deduction6);
  fprintf(p,"%0.2f,",emp.totalDeduction);
  fprintf(p,"%0.2f,",emp.taxableIncome);
  fprintf(p,"%0.2f,",emp.tax);
  fprintf(p,"%0.2f,",emp.monthlyTax);
  fprintf(p,"%0.2f\n",emp.due);
}
void display(int n)//function to display details if it already exists in the file
{
  if(n==1)
  printf("Pan Card Number = ");
  if(n==2)
  printf("Name = ");
  if(n==3)
  printf("Gross Salary = ");
  if(n==4)
  printf("Rent Received = ");
  if(n==5)
  printf("Income from Business/Profession = ");
  if(n==6)
  printf("Capital Gains = ");
  if(n==7)
  printf("Bank interest = ");
  if(n==8)
  printf("Income from oher soureces = ");
  if(n==9)
  printf("Total income = ");
  if(n==10)
  printf("Amount given u/s 80C = ");
  if(n==11)
  printf("Amount given u/s 80D = ");
  if(n==12)
  printf("Amount given u/s 80E = ");
  if(n==13)
  printf("Amount given u/s 80TTA/80TTB = ");
  if(n==14)
  printf("Amount given under(HRA,LTA/LTC,EA) = ");
  if(n==15)
  printf("Amount given as P-Tax = ");
  if(n==16)
  printf("Interest given on house loan u/s 24 = ");
  if(n==17)
  printf("Total deduction (excluding standard deduction) = ");
  if(n==18)
 { 
   printf("standard deduction = 50000\n");
   printf("Taxable income = ");
 }
  if(n==19)
  printf("Tax= ");
  if(n==20)
  printf("Monthly tax = ");
  if(n==21)
  printf("Due amount = ");
}


int main()
{
  int n=0,i=7;
  char pan[11],*value,name[20];
 
  FILE *fptr;
  fptr=fopen("taxDetails.csv","a+");
  if(fptr==NULL)
  {
    printf("error in opening file!\n");
    exit(1);
  }
  
  printf("enter pan card number ");
  scanf(" %s",pan);
  strcpy(emp.panNumber,pan);
  rewind(fptr);
  while(fgets(line,199,fptr))
  {
    value = strtok(line,",");//for seperating the details present in the csv file
    i=strcmp(pan,value);//checking if the details against entered PAN number is already present
    if(i==0)
    { 
      printf("details found\n");
      printf("\n");
      while(value)
      {
        n+=1;
        display(n);
        printf("%s\n",value);
        value=strtok(NULL,",");
      }
    }
    n=0;
    if(i==0)
    break;
  }
  fclose(fptr);
  if(i!=0)
  {
    printf("no data found\n");
  
    FILE *p=fopen("taxDetails.csv","a");
    printf("Enter name : ");
    scanf(" %[^\n]%*c",name);
    strcpy(emp.name,name);
      
    sourcesOfIncome();
    printToFile(p);
     
    fclose(p);
  }
  
  return 0;
}







