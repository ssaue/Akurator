/*
  ==============================================================================

	sspLogging.cpp
	Created: 10 November 2023
	Author:  sigurds

  ==============================================================================
*/

#include "sspLogging.h"

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace logging {

    std::shared_ptr<spdlog::logger> configure(const std::string& logger_name, const std::vector<Config>& configs,
        bool async, FlushPolicy flush_policy);
    void configure_sink(const spdlog::sink_ptr& sink, const Config& config);

    AkuratorLogger createLogger(const std::vector<Config>& configs, bool async, FlushPolicy flush_policy)
    {
        auto logger = configure(logger_name_server, configs, async, flush_policy);
        spdlog::set_default_logger(logger);
        return AkuratorLogger(logger);
    }

    void AkuratorLogger::setProjectSink(const std::string& logfile)
    {
        if (has_project_sink_) removeProjectSink();

        try {
            logger_->sinks().push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfile, true));
            has_project_sink_ = true;
        }
        catch (spdlog::spdlog_ex& e) {
            SSP_LOG(err, "Unable to establish project sink: {}", e.what());
        }
    }

    void AkuratorLogger::removeProjectSink()
    {
        if (has_project_sink_) {
            flush();
            // Currently no blocking flush for spdlog https://github.com/gabime/spdlog/issues/1696
            // sleep thread to give flush time to execute;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            logger_->sinks().pop_back();
            has_project_sink_ = false;
        }
    }

    std::shared_ptr<spdlog::logger> configure(const std::string& logger_name, const std::vector<Config>& configs,
        bool async, FlushPolicy flush_policy)
    {
        // Ensure no residual loggers cause problems
        spdlog::drop(logger_name);

        spdlog::level::level_enum minimum_level = spdlog::level::critical;

        if (async && not spdlog::thread_pool()) {
            spdlog::init_thread_pool(8192, 1);
        }
        std::vector<spdlog::sink_ptr> sinks;

        for (const auto& config : configs) {
            spdlog::sink_ptr sink;
            switch (config.type) {
            case Type::console:
                sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
                break;
            case Type::file:
                sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                    config.filename, true);
                break;
#ifdef SYSLOG_AVAILABLE
            case Type::syslog:
                sink = std::make_shared<spdlog::sinks::syslog_sink_mt>("", 0, LOG_USER, false);
                break;
#endif
            default:
                // Use null sink to discard logs to avoid undefined sink_ptr
                sink = std::make_shared<spdlog::sinks::null_sink_mt>();
                break;
            }

            configure_sink(sink, config);
            sinks.push_back(sink);
            if (config.level < minimum_level) {
                minimum_level = config.level;
            }
        }

        std::shared_ptr<spdlog::logger> combo_logger;
        if (async) {
            combo_logger =
                std::make_shared<spdlog::async_logger>(logger_name, sinks.begin(), sinks.end(), spdlog::thread_pool(),
                    spdlog::async_overflow_policy::overrun_oldest);
        }
        else {
            combo_logger = std::make_shared<spdlog::logger>(logger_name, sinks.begin(), sinks.end());
        }

        switch (flush_policy) {
        case FlushPolicy::warning:
            combo_logger->flush_on(spdlog::level::warn);
            break;
        case FlushPolicy::trace:
            combo_logger->flush_on(spdlog::level::trace);
            break;
        case FlushPolicy::automatic:
            // automatic retains the loggers default optimized solution
            break;
        default:
            break;
        }

        combo_logger->set_level(minimum_level);
        return combo_logger;
    }

    void configure_sink(const spdlog::sink_ptr& sink, const Config& config)
    {
        switch (config.format) {
        case Format::debugger:
            sink->set_pattern("[%Y-%m-%d %T.%e][%=8l][%s:%#] %v");
            break;
        case Format::verify:
        default:
            sink->set_pattern("[%=8l][%s:%#] %v");
            break;
        }

        sink->set_level(config.level);
    }

    void flush()
    {
        spdlog::apply_all([](auto logger) { logger->flush(); });
    }

    void close() { spdlog::shutdown(); }

    void defaultConfiguration() { createLogger({ logging::Config() }); }

}  // namespace audio_server::logging