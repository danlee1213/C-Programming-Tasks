#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "dayconf.h"

/*
*
* Your code should start from here
* You can add any helper functions as you like
* You can also modify the parameter of the function as you like
*
*/
/*26/12/2004
31/3/2002
*/

day_info save_info[30];

//Give a number to a stored data
int index_of_stored_data(){
  int latest_index = 0;
  while(save_info[latest_index].date != '\0'){
    ++latest_index;
  }
  return latest_index;
}

//Task 3
void save_data(day_info daymodifier){
  const int latest_index = index_of_stored_data();
  //printf("latest_index:%d\n",latest_index); //For Debugging
  save_info[latest_index] = daymodifier;
}

//Gregorian date function
int gregorian_date(int d, int m, int y){
  static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
  y -= m < 3;
  return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

int check_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//Check the Leap Year
bool LeapYear_check(const int year){
  if((year % 400 == 0) || ((year % 4 == 0) && (year % 100 !=0))){
    return true;
  }
  return false;
}

  //Task2
void date_input() {
  const int latest_index = index_of_stored_data();
    int input_day;
    int input_month;
    int input_year;
    MONTHS month;
    day_info daymodifier;

    while(1){
      //Intro message
      printf("Please input a date (DD/MM/YYYY): ");
      //User Input
      scanf("%d/%d/%d",&input_day,&input_month,&input_year);

      //Input year decision
      if(input_year < 1800 || input_year >9999){
        invalid_input_msg();
        return date_input();
      } else {
        daymodifier.year = input_year;
      }

      //Input month decision
      if(input_month <= 0 || input_month > 12){
        invalid_input_msg();
        return date_input();
      }

      switch(input_month){
        case 1: daymodifier.month = JANUARY;
        break;
        case 2: daymodifier.month = FEBRUARY;
        break;
        case 3: daymodifier.month = MARCH;
        break;
        case 4: daymodifier.month = APRIL;
        break;
        case 5: daymodifier.month = MAY;
        break;
        case 6: daymodifier.month = JUNE;
        break;
        case 7: daymodifier.month = JULY;
        break;
        case 8: daymodifier.month = AUGUST;
        break;
        case 9: daymodifier.month = SEPTEMBER;
        break;
        case 10: daymodifier.month = OCTOBER;
        break;
        case 11: daymodifier.month = NOVEMBER;
        break;
        case 12: daymodifier.month = DECEMBER;
        }

      //In Leap Year February ends 29th
       if(LeapYear_check(daymodifier.year) == true){
        check_month[1] = 29;
      } else{
          check_month[1] = 28;
        }

       //Input day decision
       for(int i=1; i<=12; ++i){
        if(daymodifier.month == i){
          if((input_day <= 0 || input_day > 31) || (input_day > check_month[i-1])){
            invalid_input_msg();
            return date_input();
          } else {
            daymodifier.date = input_day;
          }
        }
      }

      //gregorian calendar algorithm (Day determination)
      daymodifier.day = gregorian_date(daymodifier.date, daymodifier.month, daymodifier.year);

      if(daymodifier.day == SUNDAY){
        strcpy(daymodifier.daystore ,"Sunday");
      }
      else if(daymodifier.day == MONDAY){
        strcpy(daymodifier.daystore ,"Monday");
      }
      else if(daymodifier.day == TUESDAY){
        strcpy(daymodifier.daystore ,"Tuesday");
      }
      else if(daymodifier.day == WEDNESDAY){
        strcpy(daymodifier.daystore ,"Wednesday");
      }
      else if(daymodifier.day == THURSDAY){
        strcpy(daymodifier.daystore ,"Thursday");
      }
      else if(daymodifier.day == FRIDAY){
        strcpy(daymodifier.daystore ,"Friday");
      }
      else if(daymodifier.day == SATURDAY){
        strcpy(daymodifier.daystore ,"Saturday");
      }

      //Special day decision
      while(daymodifier.day == 0){

        if(daymodifier.date == 1 && daymodifier.month == 1){
        strcpy(daymodifier.name_of_holiday, "First Day of January, Sunday");
      }
        else if(daymodifier.date == 29 && daymodifier.month == 1){
          strcpy(daymodifier.name_of_holiday, "Birthday of the Great Tim Woo, Sunday");
        }
        else if(daymodifier.date == 10 && daymodifier.month == 3){
          strcpy(daymodifier.name_of_holiday, "Mario Day, Sunday");
        }
        else if(daymodifier.date == 31 && daymodifier.month == 3){
          strcpy(daymodifier.name_of_holiday, "World Backup Day, Sunday");
        }
        else if(daymodifier.date == 10 && daymodifier.month == 4){
          strcpy(daymodifier.name_of_holiday, "Whatever Day, Sunday");
        }
        else if(daymodifier.date == 13 && daymodifier.month == 4){
          strcpy(daymodifier.name_of_holiday, "Easter, Sunday");
        }
        else if(daymodifier.date == 11 && daymodifier.month == 5){
          strcpy(daymodifier.name_of_holiday, "National Technology Day, Sunday");
        }
        else if(daymodifier.date == 6 && daymodifier.month == 6){
          strcpy(daymodifier.name_of_holiday, "D-Day, Sunday");
        }
        else if(daymodifier.date == 25 && daymodifier.month == 12){
          strcpy(daymodifier.name_of_holiday, "Christmas, Sunday");
        }
        else if(daymodifier.date == 26 && daymodifier.month == 12){
          strcpy(daymodifier.name_of_holiday, "Boxing Day, Sunday");
        }
        else if(daymodifier.day == 0){
          strcpy(daymodifier.name_of_holiday, "Sunday");
        }
        else{
          strcpy(daymodifier.name_of_holiday, "Not a holiday, Sunday");
        }
        printf("Day: %s\n",daymodifier.daystore);
        printf("Name of holiday: %s\n",daymodifier.name_of_holiday);
        printf("\n");
        save_data(daymodifier);
        break;
      }

      while(daymodifier.day != 0){

      if(daymodifier.date == 1 && daymodifier.month == 1){
        strcpy(daymodifier.name_of_holiday, "First Day of January");
      }
        else if(daymodifier.date == 29 && daymodifier.month == 1){
          strcpy(daymodifier.name_of_holiday, "Birthday of the Great Tim Woo");
        }
        else if(daymodifier.date == 10 && daymodifier.month == 3){
          strcpy(daymodifier.name_of_holiday, "Mario Day");
        }
        else if(daymodifier.date == 31 && daymodifier.month == 3){
          strcpy(daymodifier.name_of_holiday, "World Backup Day");
        }
        else if(daymodifier.date == 10 && daymodifier.month == 4){
          strcpy(daymodifier.name_of_holiday, "Whatever Day");
        }
        else if(daymodifier.date == 13 && daymodifier.month == 4){
          strcpy(daymodifier.name_of_holiday, "Easter");
        }
        else if(daymodifier.date == 11 && daymodifier.month == 5){
          strcpy(daymodifier.name_of_holiday, "National Technology Day");
        }
        else if(daymodifier.date == 6 && daymodifier.month == 6){
          strcpy(daymodifier.name_of_holiday, "D-Day");
        }
        else if(daymodifier.date == 25 && daymodifier.month == 12){
          strcpy(daymodifier.name_of_holiday, "Christmas");
        }
        else if(daymodifier.date == 26 && daymodifier.month == 12){
          strcpy(daymodifier.name_of_holiday, "Boxing Day");
        }
        /*
        else if(daymodifier.day == 0){
          strcpy(daymodifier.name_of_holiday, "Sunday");
        }*/
        else{
          strcpy(daymodifier.name_of_holiday, "Not a holiday");
        }
        // DEBUGGING
        // printf("%d/%d/%d\n",daymodifier.date,daymodifier.month,daymodifier.year);
        printf("Day: %s\n",daymodifier.daystore);
        printf("Name of holiday: %s\n",daymodifier.name_of_holiday);
        printf("\n");
        save_data(daymodifier);
        break;
      }
      break;
    }
  }

void display_saved_data(const int latest_index){
  printf("Here is the list of save data:\n");
  for(int i=0; i<latest_index; ++i){
    // DEBUGGING
    // printf("%d/%d/%d\n",save_info[i].date,save_info[i].month,save_info[i].year);
    char formatted_date[10];
    char formatted_month[10];

    // for clearing char array all values to NULL
    memset(&formatted_date, '\0', sizeof(formatted_date));
    memset(&formatted_month, '\0', sizeof(formatted_month));

    if(save_info[i].date > 0  && save_info[i].date < 10) {
      formatted_date[0] = '0';
	  formatted_date[1] = save_info[i].date + '0';
    formatted_date[2] = '\0';
    }

    if(save_info[i].month > 0  && save_info[i].month < 10) {
      formatted_month[0] = '0';
		  formatted_month[1] = save_info[i].month + '0';
      formatted_month[2] = '\0';
    }

    // if date and month are 0 ~ 9
    if(formatted_date[0] != '\0' && formatted_month[0] != '\0') {
      printf("%d. %s/%s/%d \n",i+1, formatted_date, formatted_month, save_info[i].year);
    }
    // if only date is 0 ~ 9
    else if(formatted_date[0] != '\0') {
      printf("%d. %s/%d/%d \n",i+1, formatted_date, save_info[i].month, save_info[i].year);
    }
    // if only month is 0 ~ 9
    else if(formatted_month[0] != '\0') {
      printf("%d. %d/%s/%d \n",i+1, save_info[i].date, formatted_month, save_info[i].year);
    }
    // all greater than 9
    else {
      printf("%d. %d/%d/%d \n",i+1, save_info[i].date, save_info[i].month, save_info[i].year);
    }
  }
}



//Task 4
void select_saved_data(const day_info daymodifier){
  const int latest_index = index_of_stored_data();
  int saved_data_no;
  //if there is a saved data
  if(latest_index !=0){
    display_saved_data(latest_index);
    printf("Please select the saved data from the list:\n");
    scanf("%d", &saved_data_no);

    while(saved_data_no > 0 && saved_data_no < 31){
      char formatted_date[10];
      // for clearing char array all values to NULL
      memset(&formatted_date, '\0', sizeof(formatted_date));

      if(save_info[saved_data_no-1].date > 0 && save_info[saved_data_no-1].date < 10) {

          	formatted_date[0] = '0';
            formatted_date[1] = save_info[saved_data_no-1].date + '0';
            formatted_date[2] = '\0';
            printf("Date: %s\n", formatted_date);
      }
      else {
            printf("Date: %d\n", save_info[saved_data_no-1].date);
      }

      //Display integer month to character
      switch(save_info[saved_data_no-1].month){
        case 1: printf("Month: January\n");
        break;
        case 2: printf("Month: February\n");
        break;
        case 3: printf("Month: March\n");
        break;
        case 4: printf("Month: August\n");
        break;
        case 5: printf("Month: May\n");
        break;
        case 6: printf("Month: June\n");
        break;
        case 7: printf("Month: July\n");
        break;
        case 8: printf("Month: August\n");
        break;
        case 9: printf("Month: September\n");
        break;
        case 10: printf("Month: October\n");
        break;
        case 11: printf("Month: November\n");
        break;
        case 12: printf("Month: December\n");
      }
      printf("Year: %d\n",save_info[saved_data_no-1].year);
      printf("Day: %s\n", save_info[saved_data_no-1].daystore);
      printf("Name of holiday: %s\n", save_info[saved_data_no-1].name_of_holiday);

      //Check whether input date is holiday or not
      if(save_info[saved_data_no-1].date == 1 && save_info[saved_data_no-1].month == 1){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].date == 29 && save_info[saved_data_no-1].month == 1){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].date == 10 && save_info[saved_data_no-1].month == 3){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].date == 31 && save_info[saved_data_no-1].month == 3){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].date == 10 && save_info[saved_data_no-1].month == 4){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].date == 13 && save_info[saved_data_no-1].month == 4){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].date == 11 && save_info[saved_data_no-1].month == 5){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].date == 6 && save_info[saved_data_no-1].month == 6){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].date == 25 && save_info[saved_data_no-1].month == 12){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].date == 26 && save_info[saved_data_no-1].month == 12){
        printf("It is a holiday! :)\n\n");
      } else if(save_info[saved_data_no-1].day == 0){
        printf("It is a holiday! :)\n\n");
      }
      else{
        printf("It is not a holiday... :(\n\n");
      }
      break;
    }
  } else{
    printf("There is no saved data, Try again!\n\n");
  }

}

