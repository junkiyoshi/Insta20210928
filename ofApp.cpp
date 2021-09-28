#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	for (int i = 0; i < 50; i++) {

		auto particle = make_unique<Particle>();
		this->particles.push_back(move(particle));
	}

	this->hexagon_height = 6;
	this->hexagon_width = 3;

	for (float x = this->hexagon_width * 18; x <= ofGetWidth() - this->hexagon_width * 18; x += this->hexagon_height * 1.5) {

		for (float y = this->hexagon_height * 6; y <= ofGetHeight() - this->hexagon_height * 6; y += this->hexagon_height * 3) {

			this->number_list.push_back(make_pair(glm::vec2(x, y), 0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (auto& particle : this->particles) {

		particle->update(this->particles);
	}

	for (auto& number : this->number_list) {

		number.second = number.second > 0 ? number.second - 1 : 0;
	}


	for (auto& particle : this->particles) {

		for (auto& number : this->number_list) {

			if (glm::distance(particle->location, number.first) < 10) {

				number.second = number.second < 50 ? number.second + 8 : 50;
			}
		}
	}
		
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	for (auto& number : this->number_list) {

		if (number.second > 0) {

			int number_index = ofMap(ofNoise(glm::vec3(number.first * 0.05, ofGetFrameNum() * 0.03)), 0, 1, 0, 10);
			this->draw_digital(number.first, number_index);
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw_digital(glm::vec2 location, int number_index) {

	vector<pair<glm::vec2, float>> part_list = {
		make_pair<glm::vec2, float>(location + glm::vec2(0, -this->hexagon_height), 90),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * 0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(0, 0), 90),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * -0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(this->hexagon_height * 0.5, this->hexagon_height * -0.5), 0),
		make_pair<glm::vec2, float>(location + glm::vec2(0, this->hexagon_height), 90)
	};

	vector<vector<int>> index_list = {
		{ 0, 1, 2, 4, 5, 6 },
		{ 2, 5 },
		{ 0, 1, 3, 5, 6 },
		{ 0, 2, 3, 5, 6 },
		{ 2, 3, 4, 5 },
		{ 0, 2, 3, 4, 6 },
		{ 0, 1, 2, 3, 4, 6 },
		{ 0, 2, 5 },
		{ 0, 1, 2, 3, 4, 5, 6 },
		{ 0, 2, 3, 4, 5, 6 },
	};

	for (auto& index : index_list[number_index]) {

		this->draw_hexagon(part_list[index].first, part_list[index].second);
	}
}

//--------------------------------------------------------------
void ofApp::draw_hexagon(glm::vec2 location, float deg) {

	ofPushMatrix();
	ofTranslate(location);
	ofRotate(deg);

	vector<glm::vec2> vertices;
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * -0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * 0.5));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * 0.4));
	vertices.push_back(glm::vec2(this->hexagon_width * 0.4, this->hexagon_height * -0.4));
	vertices.push_back(glm::vec2(0, this->hexagon_height * -0.5));

	ofFill();
	ofSetColor(39);

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape(true);

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}