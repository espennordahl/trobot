#ifndef BRAIN_H
#define BRAIN_H

class Brain{
  public:
    Brain(TrKjMotor *motorL, TrKjMotor *motorR){
      Serial.println("Initializing brain");
      m_numActions = 4;
      actionPool[0] = new ActionForward(motorL, motorR);
      actionPool[1] = new ActionBackward(motorL, motorR);
      actionPool[2] = new ActionRotateLeft(motorL, motorR);
      actionPool[3] = new ActionRotateRight(motorL, motorR);
    }
    
    Action *pickAction(State *state){
      Serial.println("Updating PDFs");
      int pdfSum = 0;
      for(int i=0; i<m_numActions; ++i){
        actionPool[i]->updatePdf(state);
        pdfSum += actionPool[i]->pdf();
      }

      int randnum = random(pdfSum);
      Serial.println("randum num: ");
      Serial.println(randnum);

      int accumPdf = 0;
      Serial.println("Picking action.");
      for(int i=0; i<m_numActions; ++i){
        accumPdf += actionPool[i]->pdf();
        if (accumPdf >= randnum){
          return actionPool[i];
        }
      }
      Serial.println("Ooops, found no action.");
      return NULL;
    }
  private:  
    Action *actionPool[4];
    int m_numActions;
};

#endif
