int count1 = 0;
int count2 = 0;

void task1(void * parameters){
  for(;;){
    Serial.print("Task 1 counter: ");
    Serial.println(count1);
    count1++;
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void task2(void * parameters){
  for(;;){
    Serial.print("Task 2 counter: ");
    Serial.println(count2);
    count2++;
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

public xTaskCreate(
    task1,  //Function name
    "*Task 1", //Task name
    1000, //Stack size
    NULL, //Task parameters
    1, //Task priority
    NULL  //Task handle
  );

public xTaskCreate(
    task2,    //Function name
    "*Task 2", //Task name
    1000,     //Stack size
    NULL,     //Task parameters
    1,        //Task priority
    NULL      //Task handle
);