
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetFrameRate(60);
    ofSetWindowTitle("openframeworks");

    ofBackground(255,246,0);
    ofSetColor(230,111,333);
    ofEnableDepthTest();
    
    mySound.load("space.wav");
            mySound.setLoop(true); //Sound will loop
            mySound.play();
}

//--------------------------------------------------------------
void ofApp::update() {

    ofSeedRandom(39);
    this->mesh.clear();

    int span = 10;  //adjust the number of facets
    int scale, index;
    for (int v = 0; v < 360; v += span) {   //Graphic display range, full display or display half

        for (int u = -170; u < 250; u += span) {  //Graph up and down display range


            auto noise_seed = (this->make_apple_point(u - span * 0.5, v - span * 0.5) + this->make_apple_point(u - span * 0.5, v + span * 0.5) + this->make_apple_point(u + span * 0.5, v + span * 0.5)) / 30;     //Graphic explosion range and scale time

            auto noise_value = ofNoise(glm::vec4(noise_seed * 0.25, ofGetFrameNum() * 0.008)); //The bigger it goes, the faster it goes

            scale = 300;   //The original value is 30. The larger the number is, the larger the volume will be

            if (noise_value > 0.65) { //Control whether to explode on a large scale, the larger the more not to explode

            
                scale = ofMap(noise_value, 0.65, 1, 30, 100);
            }
            index = this->mesh.getNumVertices();
            
            this->mesh.addVertex(this->make_apple_point(u - span * 0.5, v - span * 0.5) * scale);
            this->mesh.addVertex(this->make_apple_point(u - span * 0.5, v + span * 0.5) * scale);
            this->mesh.addVertex(this->make_apple_point(u + span * 0.5, v + span * 0.5) * scale);
                        
            this->mesh.addIndex(index); this->mesh.addIndex(index + 1);     //Section width

                this->mesh.addIndex(index + 2);

            noise_seed = (this->make_apple_point(u - span * 0.5, v - span * 0.5) + this->make_apple_point(u + span * 0.5, v - span * 0.5) + this->make_apple_point(u + span * 0.5, v + span * 0.5)) / 3;
            noise_value = ofNoise(glm::vec4(noise_seed * 0.25, ofGetFrameNum() * 0.008));
            scale = 30;
            if (noise_value > 20.65) {

                scale = ofMap(noise_value, 10.65, 21, 30, 50);
            }
            index = this->mesh.getNumVertices();

            this->mesh.addVertex(this->make_apple_point(u - span * 0.5, v - span * 0.5) * scale);
            this->mesh.addVertex(this->make_apple_point(u + span * 0.5, v - span * 0.5) * scale);
            this->mesh.addVertex(this->make_apple_point(u + span * 0.5, v + span * 0.5) * scale);

            this->mesh.addIndex(index); this->mesh.addIndex(index + 1); this->mesh.addIndex(index + 2);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {

    this->cam.begin();
    ofRotateZ(ofGetFrameNum() * 0.5);

    ofSetColor(22,300,430);  //color
    this->mesh.drawFaces();
    ofSetColor(100,0,111); //Stroke color

    this->mesh.drawWireframe();

    ofSetColor(220,30,10);  //color 2th
    this->mesh.drawFaces();
    
    ofSetColor(100,0,111); //Stroke color
    this->mesh.drawWireframe();

    
    this->cam.end();
    
}


//--------------------------------------------------------------
glm::vec3 ofApp::make_apple_point(float u, float v) {

    

    u *= DEG_TO_RAD;
    v *= DEG_TO_RAD;
  /*
    float x = (4 + 3.8 * cos(u)) * cos(v);
    float y = (4 + 3.8 * sin(u)) * sin(v);
    float z = 5 * log10(1 - 0.315 * u) + 5 * sin(u) + 2 * cos(u);
  */
    float x = (4 + 3.8 * cos(u)) * cos(v);
    float y = (4 + 3.8 * sin(u)) * sin(v);
    float z = 1 * log10(3 - 0.315 * u) + 5 * sin(v) + 2 * cos(u);

    //float x = 2*cos(u)*sin(u)*sin(u)+0.1*cos(v)*cos(u);
    //float y = 2*sin(u)*0.1*cos(v)*(sin(u)*sin(u)*sin(u)-0.2*sin(u)*cos(u)*cos(u));
    //float z = 0.1*sin(v);

    return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    ofBackground(0);
  
}

void ofApp::mouseReleased(int x, int y, int button){
        
    ofBackground(255,0,234);
}
