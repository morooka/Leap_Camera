#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // 非アクティブでもLeapMtionの動作を続ける
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    
    // 画像の取得を有効にする
    controller.setPolicy(Leap::Controller::PolicyFlag::POLICY_IMAGES );
    videoInverted 	= new unsigned char [IMAGE_WIDTH * IMAGE_HEIGHT];
    
#ifdef DUAL_CAMERA
    videoTexture[0].allocate(IMAGE_WIDTH,IMAGE_HEIGHT, GL_LUMINANCE);
    videoTexture[1].allocate(IMAGE_WIDTH,IMAGE_HEIGHT, GL_LUMINANCE);
#else
    videoTexture.allocate(IMAGE_WIDTH,IMAGE_HEIGHT, GL_LUMINANCE);
#endif
    
    ofSetVerticalSync(true);
    
    ofSetWindowShape(IMAGE_WIDTH, IMAGE_HEIGHT * 2);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // 画像を取得する
    frame = controller.frame();
    images = frame.images();
    
#ifdef DUAL_CAMERA
    // カメラ画像を表示する
    for ( int i = 0; i < 2; i++ ){
        image = images[i];
        if ( !image.isValid() ){
            continue;
        }
        unsigned char* image_buffer = (unsigned char*)image.data();
        
        for (int h = 0; h < totalPixels; h++){
            videoInverted[h] = image_buffer[h];
        }
        videoTexture[i].loadData(videoInverted, IMAGE_WIDTH,IMAGE_HEIGHT, GL_LUMINANCE);
    }
#else
    image = images[0];
    if ( image.isValid() ){
        unsigned char* image_buffer = (unsigned char*)images[0].data();
        for (int h = 0; h < totalPixels; h++){
            videoInverted[h] = image_buffer[h];
        }
        videoTexture.loadData(videoInverted, IMAGE_WIDTH,IMAGE_HEIGHT, GL_LUMINANCE);
    }
#endif
    
    ofSetWindowTitle(ofToString(ofGetFrameRate(),2));
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetHexColor(0xffffff);
#ifdef DUAL_CAMERA
    for ( int i = 0; i < 2; i++ ){
        // 画像を表示
        videoTexture[i].draw(0, i*IMAGE_HEIGHT);
        
        //指の位置を表示する
        ofVec2f origin = ofVec2f(0,IMAGE_HEIGHT * i);
        const float camera_offset = 20; //x-axis offset of camera in millimeters
        Leap::FingerList allTheFingers = frame.fingers();
        for(Leap::FingerList::const_iterator fl = allTheFingers.begin();
            fl != allTheFingers.end(); fl++){
            Leap::Vector tip = (*fl).tipPosition();
            float h_slope = -(tip.x + camera_offset * (2 * i -1)) / tip.y;
            float v_slope = tip.z / tip.y;
            Leap::Vector pixel = image.warp( Leap::Vector( h_slope, v_slope, 0 ) );
            ofDrawCircle(pixel.x + origin.x, pixel.y + origin.y, 10);
        }
    }
#else
     videoTexture.draw(20,20);
#endif
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
  

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}