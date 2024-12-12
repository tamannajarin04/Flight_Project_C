#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define username_length 50
#define password_length 50
#define first_name_length 25
#define last_name_length 25
#define passport_length 20
#define mobile_length 12
#define destination_length 25

FILE *Agent_Registration,*Passenger_Booking,*Flight_Schedule;

void Registration()
{
    system("CLS");

    Agent_Registration = fopen("Agent_Registration.txt","a+");
    if(Agent_Registration == NULL){
        printf("Error Opening Passenger Registration File\n");
        return;
    }

    char Username[username_length];
    char Password[password_length];

    printf("\n\n\n\t\t\t\t\t\t   ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    User Registration    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");
    printf(" ");

    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t     #Enter a Username: ");
    scanf("%s",&Username);

    printf("\n");

    printf("\n\n\t\t\t\t\t\t\t\t     #Enter a Password: ");
    scanf("%s",&Password);

    fprintf(Agent_Registration,"%s %s\n",Username,Password);
    fclose(Agent_Registration);

    Loading();
    system("CLS");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t         *** User Registration Successful ***\n");
    printf("\n\n\n\nPress any key to continue...");
    getch();
}

void Login()
{
    system("CLS");

    Agent_Registration = fopen("Agent_Registration.txt","a+");
    if(Agent_Registration == NULL){
        printf("Error Opening Passenger Registration File\n");
        return;
    }

    char line[username_length + password_length + 2];

    char saved_username[username_length];
    char saved_password[password_length];

    char Username[username_length];
    char Password[password_length];

    printf("\n\n\n\t\t\t\t\t\t      ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    User Login    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");
    printf(" ");

    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t    #Enter Your Username: ");
    scanf("%s",&Username);

    printf("\n\n\t\t\t\t\t\t\t\t    #Enter Your Password: ");
    scanf("%s",&Password);

    int found = 0;

    while(fgets(line,sizeof(line),Agent_Registration) != NULL){
        sscanf(line,"%s %s",saved_username,saved_password);

        if(strcmp(Username,saved_username)==0 && strcmp(Password,saved_password)==0){
            found = 1;
            break;
        }
    }

    fclose(Agent_Registration);

    Loading();

    if(found){
       system("CLS");
       printf("\n\n\n\n\n\t\t\t\t\t\t\t            *** User Login Successful ***\n");
       printf("\n\n\n\nPress any key to continue...");
       getch();
       system("CLS");
       Main_Menu();
    }
    else{
       system("CLS");
       printf("\n\n\n\n\n\t\t\t\t\t\t\t            *** User Login Unsuccessful ***\n");
       printf("\n\n\n\nPress any key to try again...");
       getch();
       Login_Page();
    }
}

void Change_Password()
{
    system("COLOR 0A");
    FILE *Temporary_2;
    Temporary_2 = fopen("Temporary_2.txt","a+");
    if(Temporary_2 == NULL){
        printf("Error Opening Temporary_2 File\n");
        return;
    }

    Agent_Registration = fopen("Agent_Registration.txt","a+");
    if(Agent_Registration == NULL){
        printf("Error Opening Passenger Registration File\n");
        return;
    }

    char line[username_length + password_length + 2];

    char saved_username[username_length];
    char saved_password[password_length];

    char Username[username_length];
    char Password[password_length];
    char New_Password[password_length];

    printf("\n\n\n\t\t\t\t\t\t      ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    Change Password    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");

    printf("\n\n\n\t\t\t#Enter Your Username: ");
    scanf("%s",&Username);

    printf("\n");

    printf("\t\t\t#Enter Your Old Password: ");
    scanf("%s",&Password);

    printf("\n");

    printf("\t\t\t#Enter Your New Password: ");
    scanf("%s",&New_Password);

    int found = 1;

    while(fgets(line,sizeof(line),Agent_Registration) != NULL){
        sscanf(line,"%s %s",saved_username,saved_password);

        if(strcmp(Username,saved_username)==0 && strcmp(Password,saved_password)==0){
            found = 0;
            continue;
        }

        fprintf(Temporary_2,"%s %s\n",saved_username,saved_password);
    }

    if(found==0){
        fprintf(Temporary_2,"%s %s\n",Username,New_Password);
    }

    fclose(Temporary_2);
    fclose(Agent_Registration);

    if(found){
        if(remove("Temporary_2.txt") != 0){
            printf("Error Deleting Temporary_2 File\n");
            return;
        }
        printf("\n\n\n\n\n\t\t\t\t\t\t\t          !!! Incorrect Username & Password !!!\n");
        printf("\n\n\n  \n\nPress any key to back to the home page...");
        getch();
        system("CLS");
        Main_Menu();
    }

    else{
        int check = 1;
        if(remove("Agent_Registration.txt") != 0){
            check = 0;
            printf("Error Deleting Agent_Registration File\n");
            return;
        }

        if(rename("Temporary_2.txt","Agent_Registration.txt") !=0){
            check = 0;
            printf("Error Renaming Temporary_2 File\n");
            return;
        }

        if(check){
            printf("\n\n\n\n\n\t\t\t\t\t\t\t           *** Password Changed Successfully ***\n");
        }
        else{
            printf("\n\n\n\n\n\t\t\t\t\t\t\t        !!! Failed! Something Went Wrong. Try Again !!!\n");
        }
        printf("\n\n\n  \n\nPress any key to back to the home page...");
        getch();
        system("CLS");
        Main_Menu();
    }

}

