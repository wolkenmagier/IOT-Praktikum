// include queue library header.
#include <QueueArray.h>


struct COMMAND {
  uint32_t time;
  uint8_t cmd;
  uint8_t param;
};

// create a queue of characters.
QueueArray <COMMAND> queue;

void insertTask(uint32_t time, uint8_t cmd, uint8_t param){
//  if (first == true){
//    setAlarmFromSeconds(time);
//    first = false;
//  }
  Serial.print ("TASK INSERTED");
  COMMAND _command = { time , cmd , param };
  queue.enqueue (_command);
}

void printTasklist(){

//    Store the queue data in temp queue
    QueueArray <COMMAND> temp_queue;
    COMMAND _command;
    while (!queue.isEmpty ()){
      _command = queue.dequeue();
      temp_queue.enqueue (_command);
      Serial.print ("TASK---");
      Serial.print (_command.time);
      Serial.print (_command.cmd);
      Serial.print (_command.param);
    }

//    Store the data back in orignal queue
    while (!temp_queue.isEmpty ()){
      _command = temp_queue.dequeue();
      queue.enqueue (_command);
    }
        
}

void runAvailTasks(){
  uint32_t _time;
  _time = millis();
//  setAlarmFromSeconds(_time+30000);
  //Run all task with a timestamp before current time
//  Store the queue data in temp queue
    QueueArray <COMMAND> temp_queue;
    COMMAND _command;
    while (!queue.isEmpty ()){
      _command = queue.dequeue();
      if (_command.time < _time){
        runTaskOnce(_command.cmd,_command.param); 
      }
      else{
        temp_queue.enqueue (_command);
      }
    }

//    Store the command with timestamp less than current timestamp back in orignal queue
    while (!temp_queue.isEmpty ()){
      _command = temp_queue.dequeue();
      queue.enqueue (_command);
    }
}
