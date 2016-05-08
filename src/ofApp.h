#pragma once

#include "ofMain.h"
#include "Leap.h"

#define DUAL_CAMERA
#define RAW_DATA

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    Leap::Controller controller;
    Leap::ImageList images;
    Leap::Image image;
    Leap::Frame frame;
    
    unsigned char * videoInverted;
    
#ifdef DUAL_CAMERA
    ofTexture videoTexture[2];
#else
    ofTexture videoTexture;
#endif
    
#ifdef RAW_DATA
    // 生データ
    const int IMAGE_WIDTH = 640;
    const int IMAGE_HEIGHT = 240;
#else
    // 歪み補正時
    const int IMAGE_WIDTH = 400;
    const int IMAGE_HEIGHT = 400;
#endif
    
    int totalPixels = IMAGE_WIDTH * IMAGE_HEIGHT;
    
    
    
};