void Book_Ticket()
{
    system("COLOR 0A");
    Passenger_Booking = fopen("Passenger_Booking.txt","a+");
    if(Passenger_Booking == NULL){
        printf("Error Opening Passenger Booking File\n");
        return;
    }

    Flight_Schedule = fopen("Flight_Schedule.txt","a+");
    if(Flight_Schedule == NULL){
        printf("Error Opening Flight Schedule File\n");
        return;
    }

    char from_1[destination_length];
    char to_1[destination_length];
    char flight_time_1[6];
    char price_1[12];
    char flight_time[6];
    char price[12];

    char username[username_length];
    char first_name[first_name_length];
    char last_name[last_name_length];
    char passport_no[passport_length];
    char mobile_no[mobile_length];
    char destination_from[destination_length];
    char destination_to[destination_length];
    int dd;
    int mm;
    int yyyy;
    char seat_no[3];

    char username_1[username_length];
    char first_name_1[first_name_length];
    char last_name_1[last_name_length];
    char passport_no_1[passport_length];
    char mobile_no_1[mobile_length];
    char destination_from_1[destination_length];
    char destination_to_1[destination_length];
    int dd_1;
    int mm_1;
    int yyyy_1;
    char seat_no_1[3];

    printf("\n\n\n\t\t\t\t\t\t\t");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    Book Ticket    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");

    printf("\n\n\n\t\t\t#Enter Your Username: ");
    scanf("%s",&username);

    printf("\n\n\t\t\t\t\t\t\t\t*** Provide Passenger's Information Here *** \n\n\n");

    printf("\n\n\t\t\t#Enter Firstname: ");
    scanf("%s",&first_name);

    printf("\n\n\t\t\t#Enter Lastname: ");
    scanf("%s",&last_name);

    printf("\n\n\t\t\t#Enter Passport/NID No: ");
    scanf("%s",&passport_no);

    printf("\n\n\t\t\t#Enter Mobile No: ");
    scanf("%s",&mobile_no);

    char line[destination_length+destination_length+6+12+4];
    int check = 1;

    while(check){
        rewind(Flight_Schedule);

        printf("\n\n\t\t\t\t\t\t\t\t     *** Enter Destination Here ***\n");
        printf("\n\n\t\t\t#From: ");
        scanf("%s",&destination_from);

        printf("\n\n\t\t\t#To: ");
        scanf("%s",&destination_to);

        while(fgets(line,sizeof(line),Flight_Schedule)!= NULL){
            sscanf(line,"%s %s %s %s",from_1,to_1,flight_time_1,price_1);
            if((strcmp(destination_from,from_1)==0)&&(strcmp(destination_to,to_1)==0)){
                strcpy(flight_time,flight_time_1);
                strcpy(price,price_1);
                check = 0;
                break;
            }
        }
        if(check){
            printf("\n\n\t\t\t\t\t\t\t\t     !!! No Available Route Found !!!\n");
        }
    }

    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    int day = date.tm_mday;
    int month = date.tm_mon+1;
    int year = date.tm_year+1900;
    int day1,month1=month,year1=year;
    int day2,month2=month,year2=year;

    if(month==3||month==5||month==7||month==8||month==10){
        day1 = day + 30;
        if(day1>31){
            day1 = day1 - 31;
            month1++;
        }
    }
    else if(month==4||month==6||month==9||month==11){
        day1 = day + 30;
        if(day1>30){
            day1 = day1 - 30;
            month1++;
        }
    }
    else if(month==12){
        day1 = day + 30;
        if(day1>31){
            day1 = day1 - 31;
            month1 = 1;
            year1++;
        }
    }
    else if(month==2){
        if((year%4==0&&year%100!=0)||(year%400==0)){
            day1 = day + 30;
            if(day1>29){
                day1 = day1 - 29;
                month1++;
            }
        }
        else{
            day1 = day + 30;
            if(day1>28){
                day1 = day1 - 28;
                month1++;
            }
        }
    }
    else{
        if((year%4==0&&year%100!=0)||(year%400==0)){
            if(day == 31){
                day1 = 1;
                month1 = month1 + 2;
            }
            else{
                day1 = day + 30;
                if(day1>31){
                    day1 = day1 - 31;
                    month1++;
                }
            }
        }
        else{
            if(day == 31){
                day1 = 2;
                month1 = month1 + 2;
            }
            else if(day == 30){
                day1 = 1;
                month1 = month1 + 2;
            }
            else{
                day1 = day + 30;
                if(day1>31){
                    day1 = day1 - 31;
                    month1++;
                }
            }
        }
    }

    if(month==1||month==3||month==5||month==7||month==8||month==10){
        day2 = day + 1;
        if(day2>31){
            day2 = day2 - 31;
            month2++;
        }
    }
    else if(month==4||month==6||month==9||month==11){
        day2 = day + 1;
        if(day2>30){
            day2 = day2 - 30;
            month2++;
        }
    }
    else if(month==12){
        day2 = day + 1;
        if(day2>31){
            day2 = day2 - 31;
            month2 = 1;
            year2++;
        }
    }
    else if(month==2){
        if((year%4==0&&year%100!=0)||(year%400==0)){
            day2 = day + 1;
            if(day2>29){
                day2 = day2 - 29;
                month2++;
            }
        }
        else{
            day2 = day + 1;
            if(day2>28){
                day2 = day2 - 28;
                month2++;
            }
        }
    }

    printf("\n\n\t\t\t#Enter The Travel date Between (%02d-%02d-%d) to (%02d-%02d-%d): ",day2,month2,year2,day1,month1,year1);
    scanf("%d",&dd);
    scanf("%d",&mm);
    scanf("%d",&yyyy);

    char line1[username_length + first_name_length + last_name_length + passport_length + mobile_length + destination_length + destination_length + 3 + 6 + 12 + 3 + 3 + 5 + 13];

    int check1 = 1;

    while(check1){
        rewind(Passenger_Booking);
        printf("\n\n\t\t\t\t\t\t\t\t     *** Select a Seat From Below ***\n\n");
        printf("\n\n\t\t\tA1  A2\t\tA3  A4\t\tA5  A6\n\n\t\t\tB1  B2\t\tB3  B4\t\tB5  B6\n\n\t\t\tC1  C2\t\tC3  C4\t\tC5  C6\n\n");
        printf("\t\t\tD1  D2\t\tD3  D4\t\tD5  D6\n\n\t\t\tE1  E2\t\tE3  E4\t\tE5  E6\n\n\t\t\tF1  F2\t\tF3  F4\t\tF5  F6\n\n");
        printf("\t\t\tG1  G2\t\tG3  G4\t\tG5  G6\n\n\t\t\tH1  H2\t\tH3  H4\t\tH5  H6\n\n\t\t\tI1  I2\t\tI3  I4\t\tI5  I6\n\n");
        printf("\n\n\t\t\t#Enter The Seat Number: ");
        scanf("%s",&seat_no);
        check1 = 0;
        while(fgets(line1,sizeof(line1),Passenger_Booking)!=NULL){
            sscanf(line1,"%s %s %s %s %s %s %s %s %s %s %d %d %d",username_1,first_name_1,last_name_1,passport_no_1,mobile_no_1,destination_from_1,destination_to_1,seat_no_1,flight_time_1,price_1,&dd_1,&mm_1,&yyyy_1);
            if((strcmp(destination_from,destination_from_1)==0)&&(strcmp(destination_to,destination_to_1)==0)&&(dd==dd_1)&&(mm==mm_1)&&(yyyy==yyyy_1)&&(strcmp(seat_no,seat_no_1)==0)){
                check1 = 1;
                break;
            }
            else{
                check1 = 0;
            }
        }
    }

    printf("\n\n\n\t\t\t#Ticket Price: %s\n",price);
    printf("\n\n\t\t\t#Flight Time (24 hour format): %s\n",flight_time);

    fprintf(Passenger_Booking,"%s %s %s %s %s %s %s %s %s %s %d %d %d\n",username,first_name,last_name,passport_no,mobile_no,destination_from,destination_to,seat_no,flight_time,price,dd,mm,yyyy);
    fclose(Passenger_Booking);
    fclose(Flight_Schedule);

    printf("\n\n\t\t\t\t\t\t\t\t\t*** Ticket Booking Successful ***");
    printf("\n\n\n  \n\nPress any key to back to the home page...");
    getch();
    system("CLS");
    Main_Menu();
}

