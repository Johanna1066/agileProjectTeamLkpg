#include <Arduino.h>
#include <iostream>
#include <vector>
#include "semphr.h"



// xSemaphoreTake(),, xSemaphoreGive()

int counter = 0;
SemaphoreHandle_t myHandle;
void myFunctionAdd(void *parameters);
void myFunctionPrint(void *parameters);


void setup()
{
    myHandle = xSemaphoreCreateMutex();

    Serial.begin(9600);
  xTaskCreate(
    myFunctionAdd,
    "*myFunctionAdd",
    2048,
    NULL,
    1,
    NULL
    );

     xTaskCreate(
    myFunctionPrint,
    "*myFunctionPrint",
    2048,
    NULL,
    1,
    NULL
    );
}

void myFunctionAdd(void *parameter){
   for (;;)
   {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE) {  // Use portMAX_DELAY to block indefinitely
            counter++;
            xSemaphoreGive(myHandle);
        }
    
    vTaskDelay(100);
   }
}

void myFunctionPrint(void *parameter){
    for (;;)
    {
        if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE) {
            Serial.println(counter);
            xSemaphoreGive(myHandle);
        }
        vTaskDelay(1000);
    }
}

void loop()
{

  
}
//END OF OUR CODE/
/* Basic Multi Threading Arduino Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

//_____________________________________________________________________________________________________________________________

/*GITHUB TEST CODE!
// Please read file README.md in the folder containing this example.
#include <Arduino.h>

#define USE_MUTEX
int shared_variable = 0;
SemaphoreHandle_t shared_var_mutex = NULL;

// Define a task function
void TaskAdd(void *pvParameters);
void TaskPrint(void *pvParameters);

// The setup function runs once when you press reset or power on the board.
void setup() {
  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.printf(" Task 0          | Task 1\n");

#ifdef USE_MUTEX
  shared_var_mutex = xSemaphoreCreateMutex();  // Create the mutex
#endif

  // Set up two tasks to run the same function independently.
  static int task_number0 = 0;
  xTaskCreate(
    TaskAdd, "Task 0"  // A name just for humans
    ,
    2048  // The stack size
    ,
    (void *)&task_number0  // Pass reference to a variable describing the task number
    //,  5  // High priority
    ,
    1  // priority
    ,
    NULL  // Task handle is not used here - simply pass NULL
  );

  static int task_number1 = 1;
  xTaskCreate(
    TaskPrint, "Task 1", 2048  // Stack size
    ,
    (void *)&task_number1  // Pass reference to a variable describing the task number
    ,
    1  // Low priority
    ,
    NULL  // Task handle is not used here - simply pass NULL
  );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop() {}

//--------------------------------------------------/
//---------------------- Tasks ---------------------/
//--------------------------------------------------/

void TaskAdd(void *pvParameters) {  // This is a task.
  int task_num = *((int *)pvParameters);
  Serial.printf("%s\n", task_num ? " Starting        |" : "                 | Starting");
  for (;;) {  // A Task shall never return or exit.
#ifdef USE_MUTEX
    if (shared_var_mutex != NULL) {  // Sanity check if the mutex exists
      // Try to take the mutex and wait indefinitely if needed
      if (xSemaphoreTake(shared_var_mutex, portMAX_DELAY) == pdTRUE) {
        // Mutex successfully taken
#endif
        int new_value = random(1000);

        char str0[32];
        sprintf(str0, " %d <- %d      |", shared_variable, new_value);
        char str1[32];
        sprintf(str1, "                 | %d <- %d", shared_variable, new_value);
        Serial.printf("%s\n", task_num ? str0 : str1);

        shared_variable = new_value;
        delay(random(100));  // wait random time of max 100 ms - simulating some computation

        sprintf(str0, " R: %d          |", shared_variable);
        sprintf(str1, "                 | R: %d", shared_variable);
        Serial.printf("%s\n", task_num ? str0 : str1);
        //Serial.printf("Task %d after write: reading %d\n", task_num, shared_variable);

        if (shared_variable != new_value) {
          Serial.printf("%s\n", task_num ? " Mismatch!       |" : "                 | Mismatch!");
          //Serial.printf("Task %d: detected race condition - the value changed!\n", task_num);
        }

#ifdef USE_MUTEX
        xSemaphoreGive(shared_var_mutex);  // After accessing the shared resource give the mutex and allow other processes to access it
      } else {
        // We could not obtain the semaphore and can therefore not access the shared resource safely.
      }  // mutex take
    }  // sanity check
#endif
    delay(10);  // Allow other task to be scheduled
  }  // Infinite loop
}
void TaskPrint(void *pvParameters) {  // This is a task.
  int task_num = *((int *)pvParameters);
  Serial.printf("%s\n", task_num ? " Starting        |" : "                 | Starting");
  for (;;) {  // A Task shall never return or exit.
#ifdef USE_MUTEX
    if (shared_var_mutex != NULL) {  // Sanity check if the mutex exists
      // Try to take the mutex and wait indefinitely if needed
      if (xSemaphoreTake(shared_var_mutex, portMAX_DELAY) == pdTRUE) {
        // Mutex successfully taken
#endif
        int new_value = random(1000);

        char str0[32];
        sprintf(str0, " %d <- %d      |", shared_variable, new_value);
        char str1[32];
        sprintf(str1, "                 | %d <- %d", shared_variable, new_value);
        Serial.printf("%s\n", task_num ? str0 : str1);

        shared_variable = new_value;
        delay(random(100));  // wait random time of max 100 ms - simulating some computation

        sprintf(str0, " R: %d          |", shared_variable);
        sprintf(str1, "                 | R: %d", shared_variable);
        Serial.printf("%s\n", task_num ? str0 : str1);
        //Serial.printf("Task %d after write: reading %d\n", task_num, shared_variable);

        if (shared_variable != new_value) {
          Serial.printf("%s\n", task_num ? " Mismatch!       |" : "                 | Mismatch!");
          //Serial.printf("Task %d: detected race condition - the value changed!\n", task_num);
        }

#ifdef USE_MUTEX
        xSemaphoreGive(shared_var_mutex);  // After accessing the shared resource give the mutex and allow other processes to access it
      } else {
        // We could not obtain the semaphore and can therefore not access the shared resource safely.
      }  // mutex take
    }  // sanity check
#endif
    delay(10);  // Allow other task to be scheduled
  }  // Infinite loop
}
*/
