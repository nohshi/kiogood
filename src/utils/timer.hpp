
#ifndef timer_hpp
#define timer_hpp

#include "ofMain.h"

//一定間隔の時間で関数をキックしてくれるイベントオブジェクト
class Timer {
public:
    
    ofEvent<int> tick;
    
    float time = 0;
    float interval = 1;
    
    Timer(const float &_interval = 1) {
        interval = _interval;
    }
    
    void update() {
        time += ofGetLastFrameTime();
        if (time > interval) {
            int taskNum = time/interval; //intevalがtimeの中に何個入ってるか
            for (int i=0; i<taskNum; i++) {
                ofNotifyEvent(tick, i, this);
            }
            time -= interval * taskNum;
        }
    }
    
};

#endif /* timer_hpp */
