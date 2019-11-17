

#include <iostream>
#include <cstring>
#include "gdexample.h"
#include "Leap.h"

using namespace std;
using namespace Leap;
using namespace godot;

class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);

  private:
};

SampleListener listener;
Controller controller;
float x, y, lastx, lasty;
float scale, lastscale;
float rotx, roty, rotz;
float lastrotx, lastroty, lastrotz;

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
  controller.enableGesture(Gesture::TYPE_CIRCLE);
  controller.enableGesture(Gesture::TYPE_KEY_TAP);
  controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
  controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
  // Note: not dispatched when running in a debugger.
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}
void SampleListener::onFocusGained(const Controller& controller) {
  std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
  std::cout << "Focus Lost" << std::endl;
}

void SampleListener::onDeviceChange(const Controller& controller) {
  std::cout << "Device Changed" << std::endl;
  const DeviceList devices = controller.devices();

  for (int i = 0; i < devices.count(); ++i) {
    std::cout << "id: " << devices[i].toString() << std::endl;
    std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
  }
}

void SampleListener::onServiceConnect(const Controller& controller) {
  std::cout << "Service Connected" << std::endl;
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
  std::cout << "Service Disconnected" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
	//cout << "onFrame" << endl;
   const Frame frame = controller.frame();

   HandList hands = frame.hands();
   for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
	const Hand hand = *hl;
	if (!hand.isRight()) break;
	float x = hand.palmPosition().x;
	float y = hand.palmPosition().y;
	float z = hand.palmPosition().z;
	//cout << x << " " << y << " " << z << endl;
	::x = x;
	::y = z;
	float ps = hand.grabStrength();
	if (ps > 0.0) {
            cout << "pinch distance" << hand.grabStrength() << endl;
	    scale = 1.0 - ps;
	}
	const Vector normal = hand.palmNormal();
	const Vector direction = hand.direction();
	//cout << "roll " << normal.roll() << endl;
	::rotx = normal.roll();
	::roty = direction.yaw();
	::rotz = direction.pitch();
   }

}

void GDExample::_register_methods() {
    register_method((char *)"_process", &GDExample::_process);
}

GDExample::GDExample() {
    // Initialize any variables here
    //SampleListener listener;
    //Controller controller;
    ::controller.addListener(listener);
    //controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

    time_passed = 0.0;
    //realowner = owner;
    cout << "type " << typeid(owner).name() << endl;
    ::x = 0.0;
    ::y = 0.0;
    ::lastx = 0.0;
    ::lasty = 0.0;
    ::scale = 0.0;
    ::lastscale = 0.0;
    ::rotx = 0.0;
    ::roty = 0.0;
    ::rotz = 0.0;
    ::lastrotx = 0.0;
    ::lastroty = 0.0;
    ::lastrotz = 0.0;
    cout << "starting" << endl;
}

GDExample::~GDExample() {
    // Add your cleanup procedure here
    ::controller.removeListener(listener);
}

void GDExample::_process(float delta) {
    time_passed += delta;
    float world_scale = 0.001;
    Transform hand_transform;

    //Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 1.5)));

    // y is up/down in godot
    if ((::x != ::lastx) || (::y != ::lasty)) {
	Vector3 new_position = Vector3(x/10, 0, y/10);
	//new_position = Vector2(x+300.0, y+300.0);
    	//cout << "new position: " << new_position.x << " " << new_position.y << endl;
    	owner->set_translation(new_position);
	::lastx = ::x;
	::lasty = ::y;
    	}
    if (::scale != ::lastscale) {
	Vector3 sc = Vector3(1+scale, 1+scale, 1+scale);
	owner->set_scale(sc);
	::lastscale = ::scale;
    }
    if ((::rotx != ::lastrotx) || (::roty != ::lastroty) || (::rotz != ::lastrotz)) {
	Vector3 rot = Vector3(rotz, roty, rotx);
	cout << "rotation " << rot.x << " " << rot.y << " " << rot.z << endl;
	owner->set_rotation(rot);
	::lastrotx = ::rotx;
	::lastroty = ::roty;
	::lastrotz = ::rotz;
	}
}