void Sold_By_Agent()
{
    system("COLOR 0A");
    Passenger_Booking = fopen("Passenger_Booking.txt","a+");
    if(Passenger_Booking == NULL){
        printf("Error Opening Passenger Booking File\n");
        return;
    }

    char Username[username_length];

    char username_1[username_length];
    char first_name_1[first_name_length];
    char last_name_1[last_name_length];
    char passport_no_1[passport_length];
    char mobile_no_1[mobile_length];
    char destination_from_1[destination_length];
    char destination_to_1[destination_length];
    char seat_no_1[3];
    char flight_time_1[6];
    char price_1[12];

    int dd_1;
    int mm_1;
    int yyyy_1;

    printf("\n\n\n\t\t\t\t\t     ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    All Bookings History of a Agent    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");

    printf("\n\n\n\t\t\t#Enter Your Username: ");
    scanf("%s",&Username);

    printf("\n\n\n");

    char line[username_length + first_name_length + last_name_length + passport_length + mobile_length + destination_length + destination_length + 3 + 6 + 12 + 3 + 3 + 5 + 13];

    while(fgets(line,sizeof(line),Passenger_Booking) != NULL){
        sscanf(line,"%s %s %s %s %s %s %s %s %s %s %d %d %d",username_1,first_name_1,last_name_1,passport_no_1,mobile_no_1,destination_from_1,destination_to_1,seat_no_1,flight_time_1,price_1,&dd_1,&mm_1,&yyyy_1);
        if(strcmp(Username,username_1)==0){
            printf("\t\t\t### Passenger Name: %s %s\n\n",first_name_1,last_name_1);
            printf("\t\t\t### Passport/NID No: %s\n\n",passport_no_1);
            printf("\t\t\t### Mobile No: %s\n\n",mobile_no_1);
            printf("\t\t\t### Destination: %s to %s\n\n",destination_from_1,destination_to_1);
            printf("\t\t\t### Travelling Date: %02d-%02d-%d\n\n",dd_1,mm_1,yyyy_1);
            printf("\t\t\t### Seat No: %s\n\n",seat_no_1);
            printf("\t\t\t### Ticket Price: %s\n\n",price_1);
            printf("\t\t\t### Flight Time (24 hour format): %s\n\n\n\n",flight_time_1);
        }
    }
    fclose(Passenger_Booking);
    printf("\n\n\n  \n\nPress any key to back to the home page...");
    getch();
    system("CLS");
    Main_Menu();
}

