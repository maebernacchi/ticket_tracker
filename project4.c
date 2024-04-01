#include <stdio.h>
#include <MyroC.h>
#include <string.h>
#include <ctype.h>
/*
Preconditions: MyroC.h is included and usercheck exists

Postconditions: Moves the robot forward for one second at speed one
 */
void robot_forward(void);
/*
Preconditions: MyroC.h is included and usercheck exists

Postconditions: Moves the robot backward for one second at speed one
 */
void robot_backward(void);
/*
Preconditions: MyroC.h is included and usercheck exists

Postconditions: Makes the robot spin left for one second at speed one
 */
void robot_leftturn(void);
/*
Preconditions: MyroC.h is included and usercheck exists

Postconditions: Makes the robot spin right for one second at speed one
 */
void robot_rightturn(void);
/*
Preconditions: MyroC.h is included and user input is given for time and pitch

Postconditions: Moves the robot left and beeps at given time and pitch
 */
void robot_leftside_beep(double time, double pitch);
/*
Preconditions: MyroC.h is included and user input is given for time and pitch

Postconditions: Moves the robot right and beeps at given time and pitch
 */
void robot_rightside_beep(double time, double pitch);
/*
Preconditions: MyroC.h is included and user input is given for number of dance 
               repetitions
Postconditions: The robot performs a small dance a given number of times
 */
void dance(double reps);
/*
Preconditions: MyroC.h is included and user input is given for number of spins

Postconditions: The robot spins from side to side a given number of times
 */
void spin(double reps);
/*
Preconditions: MyroC.h is included and user input is given for the time and 
               pitch
Postconditions: The robot beeps at the given pitch for the given amount of time
 */
void beep(double time, double pitch);
/*
Preconditions: Menu is called within main

Postconditions: The menu is printed to the terminal
 */
void menu(void);
/*
Preconditions: Is called upon to check user input

Postconditions: Takes user input and returns a double based on the input
 */
double check_input(void);
/*
Preconditions: Is called upon to check user-inputted time

Postconditions: Will return the time as given by the user as a double 
 */
double get_time(void);
/*
Preconditions: Is called upon to check user-inputted pitch

Postconditions: Will return the pitch as given by the user as a double
 */
double get_pitch(void);
/*
Preconditions: Is called upon to check user-inputted repetition amount

Postconditions: Will return the repetition amount as given by the user as a 
                double
 */
double get_reps(void);
/*
Preconditions: Takes a user input and an array of strings that has space for 
               10 strings

Postconditions: Checks to ensure that command given by user is valid and if 
                it is will return the position in the character array that 
                the command corresponds to
 */
int to_lower(char * input, char * commands[10]);
/*
Preconditions: Takes in an int in the form of a pointer, the address being 
               located in main

Postconditions: Returns an int that will be added to the overall int that is 
                action_count
 */
int user_check(int * action_count);

int main(void)
{
  rConnect("/dev/rfcomm0"); //connects to Scribbler
  int action_count = 0; //initializes counter for actions made
  int runs = 1; //Allows the do-while loop to run at least once
  menu(); //prints the menu
  do{
      runs = user_check(&action_count);
      if(runs == 1)
        printf("What do you want the robot to do next?\n");
  }while(runs);
  printf("The robot completed %d actions.\n", action_count);// prints the amount
                                              //of actions made by Scribbler
  rDisconnect(); //Disconnects from Scribbler
  return 0;//Ends program
}//main

void menu ()
{
  printf("Welcome to the commands program.\n"
         "Please choose an action for the robot to carry out.\n"
         "1. forward\n"
         "2. backward\n"
         "3. left \n"
         "4. right\n"
         "5. leftside\n"
         "6. rightside\n"
         "7. dance\n"
         "8. spin\n"
         "9. beep\n"
         "10. quit\n"
         );
}//menu
void robot_forward(void)
{
  printf("Moving forward\n");
  rForward(1,-1);
}//robot_forward

void robot_backward(void)
{
  printf("Moving backward\n");
  rBackward(1,1);
}//robot_backward
 