//Bonus Task(Export)
void export_from_file(const day_info daymodifier){
  const int latest_index = index_of_stored_data();
  FILE *fp;
  fp = fopen("data_save.txt","w");
  if(fp == NULL){
    printf("Failed to open\n");
  } else{
    printf("Say Hello to your file!\n\n");
  }


  for(int i=0; i<latest_index; ++i){
    char formatted_date[10];
    char formatted_month[10];

    // for clearing char array all values to NULL
    memset(&formatted_date, '\0', sizeof(formatted_date));
    memset(&formatted_month, '\0', sizeof(formatted_month));

    if(save_info[i].date > 0  && save_info[i].date < 10) {
      formatted_date[0] = '0';
	  formatted_date[1] = save_info[i].date + '0';
    formatted_date[2] = '\0';
    }

    if(save_info[i].month > 0  && save_info[i].month < 10) {
      formatted_month[0] = '0';
		  formatted_month[1] = save_info[i].month + '0';
      formatted_month[2] = '\0';
    }

    // if date and month are 0 ~ 9
    if(formatted_date[0] != '\0' && formatted_month[0] != '\0') {
      fprintf(fp,"%d. %s/%s/%d \n",i+1, formatted_date, formatted_month, save_info[i].year);
    }
    // if only date is 0 ~ 9
    else if(formatted_date[0] != '\0') {
      fprintf(fp,"%d. %s/%d/%d \n",i+1, formatted_date, save_info[i].month, save_info[i].year);
    }
    // if only month is 0 ~ 9
    else if(formatted_month[0] != '\0') {
      fprintf(fp,"%d. %d/%s/%d \n",i+1, save_info[i].date, formatted_month, save_info[i].year);
    }
    // all greater than 9
    else {
      fprintf(fp,"%d. %d/%d/%d \n",i+1, save_info[i].date, save_info[i].month, save_info[i].year);
    }
  }
  fclose(fp);
}


//Bonus Task(Import)
void import_from_file(const day_info daymodifier){
  const int latest_index = index_of_stored_data();
  FILE *fp;
  fp = fopen("data_save.txt","a");
  if(fp == NULL){
    printf("No file to open");
  } else{
    printf("Open file success");
  }

}

//Task 1
void main_loop(){
  char input;
  day_info daymodifier;
  //Input validation
  while(1){
    choice_menu();
    scanf("%s", &input);

    if(input == DATE_INPUT){
      date_input();
    }
    else if(input == IMPORT_FROM_FILE){
      import_from_file(daymodifier);
    }
    else if(input == EXPORT_FROM_FILE){
      export_from_file(daymodifier);
    }
    else if(input == SELECT_SAVED_DATA){
      select_saved_data(daymodifier);
    }
    else if(input == END_PROGRAM){
     break;
    }
    else{
      invalid_input_msg();
    }
  }

}

/*
*
* Your code ends here
*
*/

int main(void) {
  opening();
  main_loop();
  return 0;
}