void Search_Booking()
{
    system("COLOR 0A");
    Passenger_Booking = fopen("Passenger_Booking.txt","a+");
    if(Passenger_Booking == NULL){
        printf("Error Opening Passenger Booking File\n");
        return;
    }

    char Passport_No[passport_length];

    char username_1[username_length];
    char first_name_1[first_name_length];
    char last_name_1[last_name_length];
    char passport_no_1[passport_length];
    char mobile_no_1[mobile_length];
    char destination_from_1[destination_length];
    char destination_to_1[destination_length];
    char seat_no_1[3];
    char flight_time_1[6];
    char price_1[12];

    int dd_1;
    int mm_1;
    int yyyy_1;

    printf("\n\n\n\t\t\t\t\t      ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    Search Passenger's Booking    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");

    printf("\n\n\n\t\t\t#Enter a Passport/NID No: ");
    scanf("%s",&Passport_No);

    printf("\n\n\n");

    char line[username_length + first_name_length + last_name_length + passport_length + mobile_length + destination_length + destination_length + 3 + 6 + 12 + 3 + 3 + 5 + 13];

    while(fgets(line,sizeof(line),Passenger_Booking) != NULL){
        sscanf(line,"%s %s %s %s %s %s %s %s %s %s %d %d %d",username_1,first_name_1,last_name_1,passport_no_1,mobile_no_1,destination_from_1,destination_to_1,seat_no_1,flight_time_1,price_1,&dd_1,&mm_1,&yyyy_1);
        if(strcmp(Passport_No,passport_no_1)==0){
            printf("\t\t\t### Passenger Name: %s %s\n\n",first_name_1,last_name_1);
            printf("\t\t\t### Passport/NID No: %s\n\n",passport_no_1);
            printf("\t\t\t### Mobile No: %s\n\n",mobile_no_1);
            printf("\t\t\t### Destination: %s to %s\n\n",destination_from_1,destination_to_1);
            printf("\t\t\t### Travelling Date: %02d-%02d-%d\n\n",dd_1,mm_1,yyyy_1);
            printf("\t\t\t### Seat No: %s\n\n",seat_no_1);
            printf("\t\t\t### Ticket Price: %s\n\n",price_1);
            printf("\t\t\t### Flight Time (24 hour format): %s\n\n\n\n",flight_time_1);
        }
    }
    fclose(Passenger_Booking);
    printf("\n\n\n  \n\nPress any key to back to the home page...");
    getch();
    system("CLS");
    Main_Menu();
}

void All_Bookings()
{
    system("COLOR 0A");
    Passenger_Booking = fopen("Passenger_Booking.txt","a+");
    if(Passenger_Booking == NULL){
        printf("Error Opening Passenger Booking File\n");
        return;
    }

    char username_1[username_length];
    char first_name_1[first_name_length];
    char last_name_1[last_name_length];
    char passport_no_1[passport_length];
    char mobile_no_1[mobile_length];
    char destination_from_1[destination_length];
    char destination_to_1[destination_length];
    char seat_no_1[3];
    char flight_time_1[6];
    char price_1[12];

    int dd_1;
    int mm_1;
    int yyyy_1;

    printf("\n\n\n\t\t\t\t\t         ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    All Booking History    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");
    printf(" \n\n");

    char line[username_length + first_name_length + last_name_length + passport_length + mobile_length + destination_length + destination_length + 3 + 6 + 12 + 3 + 3 + 5 + 13];

    while(fgets(line,sizeof(line),Passenger_Booking) != NULL){
        sscanf(line,"%s %s %s %s %s %s %s %s %s %s %d %d %d",username_1,first_name_1,last_name_1,passport_no_1,mobile_no_1,destination_from_1,destination_to_1,seat_no_1,flight_time_1,price_1,&dd_1,&mm_1,&yyyy_1);
        printf("\t\t\t### Passenger Name: %s %s\n\n",first_name_1,last_name_1);
        printf("\t\t\t### Passport/NID No: %s\n\n",passport_no_1);
        printf("\t\t\t### Mobile No: %s\n\n",mobile_no_1);
        printf("\t\t\t### Destination: %s to %s\n\n",destination_from_1,destination_to_1);
        printf("\t\t\t### Travelling Date: %02d-%02d-%d\n\n",dd_1,mm_1,yyyy_1);
        printf("\t\t\t### Seat No: %s\n\n",seat_no_1);
        printf("\t\t\t### Ticket Price: %s\n\n",price_1);
        printf("\t\t\t### Flight Time (24 hour format): %s\n\n\n\n",flight_time_1);
    }
    fclose(Passenger_Booking);
    printf("\n\n\n  \n\nPress any key to back to the home page...");
    getch();
    system("CLS");
    Main_Menu();
}

