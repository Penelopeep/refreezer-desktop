#include <flutter/dart_project.h>
#include <flutter/flutter_view_controller.h>
#include <windows.h>

#include <flutter/binary_messenger.h>
#include <flutter/method_channel.h>
#include <flutter/standard_method_codec.h>

#include <iostream>
#include <memory>

#include "flutter_window.h"
#include "utils.h"


void HandleNativeMethodCall(
	const flutter::MethodCall<flutter::EncodableValue>& method_call,
	std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
	if (method_call.method_name().compare("startServer") == 0) {
		std::cout << "[Native] Call to \"startServer\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	/*else if (method_call.method_name().compare("") == 0) {
		std::cout << "[Native] Call to \"\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}*/
	else if (method_call.method_name().compare("getDownloads") == 0) {
		std::cout << "[Native] Call to \"getDownloads\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	else if (method_call.method_name().compare("start") == 0) {
		std::cout << "[Native] Call to \"start\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	else if (method_call.method_name().compare("addDownloads") == 0) {
		std::cout << "[Native] Call to \"addDownloads\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	else if (method_call.method_name().compare("listen") == 0) {
		std::cout << "[Native] Call to \"listen\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	else if (method_call.method_name().compare("loadDownloads") == 0) {
		std::cout << "[Native] Call to \"loadDownloads\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	else if (method_call.method_name().compare("updateSettings") == 0) {
		std::cout << "[Native] Call to \"updateSettings\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	else if (method_call.method_name().compare("getPreloadInfo") == 0) {
		std::cout << "[Native] Call to \"getPreloadInfo\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	else if (method_call.method_name().compare("getLaunchAction") == 0) {
		std::cout << "[Native] Call to \"getLaunchAction\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	else if (method_call.method_name().compare("setShortcutItems") == 0) {
		std::cout << "[Native] Call to \"setShortcutItems\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	else {
		std::cout << "[Native] Call to unknown method: " << method_call.method_name() << std::endl;
		result->NotImplemented();
	}
}

void HandleDownloadMethodCall(
	const flutter::MethodCall<flutter::EncodableValue>& method_call,
	std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
	if (method_call.method_name().compare("listen") == 0) {
		std::cout << "[Downloads] Call to \"listen\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}
	/*else if (method_call.method_name().compare("") == 0) {
		std::cout << "[Downloads] Call to \"\" received." << std::endl;
		result->Success(flutter::EncodableValue(""));
	}*/
	else {
		std::cout << "[Downloads] Call to unknown method: " << method_call.method_name() << std::endl;
		result->NotImplemented();
	}
}

int APIENTRY wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prev,
	_In_ wchar_t* command_line, _In_ int show_command) {
	// Attach to console when present (e.g., 'flutter run') or create a
	// new console when running with a debugger.
	if (!::AttachConsole(ATTACH_PARENT_PROCESS) && ::IsDebuggerPresent()) {
		CreateAndAttachConsole();
	}

	// Initialize COM, so that it is available for use in the library and/or
	// plugins.
	::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	flutter::DartProject project(L"data");

	std::vector<std::string> command_line_arguments =
		GetCommandLineArguments();

	project.set_dart_entrypoint_arguments(std::move(command_line_arguments));

	FlutterWindow window(project);
	Win32Window::Point origin(10, 10);
	Win32Window::Size size(1280, 720);
	if (!window.Create(L"refreezer", origin, size)) {
		return EXIT_FAILURE;
	}
	window.SetQuitOnClose(true);

	flutter::BinaryMessenger* messenger = window.GetController()->engine()->messenger();
	const static std::string native_channel_name("r.r.refreezer/native");
	const static std::string download_channel_name("r.r.refreezer/downloads");
	auto native_channel =
		std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
			messenger, native_channel_name,
			&flutter::StandardMethodCodec::GetInstance());

	native_channel->SetMethodCallHandler(
		[](const flutter::MethodCall<flutter::EncodableValue>& call,
			std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>>
			result) { HandleNativeMethodCall(call, std::move(result)); });

	auto download_channel =
		std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
			messenger, download_channel_name,
			&flutter::StandardMethodCodec::GetInstance());
	download_channel->SetMethodCallHandler(
		[](const flutter::MethodCall<flutter::EncodableValue>& call,
			std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>>
			result) { HandleDownloadMethodCall(call, std::move(result)); });

	::MSG msg;
	while (::GetMessage(&msg, nullptr, 0, 0)) {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	::CoUninitialize();
	return EXIT_SUCCESS;
}
