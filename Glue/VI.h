//
// Created by Rolf Svenning on 17/04/2023.
//

#ifndef IMPLEMENTATIONS_VI_H
#define IMPLEMENTATIONS_VI_H


class VI { // NOTE_FOR_SELF: members inside class are inline by default so not an issue with multiple includes
public:
  int v;
  int ind;

  VI(int value = -1, int index = -1){
    v = value;
    ind = index;
  }

  bool operator==(const VI other) const {
      return v == other.v and ind == other.ind;
  }
};


#endif //IMPLEMENTATIONS_VI_H
