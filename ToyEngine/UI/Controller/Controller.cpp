#include "UI/Controller/Controller.h"
#include <iostream>
#include <sstream>

namespace ui {
    void Controller::init()
    {
        registerBindings();
    }
    bool Controller::getBool(const std::string& bindingName)
    {
        if (mBoolBinding[bindingName].getter) {
            return mBoolBinding[bindingName].getter();
        }
        return false;
    }

    float Controller::getFloat(const std::string& bindingName)
    {
        if (mFloatBinding[bindingName].getter) {
            return mFloatBinding[bindingName].getter();
        }
        return 0.0f;
    }

    glm::vec3 Controller::getVec(const std::string& bindingName)
    {
        if (mVec3Binding[bindingName].getter) {
            return mVec3Binding[bindingName].getter();
        }
        return glm::vec3();
    }

    int Controller::getInt(const std::string& bindingName)
    {
        if (mIntBinding[bindingName].getter) {
            return mIntBinding[bindingName].getter();
        }
        return 0;
    }

    void Controller::setFloat(const std::string& bindingName, float newVal) {
        if (mFloatBinding[bindingName].setter) {
            mFloatBinding[bindingName].setter(newVal);
        }
    }

    void Controller::setInt(const std::string& bindingName, int newVal) {
        if (mIntBinding[bindingName].setter) {
            mIntBinding[bindingName].setter(newVal);
        }
    }

    void Controller::setBool(const std::string& bindingName, bool newVal) {
        if (mBoolBinding[bindingName].setter) {
            mBoolBinding[bindingName].setter(newVal);
        }
    }

    void Controller::setVec3(const std::string& bindingName, glm::vec3 newVal) {
        if (mVec3Binding[bindingName].setter) {
            mVec3Binding[bindingName].setter(newVal);
        }
    }

    void Controller::bindBool(std::string bindingName, std::function<bool()> getter, std::function<void(bool)> setter)
    {
        if (mBoolBinding.find(bindingName) != mBoolBinding.end()) {
            std::cerr << "binding name collision!" << "collision key name:" << bindingName << std::endl;
            return;
        }
        mBoolBinding[bindingName] = { getter,setter };
    }

    void Controller::bindFloat(std::string bindingName, std::function<float()> getter, std::function<void(float)> setter)
    {
        if (mFloatBinding.find(bindingName) != mFloatBinding.end()) {
            std::cerr << "binding name collision!" << "collision key name:" << bindingName << std::endl;
            return;
        }
        mFloatBinding[bindingName] = { getter,setter };
    }

    void Controller::bindInt(std::string bindingName, std::function<int()> getter, std::function<void(int)> setter)
    {
        if (mIntBinding.find(bindingName) != mIntBinding.end()) {
            std::cerr << "binding name collision!" << "collision key name:" << bindingName << std::endl;
            return;
        }
        mIntBinding[bindingName] = { getter,setter };
    }

    void Controller::bindVec3(std::string bindingName, std::function<glm::vec3()> getter, std::function<void(glm::vec3)> setter)
    {
        if (mVec3Binding.find(bindingName) != mVec3Binding.end()) {
            std::cerr << "binding name collision!" << "collision key name:" << bindingName << std::endl;
            return;
        }
        mVec3Binding[bindingName] = { getter,setter };
    }

    void Controller::bindButtonInteractHandler(std::string bindingName, std::function<void(ViewEvent)> callback)
    {
        auto iter = mButtonBinding.find(bindingName);
        if (iter != mButtonBinding.end()) {
            std::cerr << "button interact handler key collision!" << std::endl;
        }
        mButtonBinding[bindingName] = callback;
    }


    void Controller::handleViewEvents()
    {
        while (!mViewEventQueue.empty()) {
            auto viewEvent = mViewEventQueue.front();
            mViewEventQueue.pop();

            switch (viewEvent.viewEventType) {
            case ViewEventType::InputEvent:
                handleInputEvent(viewEvent);
                break;
            case ViewEventType::ButtonEvent:
                handleButtonEvent(viewEvent);
                break;
            }
        }
    }
    void Controller::handleInputEvent(const ViewEvent& event)
    {
        switch (event.valueType) {
        case BindingValueType::Bool:
            convertBoolBindingValAndSet(event);
            break;
        case BindingValueType::Float:
            convertFloatBindingValAndSet(event);
            break;
        case BindingValueType::Int:
            convertIntBindingValAndSet(event);
            break;
        case BindingValueType::Vec3:
            convertVec3BindingValAndSet(event);
        }
    }

    void Controller::convertVec3BindingValAndSet(const ui::ViewEvent& event)
    {
        auto iter = mVec3Binding.find(event.name);
        if (iter != mVec3Binding.end()) {
            iter->second.setter(convertStringToVec3(event.value));
        }
    }

    void Controller::convertIntBindingValAndSet(const ui::ViewEvent& event)
    {
        auto iter = mIntBinding.find(event.name);
        if (iter != mIntBinding.end()) {
            iter->second.setter(std::stoi(event.value));
        }
    }

    void Controller::convertFloatBindingValAndSet(const ui::ViewEvent& event)
    {
        auto iter = mFloatBinding.find(event.name);
        if (iter != mFloatBinding.end()) {
            iter->second.setter(std::stof(event.value));
        }
    }

    void Controller::convertBoolBindingValAndSet(const ui::ViewEvent& event)
    {
        auto iter = mBoolBinding.find(event.name);
        if (iter != mBoolBinding.end()) {
            if (event.value != "true" && event.value != "false") {
                std::cerr << "bool binding value is neither true nor false!" << std::endl;
            }
            iter->second.setter(event.value == "true" ? true : false);
        }
    }

    void Controller::handleButtonEvent(const ViewEvent& event)
    {
        if (mButtonBinding.find(event.name) == mButtonBinding.end()) {
            return;
        }

        mButtonBinding[event.name](event);
    }

    //required pattern: x,y,z
    glm::vec3 Controller::convertStringToVec3(const std::string& str) {
        std::vector<float>vec;
        vec.reserve(3);
        int start = 0;
        int end = str.find(",",0);
        while (end != str.npos) {
            vec.push_back(std::stof(str.substr(start, end)));
            start = end + 1;
            end = str.find(",", start);
        }
        vec.push_back(std::stof(str.substr(start)));
        if (vec.size() != 3) {
            std::cerr << "vec3 parse failure!" << std::endl;
            return glm::vec3();
        }

        return glm::vec3(vec[0], vec[1], vec[2]);
    }

    void Controller::addViewEvent(ViewEvent event) {
        mViewEventQueue.push(event);
    }

    void Controller::tick() {
        handleViewEvents();
    }


}

