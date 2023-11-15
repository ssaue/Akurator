/*
  ==============================================================================

	sspLogging.h
	Created: 7 Jan 2019 6:58:19pm
	Author:  sigurds

	Updated with spdlog November 2023

  ==============================================================================
*/

#pragma once

#include <string>
#include <vector>

#include <spdlog/spdlog.h>

#if SPDLOG_ACTIVE_LEVEL != SPDLOG_LEVEL_OFF
#define SSP_LOG(sev, ...) SPDLOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::sev, __VA_ARGS__)
#define SSP_LOG_WRAPPER_ERROR(nErrors, bOK, ...) nErrors++; bOK = false;\
	 SPDLOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::err, __VA_ARGS__)
#define SSP_LOG_WRAPPER_WARNING(nWarnings, bOK, ...) nWarnings++;\
	 SPDLOG_LOGGER_CALL(spdlog::default_logger_raw(), spdlog::level::warn, __VA_ARGS__)
#else
#define SSP_LOG(sev, ...) (void)0
#define SSP_LOG_WRAPPER_ERROR(nErrors, bOK, ...) (void)0
#define SSP_LOG_WRAPPER_WARNING(nWarnings, bOK, ...) (void)0
#endif

namespace logging {

	constexpr auto logger_name_server = "akurator";

	enum class FlushPolicy { automatic, warning, trace };
	enum class Format { verify, debugger };
	enum class Rotation { rotation_size = 5 * 1024 * 1024, max_file_count = 10 };
	enum class Type { console, file, syslog };

	class AkuratorLogger {
	public:
		AkuratorLogger() = default;
		explicit AkuratorLogger(std::shared_ptr<spdlog::logger> logger) : logger_(std::move(logger)) {}
		// @threading not thread safe with regards to logging
		void setProjectSink(const std::string& logfile);
		// @threading not thread safe with regards to logging
		void removeProjectSink();

	private:
		std::shared_ptr<spdlog::logger> logger_;
		bool has_project_sink_ = false;
	};

	struct Config {
		Type type = Type::file;
		std::string filename = "logs/debug.log";
		Format format = Format::debugger;
		spdlog::level::level_enum level = spdlog::level::debug;
	};

	//@throws spdlog::spdlog_ex if spdlog fails to create a logger (e.g. unwritable filename);
	AkuratorLogger createLogger(const std::vector<Config>& configs, bool async = true,
		FlushPolicy flush_policy = FlushPolicy::automatic);

	void flush();
	void close();

	// The default configuration creates an error log in "logs/debug.log"
	//@throws spdlog::spdlog_ex if "logs/debug.log" is not writable
	void defaultConfiguration();

}  // namespace logging
