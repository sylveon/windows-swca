#include <cstdint>
#include <dwmapi.h>
#include <node.h>
#include <node_buffer.h>

struct ACCENTPOLICY
{
	int32_t nAccentState;
	int32_t nFlags;
	uint32_t nColor;
	int32_t nAnimationId;
};

struct WINCOMPATTRDATA
{
	int32_t nAttribute;
	void *pData;
	uint32_t ulDataSize;
};

void swca(const v8::FunctionCallbackInfo<v8::Value> &args)
{
	typedef BOOL(WINAPI *pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA *);
	static pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "SetWindowCompositionAttribute");
	bool returnValue = false;

	if (SetWindowCompositionAttribute)
	{
		HWND handle = *reinterpret_cast<HWND *>(node::Buffer::Data(args[0].As<v8::Object>()));

		ACCENTPOLICY policy = {
			static_cast<int32_t>(args[1]->NumberValue()),
			2, // No idea what this means, but it allows to use nColor correctly.
			static_cast<uint32_t>(args[2]->NumberValue()),
			0
		};

		WINCOMPATTRDATA data = {
			19, // WCA_ACCENT_POLICY
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