void robot_leftturn(void)
{
  printf("Rotating left\n");
  rTurnLeft(1,.7);
}//robot_leftturn

void robot_rightturn(void)
{
  printf("Rotating right\n");
  rTurnRight(1,.7);
}//robot_rightturn

void robot_leftside_beep(double time, double pitch)
{
  printf("Turning left and beeping!\n");
  robot_leftturn();
  robot_forward();
  rBeep(time, pitch);
}//robot_leftside_beep

void robot_rightside_beep(double time, double pitch)
{
  printf("Turning right and beeping\n");
  robot_rightturn();
  robot_forward();
  rBeep(time, pitch);
}//robot_rightside_beep

 
void dance(double reps)
{
  for (int times = 0; times < reps; times++)
    {
      spin(times);
      robot_forward();
      robot_backward();
    }
}//dance

void spin(double reps)
{
  for(int times = 0; times < reps; times++)
    {
      robot_rightturn();
      robot_leftturn();
    }
}//spin

void beep(double time, double pitch)
{
  rBeep(time, pitch);
}//beep

double check_input(void)
{
  double input;
  int scan_num;
  char enter;
  do{
    scan_num = scanf("%lf%c", &input, &enter);
    if (enter != '\n'){
      printf("return just a double");
      while(getchar() != '\n');
    }
  }while((scan_num == 0) || enter != '\n');
  return input;
}
double get_time(void)
{
   printf("Enter the duration you would like this action to last.\n");
  double time;
  time = check_input();
  return time;
 
}//getTime

double get_pitch(void)
{
printf("Enter the pitch you would like the robot to beep.\n");
  double pitch;
  pitch = check_input();
  return pitch;
}//getPitch

double get_reps(void)
{
  printf("Enter how many repetitions you would like the robot to perform.\n");
  double reps;
  reps = check_input();
  return reps;  
}//get_reps

int to_lower(char input[], char * commands[10])
{
  for(int letter = 0; letter < strlen(input); letter++)
    {
      input[letter] = tolower(input[letter]);
      if(isalpha(input[letter]) == 0)
        {
          printf("%c is not a valid input character. Please try again.\n",
                 input[letter]);
          return 0;
        }//if
    }//for
  int position;
  for(position = 0; position < 10; position++)
    {
      int correct_command = strcmp(input, commands[position]);
      if (correct_command == 0)
        return position;
    }//for
 
  if(position == 10)
    {
      printf("%s is not a usable command. Please try again!\n", input);
      return 10;
    }
  return position;
}//to_lower


int user_check(int * action_count)
{

  char * possible_inputs[10] = {"forward","backward","left","right","leftside",
                                "rightside", "dance", "spin", "beep", "quit"};
  char input[50];
  scanf("%s", input);
  int action = to_lower(input, possible_inputs);
  switch(action) {
  case 0:
    robot_forward();
    *action_count+= 1;
    break;
  case 1:
    robot_backward();
    *action_count+= 1;
    break;
  case 2:
    robot_leftturn();
    *action_count+= 1;
    break;
  case 3:
    robot_rightturn();
    *action_count+= 1;
    break;
  case 4:
    printf("");
    double fourtime = get_time();
    double fourpitch = get_pitch();
    robot_leftside_beep(fourtime, fourpitch);
    *action_count+= 1;
    break;
  case 5:
     printf("");
    double fivetime = get_time();
    double fivepitch = get_pitch();
    robot_rightside_beep(fivetime, fivepitch);
    *action_count+= 1;
    break;
  case 6:
    printf("");
    double sixreps = get_reps();
    dance(sixreps);
    *action_count+= 1;
    break;
  case 7:
    printf("");
    double sevenreps = get_reps();
    spin(sevenreps);
    *action_count+= 1;
    break;
  case 8:
    printf("");
    double eighttime= get_time();
    double eightpitch = get_pitch();
    beep(eighttime, eightpitch);
    *action_count+= 1;
    break;
  case 9:
    return 0;
  }
  return 1;
}//user_check