void Cancel_Ticket()
{
    system("COLOR 0A");
    FILE *Temporary;
    Temporary = fopen("Temporary.txt","a+");
    if(Temporary == NULL){
        printf("Error Opening Temporary File\n");
        return;
    }

    Passenger_Booking = fopen("Passenger_Booking.txt","a+");
    if(Passenger_Booking == NULL){
        printf("Error Opening Passenger Booking File\n");
        return;
    }

    char Passport_No[passport_length];

    char username_1[username_length];
    char first_name_1[first_name_length];
    char last_name_1[last_name_length];
    char passport_no_1[passport_length];
    char mobile_no_1[mobile_length];
    char destination_from_1[destination_length];
    char destination_to_1[destination_length];
    char seat_no_1[3];
    char flight_time_1[6];
    char price_1[12];

    int dd_1;
    int mm_1;
    int yyyy_1;

    int found = 1;

    printf("\n\n\n\t\t\t\t\t\t      ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    Cancel Ticket    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");

    printf("\n\n\n\t\t\t#Please Enter Passport/NID No: ");
    scanf("%s",&Passport_No);
    printf("\n\n");

    char line[username_length + first_name_length + last_name_length + passport_length + mobile_length + destination_length + destination_length + 3 + 6 + 12 + 3 + 3 + 5 + 13];

    while(fgets(line,sizeof(line),Passenger_Booking) != NULL){
        sscanf(line,"%s %s %s %s %s %s %s %s %s %s %d %d %d",username_1,first_name_1,last_name_1,passport_no_1,mobile_no_1,destination_from_1,destination_to_1,seat_no_1,flight_time_1,price_1,&dd_1,&mm_1,&yyyy_1);
        if((strcmp(Passport_No,passport_no_1)==0)){
            found = 0;
            printf("\t\t\t### Passenger Name: %s %s\n\n",first_name_1,last_name_1);
            printf("\t\t\t### Passport/NID No: %s\n\n",passport_no_1);
            printf("\t\t\t### Mobile No: %s\n\n",mobile_no_1);
            printf("\t\t\t### Destination: %s to %s\n\n",destination_from_1,destination_to_1);
            printf("\t\t\t### Travelling Date: %02d-%02d-%d\n\n",dd_1,mm_1,yyyy_1);
            printf("\t\t\t### Seat No: %s\n\n",seat_no_1);
            printf("\t\t\t### Ticket Price: %s\n\n",price_1);
            printf("\t\t\t### Flight Time (24 hour format): %s\n\n\n\n",flight_time_1);
            continue;
        }
        fprintf(Temporary,"%s %s %s %s %s %s %s %s %s %s %d %d %d\n",username_1,first_name_1,last_name_1,passport_no_1,mobile_no_1,destination_from_1,destination_to_1,seat_no_1,flight_time_1,price_1,dd_1,mm_1,yyyy_1);
    }

    fclose(Temporary);
    fclose(Passenger_Booking);

    if(found){
        if(remove("Temporary.txt") != 0){
           printf("Error Deleting Temporary File\n");
           return;
        }
        printf("\n\n\n\t\t\t\t\t\t\t\t        !!! No Passenger Found !!!");
        printf("\n\n\n  \n\nPress any key to back to the home page...");
        getch();
        system("CLS");
        Main_Menu();
    }

    else{
        printf("\t\t\tDo You Want to Cancel This Ticket?\n\n");
        printf("\t\t\t1. Yes\n");
        printf("\t\t\t2. No\n\n");

        printf("\t\t\tEnter Your Choice: ");
        int choice1,count=0;
        scanf("%d",&choice1);

        if(choice1==1){
            count = 1;
            if(remove("Passenger_Booking.txt") != 0){
                printf("Error Deleting Passenger Booking File\n");
                count=0;
                return;
            }

            if(rename("Temporary.txt","Passenger_Booking.txt") != 0){
                printf("Error Renaming Temporary File\n");
                count=0;
                return;
            }
        }
        else{
            if(remove("Temporary.txt") != 0){
                printf("Error Deleting Temporary File\n");
                return;
            }
        }

        if(count){
            printf("\n\n\n\t\t\t\t\t\t\t\t        *** Ticket Canceled ***");
        }
        else{
            printf("\n\n\n\t\t\t\t\t\t\t\t        !!! Ticket Cancel Failed !!!");
        }
        printf("\n\n\n  \n\nPress any key to back to the home page...");
        getch();
        system("CLS");
        Main_Menu();
        }
}

void Add_Flight()
{
    system("COLOR 0A");
    Flight_Schedule = fopen("Flight_Schedule.txt","a+");
    if(Flight_Schedule == NULL){
        printf("Error Opening Flight Schedule File\n");
        return;
    }

    char destination_from[destination_length];
    char destination_to[destination_length];
    char flight_time[6];
    char price[10];

    char destination_from_1[destination_length];
    char destination_to_1[destination_length];
    char flight_time_1[6];
    char price_1[12];

    char line[destination_length+destination_length+6+12+4];
    int check = 1;

    while(check){
        rewind(Flight_Schedule);

        printf("\n\n\n\t\t\t\t\t\t    ");
        for(int i=0;i<20;i++)
        {
            printf("\xB1");
        }
        printf("    Add Flight Details    ");
        for(int i=0;i<20;i++)
        {
            printf("\xB1");
        }
        printf("\n\n\n");

        printf("\n\t\t\t# From: ");
        scanf("%s",&destination_from);

        printf("\n\n\t\t\t# To: ");
        scanf("%s",&destination_to);

        printf("\n\n\t\t\t# Flight Time: ");
        scanf("%s",&flight_time);

        printf("\n\n\t\t\t# Price: ");
        scanf("%s",&price);

        check = 0;
        while(fgets(line,sizeof(line),Flight_Schedule)!=NULL){
            sscanf(line,"%s %s %s %s",destination_from_1,destination_to_1,flight_time_1,price_1);
            if((strcmp(destination_from_1,destination_from)==0)&&(strcmp(destination_to_1,destination_to)==0)){
                printf("\n\n\t\t\t\t\t\t\t\t*** Already Have This Flight.....Try Again ***\n\n");
                check = 1;
                break;
            }
            else{
                check = 0;
            }
        }
    }

    fprintf(Flight_Schedule,"%s %s %s %s\n",destination_from,destination_to,flight_time,price);
    printf("\n\n\n\t\t\t\t\t\t\t\t     *** Flight Added Successfully ***\n\n");

    fclose(Flight_Schedule);
    printf("\n\n\n  \n\nPress any key to back to the home page...");
    getch();
    system("CLS");
    Main_Menu();
}

