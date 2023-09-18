#pragma once
#include <string>
#include <functional>
#include <glm/ext/vector_float3.hpp>
#include <glm/fwd.hpp>
#include <unordered_map>
#include <queue>
#include <entt/entity/fwd.hpp>

#define Binding(type) std::unordered_map<std::string, AccessBindings<type>>
#define ButtonBinding std::unordered_map<std::string, std::function<void(ui::ViewEvent)>>

namespace ui
{
	template<typename T> struct AccessBindings{
		std::function<T()>getter;
		std::function<void(T)>setter;
	};

	enum class ViewEventType{
		InputEvent,
		ButtonEvent,
	};

	enum class BindingValueType {
		Bool,
		Float,
		Int,
		Vec3,
	};

	struct ButtonEventData {
		std::string path;
	};

	struct ViewEvent {
	public:
		ViewEventType viewEventType;
		std::string name;
		BindingValueType valueType;
		std::string value;

		std::string path;
		std::string modelName;
		entt::registry& registry;

		entt::entity parentEntity;
		
		std::vector<glm::vec3> vectorGroup;
		std::vector<float>floatGroup;
		
		ViewEvent() = default;
		ViewEvent(entt::registry& registry) :registry(registry) {};

	};

	class Controller:public std::enable_shared_from_this<Controller>
	{
	public:

		Controller() = default;

		void init();

		bool getBool(const std::string& bindingName);
		float getFloat(const std::string& bindingName);
		glm::vec3 getVec(const std::string& bindingName);
		int getInt(const std::string& bindingName);
		void addViewEvent(ViewEvent event);

		void tick();

	protected:
		void bindBool(std::string, std::function<bool()>getter, std::function<void(bool)>setter);
		void bindFloat(std::string, std::function<float()>getter, std::function<void(float)>setter);
		void bindInt(std::string, std::function<int()>getter, std::function<void(int)>setter);
		void bindVec3(std::string, std::function<glm::vec3()>getter, std::function<void(glm::vec3)>setter);
		void bindButtonInteractHandler(std::string bindingName, std::function<void(ViewEvent)> callback);

		virtual void registerBindings() = 0;

		virtual void onSelectionChange(entt::entity) = 0;

		void handleViewEvents();
		virtual void handleInputEvent(const ViewEvent& event);
		void convertVec3BindingValAndSet(const ui::ViewEvent& event);
		void convertIntBindingValAndSet(const ui::ViewEvent& event);
		void convertFloatBindingValAndSet(const ui::ViewEvent& event);
		void convertBoolBindingValAndSet(const ui::ViewEvent& event);
		virtual void handleButtonEvent(const ViewEvent& event);

		void setFloat(const std::string& bindingName, float newVal);

		void setInt(const std::string& bindingName, int newVal);

		void setBool(const std::string& bindingName, bool newVal);

		void setVec3(const std::string& bindingName, glm::vec3 newVal);

		glm::vec3 convertStringToVec3(const std::string& str);


		Binding(bool) mBoolBinding;
		Binding(glm::vec3) mVec3Binding;
		Binding(float) mFloatBinding;
		Binding(int) mIntBinding;
		ButtonBinding mButtonBinding;

		std::queue<ViewEvent> mViewEventQueue;
	};
}

