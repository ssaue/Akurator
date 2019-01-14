/*
  ==============================================================================

    sspFolderFileString.cpp
    Created: 14 Jan 2019 2:21:44pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspFolderFileString.h"
#include "sspLogging.h"

#include <algorithm>
#include <random>
namespace {
	// Establish a random-number engine
	std::random_device rd;
	std::mt19937 random_generator(rd());
}

#include <filesystem>
namespace fs = std::filesystem;

namespace {

	static const std::vector<std::string> audio_extensions = { ".wav", ".aif", ".aiff", ".ogg" };
	static bool verifyAudioExtension(std::string_view ext) 
	{
		return std::find(audio_extensions.cbegin(), audio_extensions.cend(), ext) != audio_extensions.cend();
	}

	template <typename T>
	bool searchFiles(fs::path dir, std::vector<std::string>& files, bool audio, std::string_view previous)
	{
		bool foundPrevious = false;
		for (const auto & entry : T(dir)) {
			if (fs::is_regular_file(entry.status()) && (!audio || verifyAudioExtension(entry.path().extension().string()))) {
				auto found = entry.path().string();
				if (found == previous) {
					foundPrevious = true;
				}
				else {
					files.push_back(entry.path().string());
				}
			}
		}
		return foundPrevious;
	}
}

std::string_view sspFolderFileString::getString() const
{
	std::vector<std::string> files;
	auto dir = fs::path(folder_->getString());
	auto err = std::error_code();
	if (fs::exists(dir, err) && fs::is_directory(dir)) {
		bool foundPrevious = false;
		if (recursive_) {
			foundPrevious = searchFiles< fs::recursive_directory_iterator>(dir, files, audio_only_, previous_path_);
		}
		else {
			foundPrevious = searchFiles< fs::directory_iterator>(dir, files, audio_only_, previous_path_);
		}
		if (files.empty())
			return foundPrevious ? previous_path_ : std::string("");
		else {
			if (files.size() == 1) {
				previous_path_ = files[0];
			}
			else {
				std::uniform_int_distribution<size_t> dist(0, files.size()-1);
				auto index = dist(random_generator);
				previous_path_ = files[index];
			}
			return previous_path_;
		}
	}
	else {
		return std::string("");
	}
}

bool sspFolderFileString::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	if (!folder_) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid folder string";
	}
	else {
		if (folder_.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
		else {
			auto dir = fs::path(folder_->getString());
			auto err = std::error_code();
			if (!fs::exists(dir, err) || !fs::is_directory(dir)) {
				SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " points to an invalid directory";
			}
		}
	}

	return bReturn;
}