void View_Flight_Schedule()
{
    system("COLOR 0A");
    Flight_Schedule = fopen("Flight_Schedule.txt","a+");
    if(Flight_Schedule == NULL){
        printf("Error Opening Flight Schedule File\n");
        return;
    }

    char destination_from_1[destination_length];
    char destination_to_1[destination_length];
    char flight_time_1[6];
    char price_1[12];
    printf("\n\n\n\t\t\t\t\t\t   ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    All Flight Schedule    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");
    char line[destination_length+destination_length+6+12+4];
    int count = 1;

    while(fgets(line,sizeof(line),Flight_Schedule)!=NULL){
            sscanf(line,"%s %s %s %s",destination_from_1,destination_to_1,flight_time_1,price_1);
            printf("\n\n\t\t\t#Flight %d Details: %s to %s at %s <<local time>>    (Everyday)\n\t\t\t# Price: %s\n",count,destination_from_1,destination_to_1,flight_time_1,price_1);
            count++;
    }

    fclose(Flight_Schedule);
    printf("\n\n\n  \n\nPress any key to back to the home page...");
    getch();
    system("CLS");
    Main_Menu();
}

void Remove_Flight()
{
    system("COLOR 0A");
    FILE *Temporary_1;
    Temporary_1 = fopen("Temporary_1.txt","a+");
    if(Temporary_1 == NULL){
        printf("Error Opening Temporary_1 File\n");
        return;
    }

    Flight_Schedule = fopen("Flight_Schedule.txt","a+");
    if(Flight_Schedule == NULL){
        printf("Error Opening Flight Schedule File\n");
        return;
    }

    char destination_from[destination_length];
    char destination_to[destination_length];

    char destination_from_1[destination_length];
    char destination_to_1[destination_length];
    char flight_time_1[6];
    char price_1[12];

    char line[destination_length+destination_length+6+12+4];

    int count = 0,found = 1;

    printf("\n\n\n\t\t\t\t       ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    Enter The Flight Details You Want to Remove    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");

    printf("\n\t\t\t# From: ");
    scanf("%s",&destination_from);

    printf("\n\t\t\t# To: ");
    scanf("%s",&destination_to);

    while(fgets(line,sizeof(line),Flight_Schedule) != NULL){
        sscanf(line,"%s %s %s %s",destination_from_1,destination_to_1,flight_time_1,price_1);
        count++;
        if((strcmp(destination_from,destination_from_1)==0)&&(strcmp(destination_to,destination_to_1)==0)){
            found = 0;
            printf("\n\n\t\t\t#Flight %d Details: %s to %s at %s <<local time>>    (Everyday)\n\t\t\t# Price: %s\n",count,destination_from_1,destination_to_1,flight_time_1,price_1);
            continue;
        }
        fprintf(Temporary_1,"%s %s %s %s\n",destination_from_1,destination_to_1,flight_time_1,price_1);
    }

    fclose(Temporary_1);
    fclose(Flight_Schedule);

    if(found){
        if(remove("Temporary_1.txt") != 0){
            printf("Error Deleting Temporary_1 File\n");
            return;
        }
        printf("\n\n\n\t\t\t\t\t\t\t\t\t  !!! No Flight Found !!!\n");
        printf("\n\n\n  \n\nPress any key to back to the home page...");
        getch();
        system("CLS");
        Main_Menu();
    }

    else{
        printf("\n\n\t\t\tDo You Want to Remove This Flight?\n\n");
        printf("\t\t\t1. Yes");
        printf("\n\n\t\t\t2. No\n\n");

        printf("\t\t\t#Enter Your Choice: ");
        int choice1,check = 0;
        scanf("%d",&choice1);

        if(choice1 == 1){
            check = 1;
            if(remove("Flight_Schedule.txt") != 0){
                check = 0;
                printf("Error Deleting Flight Scheduling File\n");
                return;
            }

            if(rename("Temporary_1.txt","Flight_Schedule.txt") != 0){
                check = 0;
                printf("Error Renaming Temporary File\n");
                return;
            }
        }

        else{
            if(remove("Temporary_1.txt") != 0){
                printf("Error Deleting Temporary_1 File\n");
                return;
            }
        }

        if(check){
            printf("\n\n\n\t\t\t\t\t\t\t\t    *** Flight Removed Successfully ***\n");
        }
        else{
            printf("\n\n\n\t\t\t\t\t\t\t\t     !!! Flight is Not Removed !!!\n");
        }
        printf("\n\n\n  \n\nPress any key to back to the home page...");
        getch();
        system("CLS");
        Main_Menu();
    }
}

