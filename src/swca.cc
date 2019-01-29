#include <node_buffer.h>
#include <windows.h>

#include "swcadef.h"

void swca(const v8::FunctionCallbackInfo<v8::Value> &args)
{
	static const auto SetWindowCompositionAttribute =
		(PFN_SET_WINDOW_COMPOSITION_ATTRIBUTE)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "SetWindowCompositionAttribute");
	bool returnValue = false;

	if (SetWindowCompositionAttribute)
	{
		HWND handle = *reinterpret_cast<HWND *>(node::Buffer::Data(args[0].As<v8::Object>()));

		ACCENT_POLICY policy = {
			static_cast<ACCENT_STATE>(args[1].As<v8::Int32>()->Value()),
			2,
			args[2].As<v8::Uint32>()->Value(),
			0
		};

		const WINDOWCOMPOSITIONATTRIBDATA data = {
			WCA_ACCENT_POLICY,
			&policy,
			sizeof(policy)
		};

		returnValue = SetWindowCompositionAttribute(handle, &data);
	}

	args.GetReturnValue().Set(returnValue);
}

void init(v8::Local<v8::Object> exports)
{
	NODE_SET_METHOD(exports, "swca", swca);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init)