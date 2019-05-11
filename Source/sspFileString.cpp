/*
  ==============================================================================

    sspFileString.cpp
    Created: 14 Jan 2019 2:21:44pm
    Author:  sigurds

  ==============================================================================
*/

#include "sspFileString.h"
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

	template <typename T>
	int countFiles(fs::path dir, bool audio)
	{
		int count = 0;
		for (const auto & entry : T(dir)) {
			if (fs::is_regular_file(entry.status()) && (!audio || verifyAudioExtension(entry.path().extension().string()))) {
				count++;
			}
		}
		return count;
	}
}

sspFileString::sspFileString()
	: sspString(), path_(), recursive_(false), audio_only_(true)
{
}

std::string sspFileString::getString() const
{
	auto path_ptr = path_.lock();
	if (!path_ptr) 
		return std::string("");
	
	auto path = fs::path(path_ptr->getString());
	auto err = std::error_code();

	if (fs::exists(path, err)) {
		if (fs::is_regular_file(path) && (!audio_only_ || verifyAudioExtension(path.extension().string()))) {
			return path.string();
		}
		else if (fs::is_directory(path)) {
			std::vector<std::string> files;
			bool foundPrevious = false;
			if (recursive_) {
				foundPrevious = searchFiles< fs::recursive_directory_iterator>(path, files, audio_only_, previous_path_);
			}
			else {
				foundPrevious = searchFiles< fs::directory_iterator>(path, files, audio_only_, previous_path_);
			}
			if (files.empty())
				return foundPrevious ? previous_path_ : std::string("");
			else {
				if (files.size() == 1) {
					previous_path_ = files[0];
				}
				else {
					std::uniform_int_distribution<size_t> dist(0, files.size() - 1);
					auto index = dist(random_generator);
					previous_path_ = files[index];
				}
				return previous_path_;
			}
		}
	}

	// If it gets this far, then no file is found
	return std::string("");
}

bool sspFileString::verify(int & nErrors, int & /*nWarnings*/) const
{
	bool bReturn = true;

	auto path_ptr = path_.lock();

	if (!path_ptr) {
		SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has invalid folder string";
	}
	else {
		if (path_ptr.get() == this) {
			SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " has a self reference";
		}
		else {
			auto path = fs::path(path_ptr->getString());
			auto err = std::error_code();
			if (!fs::exists(path, err) || !(fs::is_directory(path) || fs::is_regular_file(path))) {
				SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " points to an invalid path";
			}
			if (fs::is_directory(path)) {
				auto num_files = recursive_ ? countFiles< fs::recursive_directory_iterator>(path, audio_only_) 
					: countFiles< fs::directory_iterator>(path, audio_only_);
				if (num_files == 0) {
					SSP_LOG_WRAPPER_ERROR(nErrors, bReturn) << getName() << " contains no valid files in the folder";
				}
			}
		}
	}

	return bReturn;
}