void Booking_Policy()
{
    system("COLOR 0A");
    printf("\n\n\n\t\t\t\t       ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    Booking Policy For Flight Ticket Booking    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");

    printf("\n\n\n\t\t\t1. Payment Method: We accept credit card, debit card & cash only.");
    printf("\n\n\n\t\t\t2. Cancellation Policy: Cancellations are allowed up to 48 hours before the departure time for a full refund.");
    printf("\n\n\n\t\t\t3. Seat Selection: Seat selection is available during the booking process and is subject to availability.");
    printf("\n\n\n\t\t\t4. Child and Infant Policy: Please contact customer service for assistance with bookings involving children or infants.");
    printf("\n\n\n\t\t\t5. Special Assistance: If you require special assistance, please inform us at the time of booking.");
    printf("\n\n\n\t\t\t6. Travel Documents: Ensure you have valid identification and travel documents before boarding.");
    printf("\n\n\n\t\t\t7. Baggage Allowance: Baggage allowance may vary depending on the fare type. Please check your booking details for information.");

    printf("\n\n\n  \n\nPress any key to back to the home page...");
    getch();
    system("CLS");
    Main_Menu();
}

void Main_Menu()
{
    system("COLOR 5F");
    int choice1,choice2;


    printf("\n\n\n\t\t\t\t\t\t    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("   Welcome To Home Page   ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n\n\n");
    printf("\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t   1.Book Ticket\n\n");
    printf("\t\t\t\t\t\t\t\t\t   2.View Booking\n\n");
    printf("\t\t\t\t\t\t\t\t\t   3.Cancel Ticket\n\n");
    printf("\t\t\t\t\t\t\t\t\t   4.Add Flight Schedule\n\n");
    printf("\t\t\t\t\t\t\t\t\t   5.View Flight Schedules\n\n");
    printf("\t\t\t\t\t\t\t\t\t   6.Remove Flight Schedule\n\n");
    printf("\t\t\t\t\t\t\t\t\t   7.Change Password\n\n");
    printf("\t\t\t\t\t\t\t\t\t   8.Booking Policy\n\n");
    printf("\t\t\t\t\t\t\t\t\t   9.Logout\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t   #Enter Your Choice: ");

    scanf("%d",&choice1);

    if(choice1 == 1){
        system("CLS");
        Book_Ticket();
    }
    else if(choice1 == 2){
        system("CLS");

        printf("\n\n\n\t\t\t\t\t\t     ");
        for(int i=0;i<20;i++)
        {
            printf("\xB1");
        }
        printf("    Booking History    ");
        for(int i=0;i<20;i++)
        {
            printf("\xB1");
        }
        printf("\n\n\n");

        printf("\n\n\n\t\t\t1. Agent Booking History");
        printf("\n\n\t\t\t2. Search Booking");
        printf("\n\n\t\t\t3. View All Bookings");
        printf("\n\n\n\t\t\t#Enter Your Choice: ");
        scanf("%d",&choice2);

        if(choice2 == 1){
            system("CLS");
            Sold_By_Agent();
        }
        else if(choice2 == 2){
            system("CLS");
            Search_Booking();
        }
        else if(choice2 == 3){
            system("CLS");
            All_Bookings();
        }
        else{
            system("CLS");
            printf("\n\n\t\t\t\t\t\t\t\t    *** Please Choose a Valid Option ***\n");
            getch();
            system("CLS");
            Main_Menu();
        }

    }
    else if(choice1 == 3){
        system("CLS");
        Cancel_Ticket();
    }
    else if(choice1 == 4){
        system("CLS");
        Add_Flight();
    }
    else if(choice1 == 5){
        system("CLS");
        View_Flight_Schedule();
    }
    else if(choice1 == 6){
        system("CLS");
        Remove_Flight();
    }
    else if(choice1 == 7){
        system("CLS");
        Change_Password();
    }
    else if(choice1 == 8){
        system("CLS");
        Booking_Policy();
    }
    else if(choice1 == 9){
        system("CLS");
        Registration_Page();
    }
    else{
        system("CLS");
        printf("\n\n\t\t\t\t\t\t\t\t    *** Please Choose a Valid Option ***\n");
        getch();
        system("CLS");
        Main_Menu();
    }
}

void Registration_Page()
{
    system("COLOR 1F");
    printf("\n\n\n\t\t\t\t\t     ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    User Registration & Login Page    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");
    int choice;
    //printf("\n\n\n\n\n");
    printf(" ");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t  1.Registration\n\n");
    printf("\t\t\t\t\t\t\t\t\t  2.Login\n\n");
    printf("\t\t\t\t\t\t\t\t\t  3.Exit\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t\t  #Enter Your Choice: ");
    scanf("%d",&choice);
    system("CLS");

    switch(choice)
    {
        case 1:
            {
                Registration();
                system("CLS");
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t         1. Login\n\n");
                printf("\t\t\t\t\t\t\t\t\t         2. Exit\n\n");
                printf("\n\n\n\n\t\t\t\t\t\t\t\t\t    #Enter Your Choice: ");
                int choice1;
                scanf("%d",&choice1);
                if(choice1==1){
                    Login();
                }
                else if(choice1==2){
                    exit(1);
                }
                else{
                    printf("Please Enter a Valid Option\n");
                }
                break;
            }
        case 2:
            {
                Login();
                break;
            }
        case 3:
            {
                exit(1);
                break;
            }
        default:
            {
                printf("Please Enter a Valid Option");
            }
    }
}

void Login_Page()
{
    system("CLS");
    system("COLOR 1F");
    printf("\n\n\n\t\t\t\t\t\t     ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    User Login Page    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t         1. Login\n\n");
    printf("\t\t\t\t\t\t\t\t\t         2. Exit\n\n");
    printf("\n\n\n\n\t\t\t\t\t\t\t\t\t    #Enter Your Choice: ");
    int choice1;
    scanf("%d",&choice1);
    if(choice1==1){
        Login();
    }
    else if(choice1==2){
        exit(1);
    }
    else{
        printf("\n\n\n\t\t\t\t\t\t\t\t!!! Please Enter a Valid Option !!!");
        printf("\n\n\n\nPress any key to try again...");
        getch();
        //system("CLS");
        Login_Page();
    }
}

void Logo()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t\t                                                                .____   __ _\n");
    printf("\t\t\t\t\t\t   __o__   _______ _ _  _                                     /     /\n");
    printf("\t\t\t\t\t\t   \\    ~\\                                                  /      /\n");
    printf("\t\t\t\t\t\t     \\     '\\                                         ..../      .'\n");
    printf("\t\t\t\t\t\t      . ' ' . ~\\                                      ' /       /\n");
    printf("\t\t\t\t\t\t     .  _    .  ~ \\  .+~\\~ ~ ' ' \" \" ' ' ~ - - - - - -''_      /\n");
    printf("\t\t\t\t\t\t    .  <#  .  - - -/' . ' \\  __                          '~ - \\\n");
    printf("\t\t\t\t\t\t    .. -           ~-.._ / |__|  ( )  ( )  ( )  0  o    _ _    ~ .\n");
    printf("\t\t\t\t\t\t   .-'     777                                       .- ~    '-.    -.\n");
    printf("\t\t\t\t\t\t  <                      . ~ ' ' .             . - ~             ~ -.__~_. _ _\n");
    printf("\t\t\t\t\t\t    ~- .     SkySonic  .          . . . . ,- ~\n");
    printf("\t\t\t\t\t\t          ' ~ - - - - =.   <#>    .         \\.._\n");
    printf("\t\t\t\t\t\t                      .     ~      ____ _ .. ..  .- .\n");
    printf("\t\t\t\t\t\t                       .         '        ~ -.        ~ -.\n");
    printf("\t\t\t\t\t\t                         ' . . '               ~ - .       ~-.\n");
    printf("\t\t\t\t\t\t                                                     ~ - .      ~ .\n");
    printf("\t\t\t\t\t\t                                                            ~ -...0..~. ________ _ _\n");
}

