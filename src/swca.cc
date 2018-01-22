#include <node.h>
#include <node_buffer.h>
#include <dwmapi.h>

struct ACCENTPOLICY
{
	int nAccentState;
	int nFlags;
	unsigned int nColor;
	int nAnimationId;
};

struct WINCOMPATTRDATA
{
	int nAttribute;
	PVOID pData;
	ULONG ulDataSize;
};

void swca(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	typedef BOOL(WINAPI*pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);
	static pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(GetModuleHandle(TEXT("user32.dll")), "SetWindowCompositionAttribute");
	bool returnValue = false;

	if (SetWindowCompositionAttribute)
	{
		unsigned char* bufferData = (unsigned char*)node::Buffer::Data(args[0].As<v8::Object>());
		HWND handle = *reinterpret_cast<HWND*>(bufferData);

		ACCENTPOLICY policy = {
			(int)args[1]->NumberValue(),
			2, // No idea what this means, but it allows to use nColor correctly.
			(unsigned int)args[2]->NumberValue(),
			0
		};

		WINCOMPATTRDATA data = {
			19, // WCA_ACCENT_POLICY
			&policy,
			sizeof(ACCENTPOLICY)
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