void Loading()
{
    printf("\n\n\n\n\n\n");
    char ch[11] = "Loading...";
    for(int i=0;i<11;i++){
        printf("%c",ch[i]);
        Sleep(60);
        printf(" ");
    }
    Sleep(100);
}

int MaximizeOutputWindow(void)
{

    HWND ConsoleWindow;

    ConsoleWindow = GetConsoleWindow();

    ShowWindow(ConsoleWindow, SW_MAXIMIZE);

    return 0;

}

int main()
{
    system("COLOR 0A");
    MaximizeOutputWindow();

    printf("\n\n\n\n\t\t\t       ");

    for(int i=0;i<20;i++)
    {
        printf("\xB1");
        Sleep(10);
    }

    char ch[36] = "    Welcome To SkySonic Airline  ";
    for(int i=0;i<36;i++){
        printf("%c",ch[i]);
        Sleep(50);
        printf(" ");
    }

    for(int i=0;i<20;i++)
    {
        printf("\xB1");
        Sleep(10);
    }

    Logo();
    printf("\n\n\n\n\n\nPress any kew to continue...");
    getch();
    system("CLS");

    system("COLOR 1F");
    int choice;
    printf("\n\n\n\t\t\t\t\t     ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("    User Registration & Login Page    ");
    for(int i=0;i<20;i++)
    {
        printf("\xB1");
    }
    printf("\n\n\n");
    printf(" ");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t        1.Registration\n\n");
    printf("\t\t\t\t\t\t\t\t        2.Login\n\n");
    printf("\t\t\t\t\t\t\t\t        3.Exit\n\n\n\n");
    printf("\t\t\t\t\t\t\t\t        #Enter Your Choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            {
                Registration();
                system("CLS");
                printf("\n\n\n\t\t\t\t\t\t     ");
                for(int i=0;i<20;i++)
                {
                    printf("\xB1");
                }
                printf("    User Login Page    ");
                for(int i=0;i<20;i++)
                {
                    printf("\xB1");
                }
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t         1. Login\n\n");
                printf("\t\t\t\t\t\t\t\t\t         2. Exit\n\n");
                printf("\n\n\n\n\t\t\t\t\t\t\t\t\t    #Enter Your Choice: ");
                int choice1;
                scanf("%d",&choice1);
                if(choice1==1){
                    Login();
                }
                else if(choice1==2){
                    exit(1);
                }
                else{
                    printf("\n\n\n\t\t\t\t\t\t\t\t!!! Please Enter a Valid Option !!!");
                    printf("\n\n\n\nPress any key to try again...");
                    getch();
                    //system("CLS");
                    Login_Page();
                }
                break;
            }
        case 2:
            {
                Login();
                break;
            }
        case 3:
            {
                exit(1);
                break;
            }
        default:
            {
                printf("\n\n\n\t\t\t\t\t\t\t\t!!! Please Enter a Valid Option !!!");
                printf("\n\n\n\nPress any key to try again...");
                getch();
                system("CLS");
                Registration_Page();

            }
    }

    return 0;

}
